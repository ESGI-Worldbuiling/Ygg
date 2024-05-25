//
// Created by Sayama on 23/05/2024.
//

#pragma once

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

struct GLFWwindow;

namespace Ygg::Meior {

	class ImGuiLib {
	public:
		static bool Initalize(const char* glsl_version, const GLFWwindow*);
		static bool Destroy();
	public:
	private:
	};

} // namespace Ygg::Meior

