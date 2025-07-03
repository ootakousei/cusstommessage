from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
def generate_launch_description():
    return LaunchDescription([
        
    #    Node(
     #       package='etc_user',
     #       executable='etc_sender',
     #       name='etc_sender'
     #   ),
        
       # Node(
        #    package='master_sample',
        #    executable='master_node',
        #    name='master_node'
        #),
        Node(
            package="my_cpp_package",
            executable="udptotopic.py",  # Pythonスクリプトを直接指定
            name="udptotopic",
            output="screen"
        ),
        Node(
            package="can_converter",
            executable="sub_to_can_node",  # Pythonスクリプトを直接指定
            name="can_converter1",
            output="screen"
        ),
        Node(
            package="can_converter",
            executable="can_to_pub_node",  # Pythonスクリプトを直接指定
            name="can_converter2",
            output="screen"
        )
    ])
