import sys
import numpy as np
from PyQt5.QtWidgets import QApplication, QTextEdit, QMainWindow, QLabel, QSlider, QPushButton, QWidget, QLineEdit
from PyQt5.QtCore import Qt, QTimer
import pyqtgraph as pg
from collections import deque
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSDurabilityPolicy

from can_packet.msg import CanPacket


import struct








'''
topic入力欄2個
topic反映ボタン

ゲインテキスト＋スライダー 3個セット
ゲイン反映ボタン

plotするホーム2個

目標値 出力値 plot

入力値 plot

デバッグログ出力ターミナル

'''







class TuningModule(QMainWindow):
    def __init__(self):
        
        super().__init__()
        
        self.node = RosModule()
        
        
        self.tx_id_num = 0
        self.rx_id_num = 0
        
        self.setWindowTitle("Parameter Tuning")
        self.setGeometry(200, 200, 1600, 900)
        
        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)
        
        
        
        
        
        # id 入力欄
        self.tx_id = QLineEdit(self.central_widget)
        self.tx_id.setPlaceholderText("tx id")
        self.tx_id.setGeometry(50, 50, 200, 30)
            
        self.rx_id = QLineEdit(self.central_widget)
        self.rx_id.setPlaceholderText("rx id")
        self.rx_id.setGeometry(300, 50, 200, 30)
        
        self.set_id_button = QPushButton("set id", self.central_widget)
        self.set_id_button.setGeometry(550, 50, 100, 30)
        self.set_id_button.clicked.connect(self.update_id)
        
        
        
        
        
        # ゲイン入力欄
        self.slider_p = QSlider(Qt.Horizontal, self.central_widget)
        self.slider_p.setGeometry(150, 150, 400, 30)
        self.slider_p.setRange(0, 1000)
        self.slider_p.valueChanged.connect(self.update_slider_p)
        
        self.slider_i = QSlider(Qt.Horizontal, self.central_widget)
        self.slider_i.setGeometry(150, 200, 400, 30)
        self.slider_i.setRange(0, 1000)
        self.slider_i.valueChanged.connect(self.update_slider_i)
        
        self.slider_d = QSlider(Qt.Horizontal, self.central_widget)
        self.slider_d.setGeometry(150, 250, 400, 30)
        self.slider_d.setRange(0, 1000)
        self.slider_d.valueChanged.connect(self.update_slider_d)
        
        self.slider_label_p = QLabel("Kp : 0.000", self.central_widget)
        self.slider_label_p.setGeometry(50, 150, 100, 30)
        
        self.slider_label_i = QLabel("Ki : 0.000", self.central_widget)
        self.slider_label_i.setGeometry(50, 200, 100, 30)
        
        self.slider_label_d = QLabel("Kd : 0.000", self.central_widget)
        self.slider_label_d.setGeometry(50, 250, 100, 30)
        
        self.pram_set_button = QPushButton("set", self.central_widget)
        self.pram_set_button.setGeometry(300, 300, 100, 30)
        self.pram_set_button.clicked.connect(self.update_set_button)
        
        
        
        
        
        # データプロット
        self.plot_wid_0 = pg.PlotWidget(self.central_widget)
        self.plot_wid_0.setGeometry(700, 100, 800, 300)
        
        self.setpoint_plot = self.plot_wid_0.plot(pen = 'c')
        self.setpoint_buf = deque(maxlen = 1000)
        self.setpoint_buf.extend([0] * 1000)
        
        self.measuredvalue_plot = self.plot_wid_0.plot(pen = 'g')
        self.measuredvalue_buf = deque(maxlen = 1000)
        self.measuredvalue_buf.extend([0] * 1000)
        
        self.plot_wid_1 = pg.PlotWidget(self.central_widget)
        self.plot_wid_1.setGeometry(700, 450, 800, 300)
        
        self.inputvalue_plot = self.plot_wid_1.plot(pen = 'm')
        self.inputvalue_buf = deque(maxlen = 1000)
        self.inputvalue_buf.extend([0] * 1000)
        
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_plot)
        self.timer.start(10)
        
        
        
        
        # ターミナル
        self.log_terminal = QTextEdit(self.central_widget)
        self.log_terminal.setGeometry(50, 450, 600, 300)
        self.log_terminal.setReadOnly(True)
        
        
        self.log_message("Initializing TuningModule...")  # 初期化時
        
        
        
        
        
    def log_message(self, message):
        self.log_terminal.append(message)
        
       
    def update_plot(self):
        
        this_setpoint = struct.unpack('<f', bytes([
            self.node.last_msg.data[0],
            self.node.last_msg.data[1],
            self.node.last_msg.data[2],
            self.node.last_msg.data[3]
        ]))[0]
        this_measuredvalue = struct.unpack('<f', bytes([
            self.node.last_msg.data[4],
            self.node.last_msg.data[5],
            self.node.last_msg.data[6],
            self.node.last_msg.data[7]
        ]))[0]
        this_inputvalue = struct.unpack('<f', bytes([
            self.node.last_msg.data[8],
            self.node.last_msg.data[9],
            self.node.last_msg.data[10],
            self.node.last_msg.data[11]
        ]))[0]
        
        self.setpoint_buf.append(this_setpoint)
        self.setpoint_plot.setData(np.array(self.setpoint_buf))
        
        self.measuredvalue_buf.append(this_measuredvalue)
        self.measuredvalue_plot.setData(np.array(self.measuredvalue_buf))
        
        self.inputvalue_buf.append(this_inputvalue)
        self.inputvalue_plot.setData(np.array(self.inputvalue_buf))
        
    
    def update_set_button(self):
        
        kp = self.slider_p.value() / 1000.0
        ki = self.slider_i.value() / 1000.0
        kd = self.slider_d.value() / 1000.0
        
        kp_array = struct.pack('<f', kp)
        ki_array = struct.pack('<f', ki)
        kd_array = struct.pack('<f', kd)
        
        msg = CanPacket()
        
        msg.id = self.tx_id_num
        
        msg.data[0] = kp_array[0]
        msg.data[1] = kp_array[1]
        msg.data[2] = kp_array[2]
        msg.data[3] = kp_array[3]
        
        msg.data[4] = ki_array[0]
        msg.data[5] = ki_array[1]
        msg.data[6] = ki_array[2]
        msg.data[7] = ki_array[3]
        
        msg.data[8] = kd_array[0]
        msg.data[9] = kd_array[1]
        msg.data[10] = kd_array[2]
        msg.data[11] = kd_array[3]
        
        self.node.publish(msg)
        
        self.node.get_logger().info(f"gain kp : {kp}  ki : {ki}  kd : {kd}")
                
        self.log_message(f"Publishing message: kp={kp}, ki={ki}, kd={kd}")  # メッセージ送信時
        
    
    def update_id(self):
        tx_txt = self.tx_id.text()
        rx_txt = self.rx_id.text()
        try :
            self.tx_id_num = int(tx_txt, 16)
            self.rx_id_num = int(rx_txt, 16)
            self.node.set_id(self.rx_id_num)
            self.log_message(f"Set TX ID: {self.tx_id_num} (hex: {tx_txt})")
            self.log_message(f"Set RX ID: {self.rx_id_num} (hex: {rx_txt})")
            
        except ValueError:
            self.log_message("IDは16進数で入力してください（例: 1ff）")
            self.node.get_logger().info("IDは16進数で入力してください（例: 1ff）")
        
        
    def update_slider_p(self, value):
        kp = value / 1000.0
        self.slider_label_p.setText(f"Kp : {kp:.5f}")
        
        
    def update_slider_i(self, value):
        ki = value / 1000.0
        self.slider_label_i.setText(f"Ki : {ki:.5f}")
        
    
    def update_slider_d(self, value):
        kd = value / 1000.0
        self.slider_label_d.setText(f"Kd : {kd:.5f}")






class RosModule(Node):
    
    def __init__(self):
        super().__init__('pid_module')
        self.get_logger().info("pid module started")
        
        qos_profile = QoSProfile(
            depth = 10,
            reliability = QoSReliabilityPolicy.BEST_EFFORT,
            durability = QoSDurabilityPolicy.VOLATILE
        )        
        self.pub = self.create_publisher(CanPacket, 'can_tx_line', qos_profile)
        self.sub = self.create_subscription(CanPacket, 'can_rx_line', self.sub_callback, qos_profile)
        
        self.rx_id_mask = 0
        
        self.last_msg = CanPacket()
        
        
    def set_id(self, rx_id):
        
        self.rx_id_mask = rx_id
        self.get_logger().info(f'rx id mask is changed : {self.rx_id_mask}')
    
    def publish(self, msg):
        if self.pub == None:
            self.get_logger().info("pub setting is not found")
            
        else :
            self.pub.publish(msg)
        
    def sub_callback(self, msg):
        self.get_logger().info(f"sub id is {msg.id:x}")
        if msg.id == self.rx_id_mask:
            self.last_msg = msg
        
    def get_last_msg(self):
        return self.last_msg        
        
        





def main():
    import sys
    import rclpy

    rclpy.init()

    app = QApplication(sys.argv)
    gui = TuningModule()
    gui.show()

    # QTimerでrclpy.spin_onceを定期的に呼ぶ
    timer = QTimer()
    timer.timeout.connect(lambda: rclpy.spin_once(gui.node, timeout_sec=0))
    timer.start(10)  # 10msごとにspin_once

    sys.exit(app.exec_())

    rclpy.shutdown()
    


if __name__ == "__main__":
    main()