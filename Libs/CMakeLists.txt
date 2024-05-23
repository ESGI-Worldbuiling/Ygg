cmake_minimum_required(VERSION 3.16)

option(GLM_ENABLE_CXX_20 ON)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/icaven/glm.git
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

FetchContent_MakeAvailable(glm spdlog tinygltf)