set(PROJECT_NAME "TestDemo2023_Grpc_Client")
set(VAR0_PROJECT_PROPERTY0_MACOSX_BUNDLE_GUI_IDENTIFIER "my.example.${PROJECT_NAME}.com")

###
cmake_minimum_required(VERSION "${CMAKE_VERSION}")
project("${PROJECT_NAME}")
##-
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

###
find_package("Qt${QT_VERSION_MAJOR}" REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

###
file(GLOB_RECURSE cxx_src "${PROJECT_SOURCE_DIR}/cxx_src/*.cxx" "${PROJECT_SOURCE_DIR}/meta_QtObject/*.cxx" "${PROJECT_SOURCE_DIR}/meta_QtWidgetUi/*.cxx")
file(GLOB_RECURSE meta_QtWidgetUi "${PROJECT_SOURCE_DIR}/meta_QtWidgetUi/*.ui")
##-
qt_add_library(
  "${PROJECT_NAME}-CoreLibrary"
  "${cxx_src}"
  "${meta_QtWidgetUi}"
)
target_include_directories(
  "${PROJECT_NAME}-CoreLibrary" PUBLIC
  "${PROJECT_SOURCE_DIR}/cxx_include/"
  "${PROJECT_SOURCE_DIR}/meta_QtObject/"
  "${PROJECT_SOURCE_DIR}/meta_QtWidgetUi/"
)
target_link_libraries(
  "${PROJECT_NAME}-CoreLibrary" PUBLIC
  "Qt${QT_VERSION_MAJOR}::Widgets"
  "grpc_protobuf_pigpio"
)
##-
qt_add_executable(
  "${PROJECT_NAME}" MANUAL_FINALIZATION
  "${PROJECT_SOURCE_DIR}/cxx_src_main.cxx"
)
target_link_libraries(
  "${PROJECT_NAME}" PRIVATE
  "${PROJECT_NAME}-CoreLibrary"
)
set_target_properties(
  "${PROJECT_NAME}" PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER "${VAR0_PROJECT_PROPERTY0_MACOSX_BUNDLE_GUI_IDENTIFIER}"
  MACOSX_BUNDLE TRUE
)
if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable("${PROJECT_NAME}")
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
  file(GLOB_RECURSE "cxx_src_gtest" "${PROJECT_SOURCE_DIR}/plugin_gtest_cxx_src/*.cxx")
  qt_add_executable(
    "${PROJECT_NAME}-GTest"
    "${cxx_src_gtest}"
  )
  target_include_directories(
    "${PROJECT_NAME}-GTest" PRIVATE
    "${PROJECT_SOURCE_DIR}/plugin_gtest_cxx_src/"
  )
  target_link_libraries(
    "${PROJECT_NAME}-GTest" PRIVATE
    "${PROJECT_NAME}-CoreLibrary"
  )
endif()
