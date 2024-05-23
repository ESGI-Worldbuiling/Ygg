set(YGG_TARGET_NAME Ygg)

set(YGG_TARGET_SOURCES
        src/TerrainGenerator.cpp
        src/TreeGenerator.cpp
        src/LSys.cpp

        src/Core/Logger.cpp
)

configure_file(${CMAKE_SOURCE_DIR}/cmake/pch.h.in ${PROJECT_BINARY_DIR}/ygg_pch.h @ONLY)

option(YGG_SHARED_LIB "Build Ygg as a shared library" OFF)

if (YGG_SHARED_LIB)
    message("-- Ygg: Building as shared library")

    set(WINDOWS_EXPORT_ALL_SYMBOLS ON)

    include(GenerateExportHeader)

    generate_export_header(${YGG_TARGET_NAME}
            EXPORT_MACRO_NAME "YGG_API"
            EXPORT_FILE_NAME "export/ygg_export.hpp"
    )

    list(APPEND ${YGG_TARGET_SOURCES}
        include/Ygg.h
    )

    add_library(${YGG_TARGET_NAME} SHARED ${YGG_TARGET_SOURCES})

    target_include_directories(${YGG_TARGET_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/export)

else ()
    message("-- Ygg: Building as static library")
    add_library(${YGG_TARGET_NAME} STATIC ${YGG_TARGET_SOURCES})
endif ()

target_compile_definitions(${YGG_TARGET_NAME} PRIVATE YGG_LOG)

target_include_directories(${YGG_TARGET_NAME} PUBLIC include)

target_include_directories(${YGG_TARGET_NAME} PRIVATE src)

target_link_libraries(${YGG_TARGET_NAME} PUBLIC glm spdlog::spdlog_header_only tinygltf)

target_precompile_headers(${YGG_TARGET_NAME} PRIVATE ${PROJECT_BINARY_DIR}/ygg_pch.h)