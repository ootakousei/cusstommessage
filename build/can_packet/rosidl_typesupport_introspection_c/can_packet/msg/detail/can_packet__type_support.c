// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from can_packet:msg/CanPacket.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "can_packet/msg/detail/can_packet__rosidl_typesupport_introspection_c.h"
#include "can_packet/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "can_packet/msg/detail/can_packet__functions.h"
#include "can_packet/msg/detail/can_packet__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  can_packet__msg__CanPacket__init(message_memory);
}

void can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_fini_function(void * message_memory)
{
  can_packet__msg__CanPacket__fini(message_memory);
}

size_t can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__size_function__CanPacket__data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 32;
}

const void * can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__get_const_function__CanPacket__data(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__get_function__CanPacket__data(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__fetch_function__CanPacket__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__get_const_function__CanPacket__data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__assign_function__CanPacket__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__get_function__CanPacket__data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_message_member_array[2] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(can_packet__msg__CanPacket, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    32,  // array size
    false,  // is upper bound
    offsetof(can_packet__msg__CanPacket, data),  // bytes offset in struct
    NULL,  // default value
    can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__size_function__CanPacket__data,  // size() function pointer
    can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__get_const_function__CanPacket__data,  // get_const(index) function pointer
    can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__get_function__CanPacket__data,  // get(index) function pointer
    can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__fetch_function__CanPacket__data,  // fetch(index, &value) function pointer
    can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__assign_function__CanPacket__data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_message_members = {
  "can_packet__msg",  // message namespace
  "CanPacket",  // message name
  2,  // number of fields
  sizeof(can_packet__msg__CanPacket),
  can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_message_member_array,  // message members
  can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_init_function,  // function to initialize message memory (memory has to be allocated)
  can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_message_type_support_handle = {
  0,
  &can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_can_packet
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, can_packet, msg, CanPacket)() {
  if (!can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_message_type_support_handle.typesupport_identifier) {
    can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &can_packet__msg__CanPacket__rosidl_typesupport_introspection_c__CanPacket_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
