cmake_minimum_required(VERSION 4.0.1)

project(WordChecker VERSION 0.0.0.1)

#set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(wordchecker_compiler_flags INTERFACE)

target_compile_features(wordchecker_compiler_flags INTERFACE cxx_std_23)

configure_file(WordCheckerConfig.h.in WordCheckerConfig.h)

add_subdirectory(MathFunctions)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

add_executable(WordChecker main.cpp)

target_link_libraries(WordChecker PUBLIC MathFunctions wordchecker_compiler_flags ${wxWidgets_LIBRARIES})

target_include_directories(WordChecker PUBLIC "${PROJECT_BINARY_DIR}")
