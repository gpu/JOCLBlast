cmake_minimum_required(VERSION 2.8)

#############################################################################
# Overriding the CMake flags to use static runtime libraries
# See http://www.cmake.org/Wiki/CMake_FAQ#
#     How_can_I_build_my_MSVC_application_with_a_static_runtime.3F
set(CMAKE_USER_MAKE_RULES_OVERRIDE
   ${CMAKE_CURRENT_SOURCE_DIR}/../JOCLCommon/CMake_c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
   ${CMAKE_CURRENT_SOURCE_DIR}/../JOCLCommon/CMake_cxx_flag_overrides.cmake)
   
project(JOCLBlast)

#############################################################################
# Set the variables that are later used to build the name of the native 
# library, e.g. "JOCL-0_2_0-windows-x86_64.dll"

set(JOCL_BLAST_VERSION "0_9_0")


#############################################################################
# Add the dependencies to JNI and the JOCLCommon project

find_package(JNI REQUIRED)
add_subdirectory(../JOCLCommon
  ${CMAKE_CURRENT_BINARY_DIR}/JOCLCommon)


#############################################################################
# Find the CLBlast installation directory

find_path(CLBLAST_INSTALL_DIR
  NAMES include lib
  DOC "CLBlast installation directory"
)

if(CMAKE_HOST_WIN32)
  set(JOCL_HOST "windows")
elseif(CMAKE_HOST_APPLE)
  set(JOCL_HOST "apple")
  set(CMAKE_SKIP_RPATH FALSE)
elseif(CMAKE_HOST_UNIX)
  set(JOCL_HOST "linux")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(JOCL_ARCH "x86_64")
else()
  set(JOCL_ARCH "x86")
endif()



#############################################################################
# Compiler settings

if(MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /wd4514 /wd4820 /wd4710 /wd4711 /wd4350 /wd4668")
endif()
set(BUILD_SHARED_LIBS ON)

#############################################################################
# Output directories

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/nativeLibraries/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/nativeLibraries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY         ${PROJECT_SOURCE_DIR}/nativeLibraries)


#############################################################################
# Define the include directories and source files 

include_directories(
  src/main/native
  ${JOCLCommon_SOURCE_DIR}/src/main/include
  ${JOCLCommon_SOURCE_DIR}/src/main/native
  ${CLBLAST_INSTALL_DIR}/include
  ${JNI_INCLUDE_DIRS}
)
  
add_library(JOCLBlast_${JOCL_BLAST_VERSION}-${JOCL_HOST}-${JOCL_ARCH}
  src/main/native/JOCLBlast.cpp 
)

find_library(CLBlast_LIBRARY
    NAMES clblast
    HINTS ${CLBLAST_INSTALL_DIR}/lib
)

target_link_libraries(
  JOCLBlast_${JOCL_BLAST_VERSION}-${JOCL_HOST}-${JOCL_ARCH} 
  ${CLBlast_LIBRARY}
  JOCLCommon)

#############################################################################
# Enable C++11 features
set_property(TARGET JOCLBlast_${JOCL_BLAST_VERSION}-${JOCL_HOST}-${JOCL_ARCH} PROPERTY CXX_STANDARD 11)

