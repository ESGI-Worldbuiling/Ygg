cmake_minimum_required(VERSION 3.16)

set(CORE_SRC
        include/Core/Logger.hpp
        src/Logger.cpp
)

add_library(Core STATIC ${CORE_SRC})
add_compile_definitions(Core PUBLIC YGG_LOG)
target_link_libraries(Core PUBLIC glm spdlog::spdlog_header_only tracy tinygltf)
