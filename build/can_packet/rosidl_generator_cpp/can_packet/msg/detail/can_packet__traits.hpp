// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from can_packet:msg/CanPacket.idl
// generated code does not contain a copyright notice

#ifndef CAN_PACKET__MSG__DETAIL__CAN_PACKET__TRAITS_HPP_
#define CAN_PACKET__MSG__DETAIL__CAN_PACKET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "can_packet/msg/detail/can_packet__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace can_packet
{

namespace msg
{

inline void to_flow_style_yaml(
  const CanPacket & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CanPacket & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CanPacket & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace can_packet

namespace rosidl_generator_traits
{

[[deprecated("use can_packet::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const can_packet::msg::CanPacket & msg,
  std::ostream & out, size_t indentation = 0)
{
  can_packet::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use can_packet::msg::to_yaml() instead")]]
inline std::string to_yaml(const can_packet::msg::CanPacket & msg)
{
  return can_packet::msg::to_yaml(msg);
}

template<>
inline const char * data_type<can_packet::msg::CanPacket>()
{
  return "can_packet::msg::CanPacket";
}

template<>
inline const char * name<can_packet::msg::CanPacket>()
{
  return "can_packet/msg/CanPacket";
}

template<>
struct has_fixed_size<can_packet::msg::CanPacket>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<can_packet::msg::CanPacket>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<can_packet::msg::CanPacket>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAN_PACKET__MSG__DETAIL__CAN_PACKET__TRAITS_HPP_
