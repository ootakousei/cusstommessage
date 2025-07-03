#include "rclcpp/rclcpp.hpp"
#include "can_packet/msg/can_packet.hpp"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "can_converter/data_conversion.hpp"


class sub_to_can : public rclcpp::Node
{
private:

	rclcpp::Subscription<can_packet::msg::CanPacket>::SharedPtr sub;

	int sock;
	sockaddr_in stm_addr;

	void sub_callback(const can_packet::msg::CanPacket::SharedPtr rx_packet){

		uint8_t tx_data[68];

		encode_can_to_serial(*rx_packet, tx_data);

		// RCLCPP_INFO(this -> get_logger(), "id %x  %x", ascii_to_hax(tx_data[3]), ascii_to_hax(tx_data[4]));

		ssize_t err = sendto(sock, tx_data, 68, 0, reinterpret_cast<sockaddr*>(&stm_addr), sizeof(stm_addr));

		if(err < 0){
			RCLCPP_INFO(this -> get_logger(), "udp tx error");
		}

		RCLCPP_INFO(this -> get_logger(), "receive id : %x", rx_packet -> id);

	}

public:
	sub_to_can(const char* target_ip, uint16_t target_port) : Node("sub_to_can"){

		sock = socket(AF_INET, SOCK_DGRAM, 0);
		if(sock < 0){
			RCLCPP_INFO(this -> get_logger(), "socket error");
		}
		std::memset(&stm_addr, 0, sizeof(stm_addr));
		stm_addr.sin_family = AF_INET;
		stm_addr.sin_port = htons(target_port);
		stm_addr.sin_addr.s_addr = inet_addr(target_ip);

		rclcpp::QoS qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
		qos_profile.best_effort();
		qos_profile.durability_volatile();

		sub = this -> create_subscription<can_packet::msg::CanPacket>(
			"can_tx_line",
			qos_profile,
			std::bind(&sub_to_can::sub_callback, this, std::placeholders::_1)
		);

		can_packet::msg::CanPacket packet;

		packet.id = 0x200;

		memset(packet.data.data(), 0, sizeof(packet.data));

		packet.data[0] = 0x6f;

		uint8_t tx_data[68];

		encode_can_to_serial(packet, tx_data);

		ssize_t err = sendto(sock, tx_data, 68, 0, reinterpret_cast<sockaddr*>(&stm_addr), sizeof(stm_addr));



	}

	~sub_to_can(){
		close(sock);
	}

};


int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);

    auto node = std::make_shared<sub_to_can>("192.168.1.10", 6000);
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();

    rclcpp::shutdown();

	return 0;
}