set(PROJECT_NAME "TestDemo2023_GrpcService")
##-
option(OPT_IS_BUILD_CLIENT "" OFF)
option(OPT_IS_BUILD_SERVER "" OFF)
option(OPT_IS_BUILD_GTEST "" OFF)

###
cmake_minimum_required(VERSION 3.12)
project("${PROJECT_NAME}")
##-
set(CMAKE_CXX_STANDARD 20)
##-
add_compile_definitions(
  MACRO_GRPC_SERVICE_URL="127.0.0.1:50051"
)

###
include("${PROJECT_SOURCE_DIR}/subunit_grpc_cmake/grpc_common.cmake")
include("${PROJECT_SOURCE_DIR}/subunit_grpc_cmake/grpc_plugin_protobuf.cmake")
add_subdirectory("${PROJECT_SOURCE_DIR}/subunit_grpc_lib_protobuf_pigpio")
if("${OPT_IS_BUILD_CLIENT}")
  add_subdirectory("${PROJECT_SOURCE_DIR}/subunit_grpc_exec_client")
endif()
if("${OPT_IS_BUILD_SERVER}")
  add_subdirectory("${PROJECT_SOURCE_DIR}/subunit_grpc_exec_server")
endif()
