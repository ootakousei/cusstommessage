// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from can_packet:msg/CanPacket.idl
// generated code does not contain a copyright notice

#ifndef CAN_PACKET__MSG__DETAIL__CAN_PACKET__BUILDER_HPP_
#define CAN_PACKET__MSG__DETAIL__CAN_PACKET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "can_packet/msg/detail/can_packet__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace can_packet
{

namespace msg
{

namespace builder
{

class Init_CanPacket_data
{
public:
  explicit Init_CanPacket_data(::can_packet::msg::CanPacket & msg)
  : msg_(msg)
  {}
  ::can_packet::msg::CanPacket data(::can_packet::msg::CanPacket::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::can_packet::msg::CanPacket msg_;
};

class Init_CanPacket_id
{
public:
  Init_CanPacket_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CanPacket_data id(::can_packet::msg::CanPacket::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_CanPacket_data(msg_);
  }

private:
  ::can_packet::msg::CanPacket msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::can_packet::msg::CanPacket>()
{
  return can_packet::msg::builder::Init_CanPacket_id();
}

}  // namespace can_packet

#endif  // CAN_PACKET__MSG__DETAIL__CAN_PACKET__BUILDER_HPP_
