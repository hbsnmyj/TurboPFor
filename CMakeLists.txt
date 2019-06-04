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
    )
set(HEADER_FILES
    conf.h
    vp4.h
    bitpack.h
    vint.h
    bitutil.h
)



add_library(turbopfor_sse ${SOURCE_FILES})
target_include_directories(turbopfor_sse PUBLIC $<INSTALL_INTERFACE:include/turbopfor>)
target_compile_definitions(turbopfor_sse PRIVATE SSE_ON)

add_library(turbopfor_avx2 ${SOURCE_FILES})
target_include_directories(turbopfor_avx2 PUBLIC $<INSTALL_INTERFACE:include/turbopfor>)
target_compile_definitions(turbopfor_avx2 PRIVATE AVX2_ON)

add_library(turbopfor ${SOURCE_FILES})
target_sources(turbopfor PRIVATE bitutil.c)
target_include_directories(turbopfor PUBLIC $<INSTALL_INTERFACE:include/turbopfor>)
target_compile_definitions(turbopfor PRIVATE USE_SSE USE_AVX2)
target_link_libraries(turbopfor turbpfor_sse turbopfor_avx2)

include( CMakePackageConfigHelpers )
set(CONFIG_PACKAGE_INSTALL_DIR share/turbopfor/cmake)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/turbopfor-config-version.cmake
    VERSION 0.1
    COMPATIBILITY SameMajorVersion
    )

install(FILES ${HEADER_FILES} DESTINATION include/turbopfor)

install(TARGETS turbopfor turbopfor_sse turbopfor_avx2
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
