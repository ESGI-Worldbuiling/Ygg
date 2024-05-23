cmake_minimum_required(VERSION 3.16)

option(GLM_ENABLE_CXX_20 ON)

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
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad
        GIT_TAG v2.0.6
)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/Sayama3/ImGui
        GIT_TAG docking #docking branch
)

# GLAD Parameters
set(GLAD_PROFILE        "core" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_API            "gl=4.6" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest" FORCE)
set(GLAD_GENERATOR      "c" CACHE STRING "Language to generate the binding for" FORCE)
#set(GLAD_EXTENSIONS     "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included" FORCE)

# ImGui Parameters
set(IMGUI_GLFW              ON)
set(IMGUI_OPENGL3           ON)
set(IMGUI_OPENGL3_LOADER    ON)

# ASSIMP Parameters
set(ASSIMP_NO_EXPORT ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS ON)
set(USE_SYSTEM_ASSIMP ON)

FetchContent_MakeAvailable(glm spdlog tinygltf assimp meshoptimizer glfw glad imgui)

target_link_libraries(imgui PUBLIC glfw)

# Tracy Parameters
option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND "" ON)

add_subdirectory(tracy)