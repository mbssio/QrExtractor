cmake_minimum_required(VERSION 3.30)
project(QrExtractor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/dist)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/dist)

set(SOURCES
        main.cpp
        utils/ConfigManager.cpp
        utils/MuPDFConverter.cpp
        utils/BWSExtractor.cpp
)

set(HEADERS
        utils/ConfigManager.h
        utils/MuPDFConverter.h
        utils/BWSExtractor.h
)

add_executable(QrExtractor ${SOURCES} ${HEADERS})

# Optional: organize files in IDEs
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

# === External files ===
set(MUTOOL_DIR ${CMAKE_SOURCE_DIR}/mutool)
set(MUTOOL_EXE ${MUTOOL_DIR}/mutool.exe)

# Manually include DLLs you know mutool.exe needs (adjust paths if needed)
set(MUTOOL_DLLS
        "C:/Windows/System32/MSVCP140.dll"
        "C:/Windows/System32/VCRUNTIME140.dll"
        "C:/Windows/System32/ucrtbase.dll"
)

# Define target subdirectory for mutool
set(MUTOOL_DEST_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/mupdf)

# Copy mutool.exe
add_custom_command(TARGET QrExtractor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${MUTOOL_DEST_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MUTOOL_EXE} "${MUTOOL_DEST_DIR}"
)

# Copy required DLLs
foreach(DLL ${MUTOOL_DLLS})
    add_custom_command(TARGET QrExtractor POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DLL} "${MUTOOL_DEST_DIR}"
    )
endforeach()

