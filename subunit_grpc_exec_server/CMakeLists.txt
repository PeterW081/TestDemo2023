set(PROJECT_NAME "TestDemo2023_Grpc_Server")

###
cmake_minimum_required(VERSION "${CMAKE_VERSION}")
project("${PROJECT_NAME}")

###
file(GLOB_RECURSE CXX_SRC "cxx_src/*.cxx")
add_executable(
  "${PROJECT_NAME}"
  "${CXX_SRC}"
  "${PROJECT_SOURCE_DIR}/cxx_src_main.cxx"
)
target_include_directories(
  "${PROJECT_NAME}" PRIVATE
  "${PROJECT_SOURCE_DIR}/cxx_include"
)
target_link_libraries(
  "${PROJECT_NAME}" PRIVATE
  "${_REFLECTION}"
  "pigpio"
  "grpc_protobuf_pigpio"
)
