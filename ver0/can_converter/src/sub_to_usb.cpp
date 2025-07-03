#include "rclcpp/rclcpp.hpp"
#include "can_packet/msg/can_packet.hpp"
#include "can_converter/data_conversion.hpp"


#include <boost/asio.hpp>
#include <memory>
#include <string>




class sub_to_usb : public rclcpp::Node
{
private:

	rclcpp::Subscription<can_packet::msg::CanPacket>::SharedPtr sub;
    boost::asio::io_context io_;
    boost::asio::serial_port serial_;
    std::string port_name_;
    std::thread io_thread_;


	void sub_callback(const can_packet::msg::CanPacket::SharedPtr rx_packet){

		uint8_t tx_data[68];

		encode_can_to_serial(*rx_packet, tx_data);

        boost::asio::async_write(serial_, boost::asio::buffer(tx_data),
            [](const boost::system::error_code &ec, std::size_t length) {
                if (ec) {
                    std::cerr << "Write error: " << ec.message() << std::endl;
                }
            }
        );

		RCLCPP_INFO(this -> get_logger(), "usb send id : %x", rx_packet -> id);

	}

public:

	sub_to_usb(const std::string &port_name) : Node("sub_to_usb"), io_(), serial_(io_), port_name_(port_name){

        try{
            serial_.open(port_name_);
            serial_.set_option(boost::asio::serial_port_base::baud_rate(115200));
            RCLCPP_INFO(this->get_logger(), "Serial port opened %s.", port_name_.c_str());
        }
        catch(const std::exception& e){
            RCLCPP_ERROR(this->get_logger(), "Error: %s", e.what());
        }

		rclcpp::QoS qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
		qos_profile.best_effort();
		qos_profile.durability_volatile();

		sub = this -> create_subscription<can_packet::msg::CanPacket>(
			"can_tx_line",
			qos_profile,
			std::bind(&sub_to_usb::sub_callback, this, std::placeholders::_1)
		);

        io_thread_ = std::thread([this](){ io_.run(); });

        RCLCPP_INFO(this->get_logger(), "init finished");


        uint8_t tx_data[68];
        can_packet::msg::CanPacket rxpacket;

        rxpacket.id = 0x105;
        rxpacket.data.fill(0);

		encode_can_to_serial(rxpacket, tx_data);

        boost::asio::async_write(serial_, boost::asio::buffer(tx_data),
            [](const boost::system::error_code &ec, std::size_t length) {
                if (ec) {
                    std::cerr << "Write error: " << ec.message() << std::endl;
                }
            }
        );

		RCLCPP_INFO(this -> get_logger(), "usb send id : %x", rxpacket.id);


	}

    ~sub_to_usb() {
        io_.stop();
        if (io_thread_.joinable()) {
            io_thread_.join();
        }
    }

};




int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);

    auto node = std::make_shared<sub_to_usb>("/dev/ttyACM0");
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();
    rclcpp::shutdown();

	return 0;
}