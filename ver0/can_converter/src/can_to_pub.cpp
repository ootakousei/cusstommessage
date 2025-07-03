#include "rclcpp/rclcpp.hpp"
#include "can_packet/msg/can_packet.hpp"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "can_converter/data_conversion.hpp"


class can_to_pub : public rclcpp::Node
{
private:

    rclcpp::Publisher<can_packet::msg::CanPacket>::SharedPtr pub;

    int sock;
    sockaddr_in this_addr;

    std::thread receive_thread;

    uint8_t udp_preserved_data[256] = {};
    size_t packet_tail = 0;


    void receive_fn(){

        uint8_t buf[256];

        while(true){

            // RCLCPP_INFO(this -> get_logger(), "receive failed");

            ssize_t n = recv(sock, buf, sizeof(buf), 0);
            //RCLCPP_INFO(this -> get_logger(), "receive %x", buf);
            

            if (n < 0) {
                RCLCPP_INFO(this -> get_logger(), "receive failed");
            }
            else{
                //RCLCPP_INFO(this -> get_logger(), "receive %x", buf);

                for(size_t i = 0; i < n; i++){

                    if(buf[i] == '\0'){
                        //RCLCPP_INFO(this -> get_logger(), "null came");
                        udp_preserved_data[packet_tail] = '\0';
                        packet_tail ++;

                        if(packet_tail == 68){
                            can_packet::msg::CanPacket tx_packet;

                            decode_serial_to_can(udp_preserved_data, tx_packet);

                            pub -> publish(tx_packet);

                            memset(udp_preserved_data, 0, sizeof(udp_preserved_data));
                            packet_tail = 0;

                            RCLCPP_INFO(this -> get_logger(), "can to pub id is %x", tx_packet.id);
                        }
                        else{
                            memset(udp_preserved_data, 0, sizeof(udp_preserved_data));
                            packet_tail = 0;

                            RCLCPP_INFO(this -> get_logger(), "packet error");
                        }

                    }
                    else{
                        udp_preserved_data[packet_tail] = buf[i];
                        packet_tail ++;
                        
                    }     

                }



            }
            

        }

    }



public:
    can_to_pub(uint16_t receive_port) : Node("can_to_pub"){

        RCLCPP_INFO(this -> get_logger(), "started");
        
        rclcpp::QoS qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        qos_profile.best_effort();
        qos_profile.durability_volatile();

        pub = this -> create_publisher<can_packet::msg::CanPacket>("can_rx_line", qos_profile);

        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if(sock < 0){
            RCLCPP_INFO(this -> get_logger(), "socket error");
        }
        std::memset(&this_addr, 0, sizeof(this_addr));
        this_addr.sin_family = AF_INET;
        this_addr.sin_port = htons(receive_port);
        this_addr.sin_addr.s_addr = INADDR_ANY;
        bind(sock, (struct sockaddr*)&this_addr, sizeof(this_addr));

        receive_thread = std::thread(&can_to_pub::receive_fn, this);
    
    }

    ~can_to_pub(){
        close(sock);
    }

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<can_to_pub>(5000);
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();

    //rclcpp::spin(std::make_shared<can_to_pub>(5000)); // 変更

    rclcpp::shutdown();

    return 0;
}