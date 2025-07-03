cmake_minimum_required(VERSION 3.8)
project(can_converter)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)


find_package(rclcpp REQUIRED)
find_package(can_packet REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)



include_directories(
  include
)

add_executable(sub_to_can_node src/sub_to_can.cpp)
add_executable(can_to_pub_node src/can_to_pub.cpp)
add_executable(sub_to_usb_node src/sub_to_usb.cpp)
add_executable(usb_to_pub_node src/usb_to_pub.cpp)
add_executable(ros2_usb_node src/usb_pub_sub.cpp)



target_link_libraries(sub_to_usb_node
  Boost::system
)

target_link_libraries(usb_to_pub_node
  Boost::system
)

target_link_libraries(ros2_usb_node
  Boost::system
)



ament_target_dependencies(sub_to_can_node rclcpp can_packet) 
ament_target_dependencies(can_to_pub_node rclcpp can_packet)
ament_target_dependencies(sub_to_usb_node rclcpp can_packet) 
ament_target_dependencies(usb_to_pub_node rclcpp can_packet)
ament_target_dependencies(ros2_usb_node rclcpp can_packet)


install(
  TARGETS
  sub_to_can_node
  can_to_pub_node
  sub_to_usb_node
  usb_to_pub_node
  ros2_usb_node
  DESTINATION lib/${PROJECT_NAME}
)




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

ament_package()
