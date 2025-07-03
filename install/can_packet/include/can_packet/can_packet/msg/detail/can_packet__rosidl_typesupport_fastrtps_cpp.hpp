// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from can_packet:msg/CanPacket.idl
// generated code does not contain a copyright notice

#ifndef CAN_PACKET__MSG__DETAIL__CAN_PACKET__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define CAN_PACKET__MSG__DETAIL__CAN_PACKET__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "can_packet/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "can_packet/msg/detail/can_packet__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace can_packet
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_can_packet
cdr_serialize(
  const can_packet::msg::CanPacket & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_can_packet
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  can_packet::msg::CanPacket & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_can_packet
get_serialized_size(
  const can_packet::msg::CanPacket & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_can_packet
max_serialized_size_CanPacket(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace can_packet

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_can_packet
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, can_packet, msg, CanPacket)();

#ifdef __cplusplus
}
#endif

#endif  // CAN_PACKET__MSG__DETAIL__CAN_PACKET__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
