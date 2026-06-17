// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from interfaces:msg/Float32Array12.idl
// generated code does not contain a copyright notice

#include "interfaces/msg/detail/float32_array12__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_interfaces
const rosidl_type_hash_t *
interfaces__msg__Float32Array12__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xb1, 0xaa, 0xad, 0x7d, 0x9c, 0x13, 0xd9, 0x2e,
      0xd3, 0xd5, 0xe4, 0x56, 0xad, 0x18, 0x8f, 0x1f,
      0xa1, 0x63, 0x4d, 0xb1, 0x61, 0x68, 0x3c, 0x22,
      0x30, 0x06, 0x91, 0xa6, 0xc6, 0xf7, 0xc9, 0x79,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char interfaces__msg__Float32Array12__TYPE_NAME[] = "interfaces/msg/Float32Array12";

// Define type names, field names, and default values
static char interfaces__msg__Float32Array12__FIELD_NAME__data[] = "data";

static rosidl_runtime_c__type_description__Field interfaces__msg__Float32Array12__FIELDS[] = {
  {
    {interfaces__msg__Float32Array12__FIELD_NAME__data, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      12,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
interfaces__msg__Float32Array12__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {interfaces__msg__Float32Array12__TYPE_NAME, 29, 29},
      {interfaces__msg__Float32Array12__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32[12] data";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
interfaces__msg__Float32Array12__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {interfaces__msg__Float32Array12__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 16, 16},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
interfaces__msg__Float32Array12__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *interfaces__msg__Float32Array12__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
