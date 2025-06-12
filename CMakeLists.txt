cmake_minimum_required(VERSION 3.30)
project(QrExtractor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
