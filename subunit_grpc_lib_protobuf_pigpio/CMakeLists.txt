set(PROJECT_NAME "grpc_protobuf_pigpio")

###
cmake_minimum_required(VERSION 3.12)
project("${PROJECT_NAME}")
##-
find_package(Threads REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

###
file(GLOB_RECURSE CXX_SRC "cxx_src/*.cxx")
file(GLOB_RECURSE META_PROTO "meta_proto/*.proto")
##-
protobuf_generate_cpp(
  CXX_PROTO HDR_PROTO "${META_PROTO}"
)
protobuf_generate_grpc_cpp(
  CXX_PROTO_GRPC HDR_PROTO_GRPC "${META_PROTO}"
)
##-
add_library(
  "${PROJECT_NAME}" STATIC
  "${CXX_SRC}"
  "${CXX_PROTO}"
  "${CXX_PROTO_GRPC}"
)
target_include_directories(
  "${PROJECT_NAME}" PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${GRPC_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/cxx_include/"
)
target_link_libraries(
  "${PROJECT_NAME}" PUBLIC
  "gRPC::grpc++"
)

###
if("${OPT_IS_BUILD_GTEST}" AND "${OPT_IS_BUILD_CLIENT}")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    URL_HASH MD5=611067c2affbf9eafb919df5db1ea7f6
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  ##-
  link_libraries(
    "gtest_main"
    "gmock_main"
  )
  ##-
  file(GLOB_RECURSE "CXX_SRC_GTEST" "${PROJECT_SOURCE_DIR}/plugin_gtest_cxx_src/*.cxx")
  add_executable(
    "${PROJECT_NAME}-GTest"
    "${CXX_SRC_GTEST}"
  )
  target_include_directories(
    "${PROJECT_NAME}-GTest" PRIVATE
    "${PROJECT_SOURCE_DIR}/plugin_gtest_cxx_src/"
  )
  target_link_libraries(
    "${PROJECT_NAME}-GTest" PRIVATE
    "${PROJECT_NAME}"
  )
endif()
