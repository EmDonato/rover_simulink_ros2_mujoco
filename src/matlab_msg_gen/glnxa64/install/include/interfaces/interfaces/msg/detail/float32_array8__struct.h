// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/Float32Array8.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "interfaces/msg/float32_array8.h"


#ifndef INTERFACES__MSG__DETAIL__FLOAT32_ARRAY8__STRUCT_H_
#define INTERFACES__MSG__DETAIL__FLOAT32_ARRAY8__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Float32Array8 in the package interfaces.
typedef struct interfaces__msg__Float32Array8
{
  float data[8];
} interfaces__msg__Float32Array8;

// Struct for a sequence of interfaces__msg__Float32Array8.
typedef struct interfaces__msg__Float32Array8__Sequence
{
  interfaces__msg__Float32Array8 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__Float32Array8__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__FLOAT32_ARRAY8__STRUCT_H_
