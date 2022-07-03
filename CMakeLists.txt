cmake_minimum_required (VERSION 3.18)
project (compiller VERSION 1.0.0 LANGUAGES CXX)

# Determine if compiller is built as a subproject (using add_subdirectory) or if it is the master project.

if (NOT DEFINED COMPILLER_MASTER_PROJECT)
  set (COMPILLER_MASTER_PROJECT OFF)

  if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set (COMPILLER_MASTER_PROJECT ON)
  endif ()
endif ()


# Set an additional path to the CMake modules and connect them

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(NestingFileSearch)
include(CMakeDependentOption)


# Options available for project customization

cmake_dependent_option (COMPILLER_BUILD_SHARED_LIBS "Build the project as a dynamic library" "${BUILD_SHARED_LIBS}" "COMPILLER_MASTER_PROJECT" ${COMPILLER_MASTER_PROJECT})
cmake_dependent_option (COMPILLER_BUILD_TESTING "Build tests for the project" "${BUILD_TESTING}" "COMPILLER_MASTER_PROJECT" ${COMPILLER_MASTER_PROJECT})

option (COMPILLER_BUILD_APP "Build the application when building the project" ON)
option (COMPILLER_INSTALL "Generate a target for project installation" OFF)
option (COMPILLER_BUILD_EXAMPLE "Build examples for a project" OFF)
option (COMPILLER_GENERATE_DOCUMENTATION "Generate documentation when building a project" OFF)
option (COMPILLER_PEDANTIC "Enable the display of additional warnings" OFF)
option (COMPILLER_WERROR "Handle all compiler warnings with errors" OFF)
option (COMPILLER_MSVC_STATIC_RUNTIME "Link static runtime libraries" OFF)


# Configuring project output directories

if (COMPILLER_MASTER_PROJECT)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) 
endif ( )    


# Configuring project build options

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)
set_property (GLOBAL PROPERTY LINKER_LANGUAGE CXX)
string (APPEND CMAKE_DEBUG_POSTFIX "_dbg")


# Additional options for building on Windows  
if (WIN32)
    set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    if (MSVC AND ${COMPILLER_MSVC_STATIC_RUNTIME})
        set (FLAG_VARS 
            CMAKE_CXX_FLAGS 
            CMAKE_CXX_FLAGS_DEBUG 
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL 
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
        )

        foreach (FLAG_VAR ${FLAG_VARS})
            if (${FLAG_VAR} MATCHES "/MD")
                string (REGEX REPLACE "/MD" "/MT" ${FLAG_VAR} "${${FLAG_VAR}}")
            endif ()
        endforeach ()
        
        string (APPEND CMAKE_DEBUG_POSTFIX "_mt")
        string (APPEND CMAKE_RELEASE_POSTFIX "_mt")
    else ()
        string (APPEND CMAKE_DEBUG_POSTFIX "_md")
        string (APPEND CMAKE_RELEASE_POSTFIX "_md")
    endif ()
endif ()

if (COMPILLER_BUILD_TESTING)
    include (CTest)
    enable_testing ()
endif ()


# Importing additional CMake modules

if (COMPILLER_INSTALL)
    include (GNUInstallDirs)
endif ()


# Adding subdirectories to the project

add_subdirectory (lib)

if (COMPILLER_BUILD_APP)
    add_subdirectory (app)
endif ()

if (COMPILLER_BUILD_TESTING)
    add_subdirectory (test)
endif ()

if (COMPILLER_BUILD_EXAMPLE)
    add_subdirectory (example)
endif ()