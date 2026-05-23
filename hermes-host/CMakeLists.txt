cmake_minimum_required(VERSION 3.20)
project(hermes_host CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HERMES_DIR ${CMAKE_SOURCE_DIR}/../third-party/hermes)

set(HERMES_ENABLE_TEST_SUITE OFF CACHE BOOL "" FORCE)
set(HERMES_ENABLE_TOOLS ON CACHE BOOL "" FORCE)
set(HERMES_BUILD_SHARED_JSI ON CACHE BOOL "" FORCE)

add_subdirectory(${HERMES_DIR} ${CMAKE_BINARY_DIR}/hermes-build)

add_executable(hermes-host src/host.cpp)

target_include_directories(hermes-host PRIVATE
    ${HERMES_DIR}/API
    ${HERMES_DIR}/API/jsi
    ${HERMES_DIR}/public
    ${HERMES_DIR}/include
)

target_link_libraries(hermes-host PRIVATE
    hermesvm
    jsi
    compileJS
)
