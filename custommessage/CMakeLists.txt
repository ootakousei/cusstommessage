cmake_minimum_required(VERSION 3.8)
project(custommessage)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 必要な依存パッケージ
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# メッセージ生成
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/UnityMessage.msg"
  DEPENDENCIES std_msgs
)

# 他パッケージが依存できるようにエクスポート
ament_export_dependencies(rosidl_default_runtime std_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
