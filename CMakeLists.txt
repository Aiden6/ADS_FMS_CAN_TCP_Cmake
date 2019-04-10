cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE "DEBUG")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

project(ADS_FMS_OTA)

aux_source_directory(. DIR_SRCS)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(include)


add_executable(ADS_FMS_OTA main.cc)
target_link_libraries(ADS_FMS_OTA ADS_FMS_OTA_LIB)

target_link_libraries(ADS_FMS_OTA libidriving_can.so)
target_link_libraries(ADS_FMS_OTA libusbcan.so.1)
target_link_libraries(ADS_FMS_OTA libusbcan.so)

target_link_libraries(ADS_FMS_OTA libpthread.so.0)
target_link_libraries(ADS_FMS_OTA librt.so.1)

target_link_libraries(ADS_FMS_OTA libcrypto.a)
target_link_libraries(ADS_FMS_OTA libssl.a)

target_link_libraries(ADS_FMS_OTA libboost_filesystem.so)
target_link_libraries(ADS_FMS_OTA libboost_system.so)
target_link_libraries(ADS_FMS_OTA libboost_thread.so)
#target_link_libraries(ADS_FMS_OTA libcurses.so)

