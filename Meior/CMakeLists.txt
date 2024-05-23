cmake_minimum_required(VERSION 3.16)


set(MEIOR_SRC
        src/main.cpp
        include/Meior/Application.hpp
        src/Application.cpp
)

add_executable(Meior ${MEIOR_SRC})

target_include_directories(Meior PUBLIC include)
target_include_directories(Meior PRIVATE src)

target_link_libraries(Meior PUBLIC Core imgui)
target_link_libraries(Meior PRIVATE glad glfw)
