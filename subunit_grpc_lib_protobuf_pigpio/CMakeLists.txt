set(PROJECT_NAME "grpc_protobuf_pigpio")
##-
if(NOT "${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH|ONLY_RAW|ONLY_QT)$")
  message(FATAL_ERROR)
endif()

###
cmake_minimum_required(VERSION "${CMAKE_VERSION}")
project("${PROJECT_NAME}")

###
find_package(Threads REQUIRED)
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH|ONLY_RAW)$")
  find_package(Protobuf REQUIRED)
  find_package(gRPC CONFIG REQUIRED)
endif()
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH|ONLY_QT)$")
  find_package("Qt${QT_VERSION_MAJOR}" REQUIRED COMPONENTS Core)
  find_package("Qt${QT_VERSION_MAJOR}" REQUIRED COMPONENTS Protobuf)
  find_package("Qt${QT_VERSION_MAJOR}" REQUIRED COMPONENTS Grpc)
  qt_standard_project_setup()
endif()

###
file(GLOB_RECURSE CXX_SRC "cxx_src/*.cxx")
file(GLOB_RECURSE META_PROTO "meta_proto/*.proto")
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH|ONLY_RAW)$")
  protobuf_generate_cpp(
    CXX_PROTO HDR_PROTO "${META_PROTO}"
  )
  protobuf_generate_grpc_cpp(
    CXX_PROTO_GRPC HDR_PROTO_GRPC "${META_PROTO}"
  )
endif()
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
  "${PROJECT_SOURCE_DIR}/cxx_include/"
)
##-
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH|ONLY_RAW)$")
  target_include_directories(
    "${PROJECT_NAME}" PUBLIC
    "${GRPC_BINARY_DIR}"
  )
  target_link_libraries(
    "${PROJECT_NAME}" PUBLIC
    "gRPC::grpc++"
  )
endif()
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH|ONLY_QT)$")
  target_link_libraries(
    "${PROJECT_NAME}" PUBLIC
    Qt6::Core
    Qt6::Protobuf
    Qt6::Grpc
  )
  qt_add_protobuf(
    "${PROJECT_NAME}"
    EXTRA_NAMESPACE prefix_grpc_qt
    PROTO_FILES
    "${META_PROTO}"
  )
  qt_add_grpc(
    "${PROJECT_NAME}" CLIENT
    EXTRA_NAMESPACE prefix_grpc_qt
    PROTO_FILES
    "${META_PROTO}"
  )
endif()
##-
target_compile_definitions(
  "${PROJECT_NAME}" PUBLIC
  MACROMARK_GRPC_CLIENT_0ENUM_0BOTH=0
  MACROMARK_GRPC_CLIENT_0ENUM_1ONLY_RAW=1
  MACROMARK_GRPC_CLIENT_0ENUM_2ONLY_QT=2
)
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(BOTH)$")
  target_compile_definitions(
    "${PROJECT_NAME}" PUBLIC
    MACROMARK_GRPC_CLIENT=MACROMARK_GRPC_CLIENT_0ENUM_0BOTH
  )
endif()
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(ONLY_RAW)$")
  target_compile_definitions(
    "${PROJECT_NAME}" PUBLIC
    MACROMARK_GRPC_CLIENT=MACROMARK_GRPC_CLIENT_0ENUM_1ONLY_RAW
  )
endif()
if("${OPT_HOW_ENABLE_GRPC_CLIENT}" MATCHES "^(ONLY_QT)$")
  target_compile_definitions(
    "${PROJECT_NAME}" PUBLIC
    MACROMARK_GRPC_CLIENT=MACROMARK_GRPC_CLIENT_0ENUM_2ONLY_QT
  )
endif()

###
if(OFF)
  add_library(
    "${PROJECT_NAME}-melon" STATIC
    "${PROJECT_SOURCE_DIR}/cxx_src_melon.cxx"
  )
  target_link_libraries(
    "${PROJECT_NAME}-melon" PRIVATE
    "${PROJECT_NAME}"
  )
endif()

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
  ##-
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
