cmake_minimum_required(VERSION 2.8.3)
project(tue_serialization)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  std_msgs
)

add_message_files(
  FILES
  Binary.msg
)

add_service_files(
  FILES
  BinaryService.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES tue_serialization
  CATKIN_DEPENDS message_runtime std_msgs
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(tue_serialization
  src/conversions.cpp
  src/filesystem.cpp
)

add_executable(test_serialization test/test_serialization.cpp)
target_link_libraries(test_serialization tue_serialization)

add_dependencies(tue_serialization ${${PROJECT_NAME}_EXPORTED_TARGETS})
add_dependencies(test_serialization ${${PROJECT_NAME}_EXPORTED_TARGETS})

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_tue_serialization.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()
