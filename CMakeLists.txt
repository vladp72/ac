# CMakeList.txt : 
# based on https://rix0r.nl/blog/2015/08/13/cmake-guide/ 
# alse see 
#     https://www.slideshare.net/DanielPfeifer1/cmake-48475415
#     https://cliutils.gitlab.io/modern-cmake/
#     https://codingnest.com/basic-cmake/
#     https://codingnest.com/basic-cmake-part-2/
#
cmake_minimum_required (VERSION 3.8)

project ("ac" VERSION 0.1 LANGUAGES CXX)

add_definitions("-DUNICODE")
add_definitions("-D_UNICODE")
add_definitions("-DJET_UNICODE")

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /P")

enable_testing()

add_library (ac STATIC
             "src/AcEsentLibrary.cpp" 
             "src/AcEsentErrors.cpp")

if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options( ac PRIVATE /W4 /w44265 /w44061 /w44062 )
endif()

target_compile_definitions(ac PUBLIC UNICODE _UNICODE JET_UNICODE)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(ac PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)

# If we have compiler requirements for this library, list them
# here
target_compile_features(ac
                        PUBLIC cxx_auto_type
                        PUBLIC cxx_final
                        PUBLIC cxx_deleted_functions
                        PUBLIC cxx_defaulted_functions
                        PUBLIC cxx_attributes
                        PUBLIC cxx_variadic_templates)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ac 
        EXPORT acconfig
        ARCHIVE  DESTINATION lib ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION lib ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION bin ${CMAKE_INSTALL_BINDIR})  # This is for Windows

install(DIRECTORY include/ DESTINATION include ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT acconfig DESTINATION share/ac/cmake)

# This makes the project importable from the build directory
export(TARGETS ac FILE acconfig.cmake)

# Unit tests, of course
add_executable(actest
               test/main.cpp
               test/AcEsentTestErrors.cpp
	       test/AcEsentTestInstance.cpp
	       test/AcEsentTestVariant.cpp)

if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options( actest PRIVATE /W4 /w44265 /w44061 /w44062 )
endif()


target_link_libraries(actest
                      ac)

add_test(actest actest)




