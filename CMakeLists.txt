cmake_minimum_required(VERSION 3.6)
project(TurboPFor)

set(CMAKE_CXX_STANDARD 17)

set(MARCH "-march=native -mavx2 -mbmi2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MARCH}")

set(SOURCE_FILES
        vp4c.c
        vp4d.c
        vint.c
        bitpack.c
        bitunpack.c
        bitutil.c)

add_library(turbopfor ${SOURCE_FILES})


message(STATUS "INSTALL PREFIX set to ${CMAKE_INSTALL_PREFIX}")
install(TARGETS turbopfor
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

set(HEADER_FILES
        conf.h
        vp4.h
        bitpack.h
        vint.h
        bitutil.h
)

install(FILES ${HEADER_FILES} DESTINATION include/turbopfor)
