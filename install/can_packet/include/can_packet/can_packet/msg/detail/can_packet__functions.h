// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from can_packet:msg/CanPacket.idl
// generated code does not contain a copyright notice

#ifndef CAN_PACKET__MSG__DETAIL__CAN_PACKET__FUNCTIONS_H_
#define CAN_PACKET__MSG__DETAIL__CAN_PACKET__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "can_packet/msg/rosidl_generator_c__visibility_control.h"

#include "can_packet/msg/detail/can_packet__struct.h"

/// Initialize msg/CanPacket message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * can_packet__msg__CanPacket
 * )) before or use
 * can_packet__msg__CanPacket__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
bool
can_packet__msg__CanPacket__init(can_packet__msg__CanPacket * msg);

/// Finalize msg/CanPacket message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
void
can_packet__msg__CanPacket__fini(can_packet__msg__CanPacket * msg);

/// Create msg/CanPacket message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * can_packet__msg__CanPacket__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
can_packet__msg__CanPacket *
can_packet__msg__CanPacket__create();

/// Destroy msg/CanPacket message.
/**
 * It calls
 * can_packet__msg__CanPacket__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
void
can_packet__msg__CanPacket__destroy(can_packet__msg__CanPacket * msg);

/// Check for msg/CanPacket message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
bool
can_packet__msg__CanPacket__are_equal(const can_packet__msg__CanPacket * lhs, const can_packet__msg__CanPacket * rhs);

/// Copy a msg/CanPacket message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
bool
can_packet__msg__CanPacket__copy(
  const can_packet__msg__CanPacket * input,
  can_packet__msg__CanPacket * output);

/// Initialize array of msg/CanPacket messages.
/**
 * It allocates the memory for the number of elements and calls
 * can_packet__msg__CanPacket__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
bool
can_packet__msg__CanPacket__Sequence__init(can_packet__msg__CanPacket__Sequence * array, size_t size);

/// Finalize array of msg/CanPacket messages.
/**
 * It calls
 * can_packet__msg__CanPacket__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
void
can_packet__msg__CanPacket__Sequence__fini(can_packet__msg__CanPacket__Sequence * array);

/// Create array of msg/CanPacket messages.
/**
 * It allocates the memory for the array and calls
 * can_packet__msg__CanPacket__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
can_packet__msg__CanPacket__Sequence *
can_packet__msg__CanPacket__Sequence__create(size_t size);

/// Destroy array of msg/CanPacket messages.
/**
 * It calls
 * can_packet__msg__CanPacket__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
void
can_packet__msg__CanPacket__Sequence__destroy(can_packet__msg__CanPacket__Sequence * array);

/// Check for msg/CanPacket message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
bool
can_packet__msg__CanPacket__Sequence__are_equal(const can_packet__msg__CanPacket__Sequence * lhs, const can_packet__msg__CanPacket__Sequence * rhs);

/// Copy an array of msg/CanPacket messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_can_packet
bool
can_packet__msg__CanPacket__Sequence__copy(
  const can_packet__msg__CanPacket__Sequence * input,
  can_packet__msg__CanPacket__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // CAN_PACKET__MSG__DETAIL__CAN_PACKET__FUNCTIONS_H_
