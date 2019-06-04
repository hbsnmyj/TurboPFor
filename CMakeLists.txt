cmake_minimum_required(VERSION 3.6)
project(TurboPFor)

set(CMAKE_CXX_STANDARD 17)

set(MARCH "-march=native -mssse3 -mavx2 -mbmi2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MARCH}")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${MARCH}")

set(SOURCE_FILES
    vp4c.c
    vp4d.c
    vint.c
    bitpack.c
    bitunpack.c
    bitutil.c)
set(HEADER_FILES
    conf.h
    vp4.h
    bitpack.h
    vint.h
    bitutil.h
    )

add_library(turbopfor ${SOURCE_FILES})
target_sources(turbopfor PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_FILES}>)
target_include_directories(turbopfor PUBLIC $<INSTALL_INTERFACE:include/turbopfor>)
target_compile_definitions(turbopfor PUBLIC USE_SSE USE_AVX2 AVX2_ON SSE2_ON)

include( CMakePackageConfigHelpers )
set(CONFIG_PACKAGE_INSTALL_DIR share/turbopfor/cmake)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/turbopfor-config-version.cmake
    VERSION 0.1
    COMPATIBILITY SameMajorVersion
    )

install(FILES ${HEADER_FILES} DESTINATION include/turbopfor)

install(TARGETS turbopfor
    EXPORT turbopfor-targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(EXPORT turbopfor-targets
    NAMESPACE turbopfor::
    DESTINATION ${CONFIG_PACKAGE_INSTALL_DIR}
)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/turbopfor-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/turbopfor-config-version.cmake
    DESTINATION
    ${CONFIG_PACKAGE_INSTALL_DIR}
)
