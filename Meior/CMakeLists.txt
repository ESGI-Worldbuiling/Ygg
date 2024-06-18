cmake_minimum_required(VERSION 3.16)


set(MEIOR_SRC
        src/main.cpp
        include/Meior/Application.hpp
        src/Application.cpp
		src/ImGuiLib.cpp
		include/Meior/ImGuiLib.hpp
		src/Panels/Panel.cpp
		include/Meior/Panels/Panel.hpp
		include/Meior/Macro.hpp
		src/Renderer/Renderer.cpp
		include/Meior/Renderer/Renderer.hpp
		src/Renderer/Window.cpp
		include/Meior/Renderer/Window.hpp
		src/Panels/TerrainPanel.cpp
		include/Meior/Panels/TerrainPanel.hpp
		src/Panels/TreePanel.cpp
		include/Meior/Panels/TreePanel.hpp
		src/Renderer/Buffer.cpp
		include/Meior/Renderer/Buffer.hpp
		src/Renderer/Shader.cpp
		include/Meior/Renderer/Shader.hpp
		src/Renderer/VertexArray.cpp
		include/Meior/Renderer/VertexArray.hpp
)

add_executable(Meior ${MEIOR_SRC})

#target_compile_definitions(Meior PUBLIC GLFW_INCLUDE_NONE=1 PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=1)

target_include_directories(Meior PUBLIC include)
target_include_directories(Meior PRIVATE src)

target_link_libraries(Meior PUBLIC Core imgui glad glfw)
