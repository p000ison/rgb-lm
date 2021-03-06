cmake_minimum_required(VERSION 2.8.4)
project(rgb_led_matrix)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules )

add_definitions(-DREV2)

add_definitions(-DRT)

if (RELEASE)
    set(CMAKE_BUILD_TYPE Release)
    message("Build type: Release")
else (RELEASE)
    set(CMAKE_BUILD_TYPE Debug)
     message("Build type: Debug")
endif(RELEASE)


find_package (Threads)
find_library(REAL_TIME rt)

set(THREADING ${REAL_TIME} ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(src/lm)
add_subdirectory(examples)
add_subdirectory(alarm-clock)
add_subdirectory(m3u)


add_executable(measure measure.c)
target_link_libraries (measure ${THREADING})
set_target_properties(measure
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
