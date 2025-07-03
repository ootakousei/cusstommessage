cmake_minimum_required(VERSION 3.8)
project(my_cpp_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
#find_package(cartographer_ros REQUIRED)
#find_package(cartographer REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
#find_package(nav_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
#find_package(custom_message_robot REQUIRED)

find_package(can_packet REQUIRED)

# 依存関係をエクスポート


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()
# launch ファイルをインストール
install(DIRECTORY
  DESTINATION share/${PROJECT_NAME}/
)



# 設定ファイル (config) をインストール
#install(DIRECTORY
 # config
 # DESTINATION share/${PROJECT_NAME}/
#)

# Python スクリプトをインストール
install(PROGRAMS
  scripts/udptotopic.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
