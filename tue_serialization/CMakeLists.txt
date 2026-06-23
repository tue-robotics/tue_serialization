cmake_minimum_required(VERSION 3.5)
project(tue_serialization)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Werror=all)
  add_compile_options(-Wextra -Werror=extra)
endif()

find_package(ament_cmake REQUIRED)

add_library(${PROJECT_NAME} SHARED
  src/conversions.cpp
  src/filesystem.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/
  DESTINATION include
)

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)

if(BUILD_TESTING)
  find_package(tue_lint_config REQUIRED)
  find_package(ament_cmake_clang_format REQUIRED)
  find_package(ament_cmake_clang_tidy REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(ament_cmake_lint_cmake REQUIRED)
  find_package(ament_cmake_xmllint REQUIRED)

  ament_clang_format(
    CONFIG_FILE ${tue_lint_config_DIR}/../config/.clang-format
    --clang-format-version=21
  )
  ament_clang_tidy(
    CONFIG_FILE ${tue_lint_config_DIR}/../config/.clang-tidy
    --clang-tidy-version=21
    ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}/compile_commands.json)
  ament_lint_cmake(MAX_LINE_LENGTH 120 "--filter=
    +convention/filename,
    +linelength,
    +package/consistency,
    +package/stdargs,
    +readability/logic,
    +readability/mixedcase,
    +readability/wonkycase,
    +syntax,+whitespace/eol,
    +whitespace/extra,
    +whitespace/indent,
    +whitespace/mismatch,
    +whitespace/newline,
    +whitespace/tabs"
  )
  ament_xmllint(MAX_LINE_LENGTH 120)

  ament_add_gtest(${PROJECT_NAME}-test test/test_${PROJECT_NAME}.cpp)
  target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
endif()

ament_package()
