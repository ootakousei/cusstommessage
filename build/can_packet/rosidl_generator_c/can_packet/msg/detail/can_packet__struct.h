// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from can_packet:msg/CanPacket.idl
// generated code does not contain a copyright notice

#ifndef CAN_PACKET__MSG__DETAIL__CAN_PACKET__STRUCT_H_
#define CAN_PACKET__MSG__DETAIL__CAN_PACKET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/CanPacket in the package can_packet.
typedef struct can_packet__msg__CanPacket
{
  uint16_t id;
  uint8_t data[32];
} can_packet__msg__CanPacket;

// Struct for a sequence of can_packet__msg__CanPacket.
typedef struct can_packet__msg__CanPacket__Sequence
{
  can_packet__msg__CanPacket * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} can_packet__msg__CanPacket__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAN_PACKET__MSG__DETAIL__CAN_PACKET__STRUCT_H_
