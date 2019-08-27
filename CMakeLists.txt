CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
set(CMake_Misc_Dir "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMake_Misc_Dir}")

include(Hardening)
PROJECT(nppDirectWriteEnabler)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_USE_RELATIVE_PATHS TRUE)
set(Source_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(NPP_Plugin_SDK_Dir "${CMAKE_CURRENT_SOURCE_DIR}/plugintemplate/src")

file(GLOB_RECURSE SRCFILES "${Source_dir}/*.c" "${Source_dir}/*.cpp")
if(MSVC_IDE)
	file(GLOB_RECURSE HDRFILES "${Source_dir}/*.h")
endif()

add_library(DirectWriteEnabler SHARED "${SRCFILES}" "${HDRFILES}")
target_include_directories(DirectWriteEnabler PUBLIC "${NPP_Plugin_SDK_Dir}")

set_property(TARGET DirectWriteEnabler PROPERTY CXX_STANDARD 20)
set_property(TARGET DirectWriteEnabler PROPERTY PREFIX "")
harden(DirectWriteEnabler)
