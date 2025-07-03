#include "rclcpp/rclcpp.hpp"
#include "can_packet/msg/can_packet.hpp"
#include "can_converter/data_conversion.hpp"

#include <boost/asio.hpp>
#include <memory>
#include <string>



class usb_to_pub : public rclcpp::Node {
private:
    rclcpp::Publisher<can_packet::msg::CanPacket>::SharedPtr pub;

    boost::asio::io_context io_;
    boost::asio::serial_port serial_;
    std::thread io_thread_;

    std::array<uint8_t, 256> read_buf_;
    std::array<uint8_t, 256> udp_preserved_data_;
    size_t packet_tail_ = 0;

    void start_read() {
        serial_.async_read_some(boost::asio::buffer(read_buf_),
            std::bind(&usb_to_pub::handle_read, this, std::placeholders::_1, std::placeholders::_2));
    }

    void handle_read(const boost::system::error_code &ec, std::size_t bytes_transferred) {
        if (ec) {
            RCLCPP_ERROR(this->get_logger(), "Read error: %s", ec.message().c_str());
            return;
        }

        for (size_t i = 0; i < bytes_transferred; ++i) {
            uint8_t byte = read_buf_[i];

            if (byte == '\0') {
                udp_preserved_data_[packet_tail_++] = '\0';

                if (packet_tail_ == 68) {
                    can_packet::msg::CanPacket tx_packet;
                    decode_serial_to_can(udp_preserved_data_.data(), tx_packet);
                    pub->publish(tx_packet);

                    RCLCPP_INFO(this->get_logger(), "can to pub id is %x", tx_packet.id);
                } else {
                    RCLCPP_WARN(this->get_logger(), "packet error (length %zu)", packet_tail_);
                }

                packet_tail_ = 0;
                udp_preserved_data_.fill(0);
            } else {
                if (packet_tail_ < udp_preserved_data_.size()) {
                    udp_preserved_data_[packet_tail_++] = byte;
                } else {
                    // バッファあふれ
                    RCLCPP_ERROR(this->get_logger(), "Buffer overflow");
                    packet_tail_ = 0;
                    udp_preserved_data_.fill(0);
                }
            }
        }

        // 次の非同期受信を開始
        start_read();
    }

public:
    usb_to_pub(const std::string &port_name) : Node("usb_to_pub"), serial_(io_) {

        RCLCPP_INFO(this->get_logger(), "Serial subscriber started on %s", port_name.c_str());

        rclcpp::QoS qos_profile(rclcpp::KeepLast(10));
        qos_profile.best_effort();
        qos_profile.durability_volatile();

        pub = this->create_publisher<can_packet::msg::CanPacket>("can_rx_line", qos_profile);

        try {
            serial_.open(port_name);
            serial_.set_option(boost::asio::serial_port_base::baud_rate(115200));
        } catch (std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Serial open failed: %s", e.what());
        }

        start_read();  // 最初の非同期受信を始める

        io_thread_ = std::thread([this]() { io_.run(); });
        
    }

    ~usb_to_pub() {
        io_.stop();
        if (io_thread_.joinable()) {
            io_thread_.join();
        }
        if (serial_.is_open()) {
            serial_.close();
        }
    }
};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<usb_to_pub>("/dev/ttyACM0");
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();

    //rclcpp::spin(std::make_shared<can_to_pub>(5000)); // 変更

    rclcpp::shutdown();

    return 0;
}