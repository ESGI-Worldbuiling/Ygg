cmake_minimum_required(VERSION 3.16)

#GLM Options
set(GLM_ENABLE_CXX_20 ON)

# ImGui Parameters
set(IMGUI_GLFW              ON)
set(IMGUI_OPENGL3           ON)
set(IMGUI_OPENGL3_LOADER    ON)

# GLFW Parameters
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

# ASSIMP Parameters
set(ASSIMP_NO_EXPORT ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS ON)
set(USE_SYSTEM_ASSIMP ON)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/icaven/glm
        GIT_TAG master
)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG 27cb4c76708608465c413f6d0e6b8d99a4d84302 # v1.14.1
)

FetchContent_Declare(
        tinygltf
        GIT_REPOSITORY https://github.com/syoyo/tinygltf
        GIT_TAG 4bfc1fc1807e2e2cf3d3111f67d6ebd957514c80 # v2.8.21
)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp
        GIT_TAG 10df90ec144179f97803a382e4f07c0570665864 # v5.4.1
)

FetchContent_Declare(
        meshoptimizer
        GIT_REPOSITORY https://github.com/zeux/meshoptimizer
        GIT_TAG c21d3be6ddf627f8ca852ba4b6db9903b0557858 # v0.20
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # v3.4
)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/Sayama3/ImGui
        GIT_TAG docking #docking branch
)

FetchContent_MakeAvailable(glm spdlog tinygltf assimp meshoptimizer glfw imgui)

target_link_libraries(imgui PUBLIC glfw)

# Tracy Parameters
option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND "" ON)

add_subdirectory(tracy)

add_subdirectory(glad)