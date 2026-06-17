// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/Float32Array8.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "interfaces/msg/float32_array8.hpp"


#ifndef INTERFACES__MSG__DETAIL__FLOAT32_ARRAY8__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__FLOAT32_ARRAY8__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/float32_array8__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_Float32Array8_data
{
public:
  Init_Float32Array8_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::msg::Float32Array8 data(::interfaces::msg::Float32Array8::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::Float32Array8 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::Float32Array8>()
{
  return interfaces::msg::builder::Init_Float32Array8_data();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__FLOAT32_ARRAY8__BUILDER_HPP_
