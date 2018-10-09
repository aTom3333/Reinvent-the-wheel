cmake_minimum_required(VERSION 3.9)
project(reinvent_the_wheel
        VERSION 1.0
        DESCRIPTION "A anecdotical project where I reimplement some elements of the standard library"
        LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/W4 /W14640 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic)
endif()


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(COVERAGE OFF CACHE BOOL "Coverage")
if (COVERAGE)
    add_compile_options(--coverage)
    link_libraries(--coverage)
endif()

add_subdirectory(src)

#TODO remove this
add_executable(temp main.cpp)
target_link_libraries(temp PUBLIC variant)


find_package(Catch 2.2.3)
if(CATCH_FOUND)
    enable_testing()
    add_subdirectory(test)
endif()


# If doxygen is found, add a custom target that generates the doc
#find_package(Doxygen)
#if(DOXYGEN_FOUND)
#    configure_file(${CMAKE_HOME_DIRECTORY}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
#    add_custom_target(doc
#            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
#            WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
#            COMMENT "Generating API documentation with Doxygen" VERBATIM
#            )
#endif(DOXYGEN_FOUND)