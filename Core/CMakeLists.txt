cmake_minimum_required(VERSION 3.16)

set(CORE_SRC
		include/Core/Logger.hpp
		src/Logger.cpp

		src/Mesh.cpp
)

add_library(Core STATIC ${CORE_SRC})

target_include_directories(Core PUBLIC include)
add_compile_definitions(Core PUBLIC YGG_LOG GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(Core PUBLIC glm spdlog::spdlog_header_only tracy tinygltf)

