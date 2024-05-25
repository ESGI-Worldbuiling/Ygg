cmake_minimum_required(VERSION 3.16)


set(MEIOR_SRC
        src/main.cpp
        include/Meior/Application.hpp
        src/Application.cpp
		src/ImGuiLib.cpp
		include/Meior/ImGuiLib.hpp
		src/Panel.cpp
		include/Meior/Panel.hpp
		include/Meior/Macro.hpp
		src/Renderer.cpp
		include/Meior/Renderer.hpp
)

add_executable(Meior ${MEIOR_SRC})

#target_compile_definitions(Meior PUBLIC GLFW_INCLUDE_NONE=1 PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=1)

target_include_directories(Meior PUBLIC include)
target_include_directories(Meior PRIVATE src)

target_link_libraries(Meior PUBLIC Core imgui glad glfw)
