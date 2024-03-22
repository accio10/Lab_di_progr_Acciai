cmake_minimum_required(VERSION 3.20)
project(Lab_di_progr_Acciai)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(Google_Test/googletest-main)
include_directories(Google_Test/googletest-main/googletest/include)
include_directories(Google_Test/googletest-main/googlemock/include)

add_executable(Lab_di_progr_Acciai main.cpp Account.cpp User.cpp
        Google_Test/TestUser.cpp

)

target_link_libraries(Lab_di_progr_Acciai gtest gtest_main)
