cmake_minimum_required(VERSION 3.10)

project(UrlDownloader)

set(CMAKE_CXX_STANDARD 17)

set(CPR_INCLUDE_DIR "/opt/homebrew/Cellar/cpr/1.11.1/include") #укажите свой путь
set(CPR_LIB_DIR "/opt/homebrew/Cellar/cpr/1.11.1/lib") #укажите свой путь
include_directories(${CPR_INCLUDE_DIR})
link_directories(${CPR_LIB_DIR})

set(SPDLOG_INCLUDE_DIR "/opt/homebrew/Cellar/spdlog/1.15.0/include") #укажите свой путь
set(SPDLOG_LIB_DIR "/opt/homebrew/Cellar/spdlog/1.15.0/lib") #укажите свой путь         
include_directories(${SPDLOG_INCLUDE_DIR})
link_directories(${SPDLOG_LIB_DIR})

set(FMT_INCLUDE_DIR "/opt/homebrew/Cellar/fmt/11.0.2/include") #укажите свой путь 
set(FMT_LIB_DIR "/opt/homebrew/Cellar/fmt/11.0.2/lib") #укажите свой путь         
include_directories(${FMT_INCLUDE_DIR})
link_directories(${FMT_LIB_DIR})

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(UrlDownloader main.cpp)

target_link_libraries(UrlDownloader PRIVATE cpr spdlog fmt)

set(GTEST_INCLUDE_DIR "/opt/homebrew/Cellar/googletest/1.15.2/include") #укажите свой путь  
set(GTEST_LIB_DIR "/opt/homebrew/Cellar/googletest/1.15.2/lib") #укажите свой путь  

include_directories(${GTEST_INCLUDE_DIR})
link_directories(${GTEST_LIB_DIR})

add_executable(UrlDownloaderTests tests.cpp)

target_link_libraries(UrlDownloaderTests PRIVATE gtest gtest_main)

enable_testing()
add_test(NAME UrlDownloaderTests COMMAND UrlDownloaderTests)
