# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("esenthelpers" VERSION 0.1 LANGUAGES CXX)

add_definitions("-DUNICODE")
add_definitions("-D_UNICODE")
add_definitions("-DJET_UNICODE")

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++lastest")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /P")

#nable_testing()

add_library (esenthelpers STATIC
             "src/CxlEsentLibrary.cpp" 
             "src/CxlEsentErrors.cpp")

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(esenthelpers PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)

# If we have compiler requirements for this library, list them
# here
target_compile_features(esenthelpers
                        PUBLIC cxx_auto_type
                        PRIVATE cxx_variadic_templates)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS esenthelpers 
        EXPORT esenthelpersconfig
        ARCHIVE  DESTINATION lib ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION lib ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION bin ${CMAKE_INSTALL_BINDIR})  # This is for Windows

install(DIRECTORY include/ DESTINATION include ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT esenthelpersconfig DESTINATION share/esenthelpers/cmake)

# This makes the project importable from the build directory
export(TARGETS esenthelpers FILE esenthelpersconfig.cmake)

# Unit tests, of course
add_executable(esenttestlib
               test/main.cpp
               test/CxlEsentTestErrors.cpp)

target_link_libraries(esenttestlib
                      esenthelpers)

add_test(esenttestlib esenttestlib)




