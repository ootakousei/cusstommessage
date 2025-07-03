// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from can_packet:msg/CanPacket.idl
// generated code does not contain a copyright notice

#ifndef CAN_PACKET__MSG__DETAIL__CAN_PACKET__STRUCT_HPP_
#define CAN_PACKET__MSG__DETAIL__CAN_PACKET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__can_packet__msg__CanPacket __attribute__((deprecated))
#else
# define DEPRECATED__can_packet__msg__CanPacket __declspec(deprecated)
#endif

namespace can_packet
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CanPacket_
{
  using Type = CanPacket_<ContainerAllocator>;

  explicit CanPacket_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      std::fill<typename std::array<uint8_t, 32>::iterator, uint8_t>(this->data.begin(), this->data.end(), 0);
    }
  }

  explicit CanPacket_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : data(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      std::fill<typename std::array<uint8_t, 32>::iterator, uint8_t>(this->data.begin(), this->data.end(), 0);
    }
  }

  // field types and members
  using _id_type =
    uint16_t;
  _id_type id;
  using _data_type =
    std::array<uint8_t, 32>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__id(
    const uint16_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__data(
    const std::array<uint8_t, 32> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    can_packet::msg::CanPacket_<ContainerAllocator> *;
  using ConstRawPtr =
    const can_packet::msg::CanPacket_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<can_packet::msg::CanPacket_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<can_packet::msg::CanPacket_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      can_packet::msg::CanPacket_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<can_packet::msg::CanPacket_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      can_packet::msg::CanPacket_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<can_packet::msg::CanPacket_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<can_packet::msg::CanPacket_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<can_packet::msg::CanPacket_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__can_packet__msg__CanPacket
    std::shared_ptr<can_packet::msg::CanPacket_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__can_packet__msg__CanPacket
    std::shared_ptr<can_packet::msg::CanPacket_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CanPacket_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const CanPacket_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CanPacket_

// alias to use template instance with default allocator
using CanPacket =
  can_packet::msg::CanPacket_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace can_packet

#endif  // CAN_PACKET__MSG__DETAIL__CAN_PACKET__STRUCT_HPP_
