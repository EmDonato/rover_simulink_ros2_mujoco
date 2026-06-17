cmake_minimum_required(VERSION 3.8)
project(ettorone_mujoco_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# =====================
# DEPENDENCIES
# =====================
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(glfw3 REQUIRED)
find_package(interfaces REQUIRED) 
# =====================
# EXECUTABLE
# =====================
add_executable(mj_ros2_ettorone
  src/main.cpp
  src/mj_ettorone_node.cpp
)

# =====================
# MUJOCO
# =====================
set(MUJOCO_PATH $ENV{MUJOCO_PATH})

if(NOT DEFINED ENV{MUJOCO_PATH})
  message(FATAL_ERROR "MUJOCO_PATH is not set")
endif()

# include headers
target_include_directories(mj_ros2_ettorone PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${MUJOCO_PATH}/include
)

# link libraries
target_link_directories(mj_ros2_ettorone PUBLIC
  ${MUJOCO_PATH}/lib
)

target_link_libraries(mj_ros2_ettorone
  mujoco
  glfw
)

set_target_properties(mj_ros2_ettorone PROPERTIES
  BUILD_RPATH ${MUJOCO_PATH}/lib
  INSTALL_RPATH ${MUJOCO_PATH}/lib
)

# =====================
# ROS2 DEPENDENCIES
# =====================
ament_target_dependencies(mj_ros2_ettorone
  rclcpp
  std_msgs
  tf2
  geometry_msgs
  interfaces
)

# =====================
# INSTALL
# =====================
install(TARGETS mj_ros2_ettorone
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

# =====================
# TESTING
# =====================
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()