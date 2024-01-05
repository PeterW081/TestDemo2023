set(PROJECT_NAME "TestDemo2023_GrpcService")
set(CMAKE_VERSION "3.24")
##-
option(OPT_IS_BUILD_CLIENT "" OFF)
option(OPT_IS_BUILD_SERVER "" OFF)
option(OPT_IS_BUILD_GTEST "" OFF)
option(OPT_HOW_ENABLE_GRPC_CLIENT "" BOTH)  # BOTH、ONLY_RAW、ONLY_QT
##-
cmake_minimum_required(VERSION "${CMAKE_VERSION}")
if("${OPT_IS_BUILD_SERVER}")
  set(OPT_HOW_ENABLE_GRPC_CLIENT "ONLY_RAW")
endif()
if(NOT "${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH|ONLY_RAW|ONLY_QT)$")
  message(FATAL_ERROR "OPT_HOW_ENABLE_GRPC_CLIENT is \"${OPT_HOW_ENABLE_GRPC_CLIENT}\"")
endif()
##- FIXME
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH)$")
  set(OPT_HOW_ENABLE_GRPC_CLIENT "ONLY_RAW")
endif()


###
cmake_minimum_required(VERSION "${CMAKE_VERSION}")
project("${PROJECT_NAME}")
##-
set(CMAKE_CXX_STANDARD 20)

###
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH|ONLY_RAW)$")
  include("${PROJECT_SOURCE_DIR}/subunit_grpc_cmake/grpc_common.cmake")
  include("${PROJECT_SOURCE_DIR}/subunit_grpc_cmake/grpc_plugin_protobuf.cmake")
endif()

###
find_package(QT NAMES Qt6)

###
add_compile_definitions(
  MACRO_GRPC_SERVICE_URL="127.0.0.1:50051"
)
##-
add_subdirectory("${PROJECT_SOURCE_DIR}/subunit_grpc_lib_protobuf_pigpio")
if("${OPT_IS_BUILD_CLIENT}")
  add_subdirectory("${PROJECT_SOURCE_DIR}/subunit_grpc_exec_client")
endif()
if("${OPT_IS_BUILD_SERVER}")
  add_subdirectory("${PROJECT_SOURCE_DIR}/subunit_grpc_exec_server")
endif()
