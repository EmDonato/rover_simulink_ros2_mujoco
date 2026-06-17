// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from interfaces:msg/Float32Array8.idl
// generated code does not contain a copyright notice

#include "interfaces/msg/detail/float32_array8__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_interfaces
const rosidl_type_hash_t *
interfaces__msg__Float32Array8__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x34, 0x44, 0x73, 0x1d, 0xef, 0xd6, 0x76, 0xb6,
      0x97, 0x0c, 0xd9, 0xd0, 0x8b, 0x52, 0xd1, 0x76,
      0x95, 0x51, 0x53, 0xb4, 0x5a, 0x4e, 0x55, 0xda,
      0x66, 0x3f, 0xcb, 0xa3, 0x68, 0x92, 0xc4, 0x8f,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char interfaces__msg__Float32Array8__TYPE_NAME[] = "interfaces/msg/Float32Array8";

// Define type names, field names, and default values
static char interfaces__msg__Float32Array8__FIELD_NAME__data[] = "data";

static rosidl_runtime_c__type_description__Field interfaces__msg__Float32Array8__FIELDS[] = {
  {
    {interfaces__msg__Float32Array8__FIELD_NAME__data, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      8,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
interfaces__msg__Float32Array8__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {interfaces__msg__Float32Array8__TYPE_NAME, 28, 28},
      {interfaces__msg__Float32Array8__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32[8] data";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
interfaces__msg__Float32Array8__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {interfaces__msg__Float32Array8__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 15, 15},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
interfaces__msg__Float32Array8__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *interfaces__msg__Float32Array8__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
