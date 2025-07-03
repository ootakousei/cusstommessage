import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/roxy/2025_ros2/KanNon0618/install/pid_tuner'
