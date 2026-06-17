// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/Float32Array12.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "interfaces/msg/float32_array12.h"


#ifndef INTERFACES__MSG__DETAIL__FLOAT32_ARRAY12__STRUCT_H_
#define INTERFACES__MSG__DETAIL__FLOAT32_ARRAY12__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Float32Array12 in the package interfaces.
typedef struct interfaces__msg__Float32Array12
{
  float data[12];
} interfaces__msg__Float32Array12;

// Struct for a sequence of interfaces__msg__Float32Array12.
typedef struct interfaces__msg__Float32Array12__Sequence
{
  interfaces__msg__Float32Array12 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__Float32Array12__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__FLOAT32_ARRAY12__STRUCT_H_
