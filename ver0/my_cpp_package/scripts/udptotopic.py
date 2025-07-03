#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import socket
import threading
from can_packet.msg import CanPacket
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy
import msgpack
from rclpy.executors import MultiThreadedExecutor
#192.168.11.4
from std_msgs.msg import Int32
import struct
import time
def pack_mixed_data(data_list):
    result = bytearray()
    for val in data_list:
        if isinstance(val, float):
            result.extend(struct.pack('<f', val))
        else:  # bool/int など
            result.append(int(val))
    return bytes(result)

class UdpToRosNode(Node):
    def __init__(self):
        super().__init__('udp_to_ros_node')
        self.qos_profile = QoSProfile(
        depth=10,
        reliability=ReliabilityPolicy.BEST_EFFORT,
        durability=DurabilityPolicy.VOLATILE
        )
        self.start_time = None
        self.testpub = self.create_publisher(String,'tester1',self.qos_profile)
        #self.testsub = self.create_subscription(String,'tester2',self.test_callback,self.qos_profile)
        self.canpub = self.create_publisher(CanPacket, 'can_tx_line', self.qos_profile)
        #self.cansub = self.create_subscription(CanPacket, 'can_rx_line', self.test_callback,self.qos_profile)
       # self.pub = self.create_publisher(Int32, 'debug', self.qos_profile)
        self.i=1
        self.flag=1
        # UDP設定
        self.udp_ip = "0.0.0.0"                                 #受信_0.0.0.0==ANY
        self.udp_port = 60000                                   #受信
        self.sockR = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sockR.bind((self.udp_ip, self.udp_port))
        self.udp_port_test=50000
        self.sockT = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sockT.bind((self.udp_ip, self.udp_port_test))
        self.server_ip = '192.168.11.4'                         #送信先
        self.server_port = 12345                                #送信先
        self.SrcIP = "192.168.11.5"                             # 送信元IP
        self.SrcPort = 60001                                    # 送信元ポート番号
        self.SrcAddr = (self.SrcIP,self.SrcPort)   
        self.sockS = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
        self.message = 0


        self.mecanum=0 # bool
        self.arm1f=0 # bool
        self.arm1p=0 # bool
        self.arm1z0=0 # bool
        self.arm1z90=0 # bool
        self.arm1z180=0 # bool
        self.arm1z=0 # float
        self.arm1x=0 # float
        self.arm1pin=0 # float
        self.arm2f=0 # bool
        self.arm2p=0 # bool
        self.arm2z0=0 # bool
        self.arm2z90=0 # bool
        self.arm2z180=0 # bool
        self.arm2z=0 # float
        self.arm2x=0 # float
        self.arm2pin=0 # float
        self.nang=0#float
        self.nanz=0#float
        self.extend=0#bool
        self.force=0#bool
        self.LX=0 # float
        self.LY=0 # float
        self.RX=0 # float
        self.RY=0 # float


                # UDP受信用スレッドを開始
        self.recv_thread_main = threading.Thread(target=self.udp_receive_loop, daemon=True)
        self.recv_thread_main.start()
        self.get_logger().info(f"UDP受信開始 on port {self.udp_port}")
        self.recv_thread_test = threading.Thread(target=self.testpublish, daemon=True)
        self.recv_thread_test.start()
        #self.tim=self.create_timer(1,self.tim_callback)
       # self.sockR.settimeout(1.0)
       # self.sockT.settimeout(1.0)

       # self.msg = Psimsg()

    def udp_receive_loop(self):
        
        while rclpy.ok():
            data, addr = self.sockR.recvfrom(1024)
            try:
                robo_states = msgpack.unpackb(data, raw=False)
                #self.get_logger().info(f"デコード結果: {robo_states}")
                

                for group in robo_states:
                    for data in group:
                        if isinstance(data, list):
                            if len(data) == 2:
                                name, value = data
                                if name == "mecanum":
                                    self.mecanum = value
                                elif name == "arm1f":
                                    self.arm1f = value
                                elif name == "arm1p":
                                    self.arm1p = value
                                elif name == "arm1z0":
                                    self.arm1z0 = value
                                elif name == "arm1z90":
                                    self.arm1z90 = value
                                elif name == "arm1z180":
                                    self.arm1z180 = value
                                elif name == "arm1z":
                                    self.arm1z = round(value, 2)
                                elif name == "arm1x":
                                    self.arm1x = round(value, 2)
                                elif name == "arm1pin":
                                    self.arm1pin = round(value, 2)
                                elif name == "arm2f":
                                    self.arm2f = value
                                elif name == "arm2p":
                                    self.arm2p = value
                                elif name == "arm2z0":
                                    self.arm2z0 = value
                                elif name == "arm2z90":
                                    self.arm2z90 = value
                                elif name == "arm2z180":
                                    self.arm2z180 = value
                                elif name == "arm2z":
                                    self.arm2z = round(value, 2)
                                elif name == "arm2x":
                                    self.arm2x = round(value, 2)
                                elif name == "arm2pin":
                                    self.arm2pin = round(value, 2)
                                elif name == "nang":
                                    self.nang = round(value, 2)
                                elif name == "nanz":
                                    self.nanz = round(value, 2)
                                elif name == "extend":
                                    self.extend = value
                                elif name == "force":
                                    self.force = value
                                else:
                                    self.get_logger().warn(f"未定義のキー: {name}")
                            elif len(data) == 3:
                                name, x, y = data
                                if name == "LeftStick":
                                    self.LX = round(x, 2)
                                    self.LY = round(y, 2)
                                elif name == "RightStick":
                                    self.RX = round(x, 2)
                                    self.RY = round(y, 2)
                                else:
                                    self.get_logger().warn(f"未定義の3要素データ: {data}")
                            else:
                                self.get_logger().warn(f"形式不明のデータ: {data}")

                # Publish 1つのPsimsgにまとめて送信
                #self.psimsg_pub.publish(self.msg)
                # arm1 に関するデータ
                datae_arm1 = [
                    #float
                    self.arm1z,
                    self.arm1x,
                    self.arm1pin,
                    #bool
                    self.arm1f,
                    self.arm1p,
                    self.arm1z0,
                    self.arm1z90,
                    self.arm1z180
                ]

                # arm2 に関するデータ
                datae_arm2 = [
                    #float
                    self.arm2z,
                    self.arm2x,
                    self.arm2pin,
                    #bool
                    self.arm2f,
                    self.arm2p,
                    self.arm2z0,
                    self.arm2z90,
                    self.arm2z180
                ]

                # その他のデータ（Slider系とround不要、残りの変数のみ）
                datae_other = [
                    #float
                    self.nang,
                    self.nanz,
                    self.LX,
                    self.LY,
                    self.RX,
                    self.RY,
                    #bool
                    self.mecanum,
                    self.extend,
                    self.force,
                ]

                
                
                bin_data = pack_mixed_data(datae_arm1)
                txpacket = CanPacket()
                txpacket.id = 0x100
                for i in range(min(len(bin_data), 32)):
                    txpacket.data[i] = bin_data[i]
                for i in range(len(bin_data), 32):
                    txpacket.data[i] = 0
                self.canpub.publish(txpacket)

                
                bin_data = pack_mixed_data(datae_arm2)
                txpacket = CanPacket()
                txpacket.id = 0x101
                for i in range(min(len(bin_data), 32)):
                    txpacket.data[i] = bin_data[i]
                for i in range(len(bin_data), 32):
                    txpacket.data[i] = 0
                self.canpub.publish(txpacket)

                
                bin_data = pack_mixed_data(datae_other)
                txpacket = CanPacket()
                txpacket.id = 0x102
                for i in range(min(len(bin_data), 32)):
                    txpacket.data[i] = bin_data[i]
                for i in range(len(bin_data), 32):
                    txpacket.data[i] = 0
                self.canpub.publish(txpacket)

            

                #self.get_logger().info(f"mecanum,servo,pinch,shuttle,glab: {self.mecanum,self.servo,self.pinch,self.shuttle,self.glab}")
                #self.get_logger().info(f"lx,ly: {self.LX,self.LY}")
                #self.get_logger().info(f"data: {data}")

                #self.get_logger().info(f"Psimsg送信: {self.msg}")

            except Exception as e:
                self.get_logger().error(f"えらー: {e}")
    def test_callback(self,msg):
            
            data="test"
            self.message = data.encode('utf-8')
            self.sockS.sendto(self.message, (self.server_ip, self.server_port))
            #self.get_logger().info(f"recieved")
            self.start_time=time.time()
    def tim_callback(self):
        while rclpy.ok():
            
            data="test"
            self.message = data.encode('utf-8')
            self.sockS.sendto(self.message, (self.server_ip, self.server_port))
            #self.get_logger().info(f"recieved")
    def testpublish(self):
        while rclpy.ok():
            data, addr = self.sockT.recvfrom(1024)
            #self.get_logger().info(f"a")
           
            
            if data.decode('utf-8')=="test":

                txpacket = CanPacket()
                txpacket.id = 0x100
                for i in range(32):
                    txpacket.data[i] = 0

                self.canpub.publish(txpacket)
                self.get_logger().info(f"time:{time.time()-self.start_time}")
                self.get_logger().info(f"a")
                    

def main(args=None):
    rclpy.init(args=args)
    node = UdpToRosNode()
    executor =MultiThreadedExecutor()
    executor.add_node(node)
    executor.spin()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
