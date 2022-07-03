# Create and configure a library target

# Define the library type
if (COMPILLER_BUILD_SHARED_LIBS)
    set (COMPILLER_LIBRARY_TYPE SHARED)
else ()
    set (COMPILLER_LIBRARY_TYPE STATIC)
endif ()

add_library (compiller ${COMPILLER_LIBRARY_TYPE})
message (STATUS "COMPILLER_LIBRARY_TYPE - ${COMPILLER_LIBRARY_TYPE}")

# Describing the list of source files

NestingFileSearch (COMPILLER_PUBLIC_HEADERS
    RECURSIVE
    EXTENSIONS ".h"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
    EXCLUDE_PATTERNS ".*/internal/.*"
)

NestingFileSearch (COMPILLER_PRIVATE_HEADERS
    RECURSIVE
    EXTENSIONS ".h"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/compiller/internal"
)

NestingFileSearch (COMPILLER_SOURCES
    RECURSIVE
    EXTENSIONS ".cc"
    DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_sources(compiller
    PUBLIC 
        ${COMPILLER_PUBLIC_HEADERS}
    PRIVATE
        ${COMPILLER_PRIVATE_HEADERS}
        ${COMPILLER_SOURCES}
)

target_include_directories(compiller
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

foreach(HEADER ${COMPILLER_PUBLIC_HEADERS})
    set_target_properties(compiller
        PROPERTIES
            PUBLIC_HEADER ${HEADER}
    )
endforeach()

# Create an installation target

if(COMPILLER_INSTALL)

    install(
        TARGETS compiller
        EXPORT compiller-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/compiller
    )

endif()