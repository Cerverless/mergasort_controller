cmake_minimum_required(VERSION 3.26)
project(mergasort_controller1 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(src)
include_directories(lib)

add_executable(mergasort_controller1
    include/ws.h
    src/messaging.h
    src/msc.c
    src/msc.h
    src/msc_functions.c
    src/msc_functions.h)

target_link_libraries(mergasort_controller1 /root/mergasort_controller/lib/libws.a)