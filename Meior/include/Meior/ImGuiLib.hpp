//
// Created by Sayama on 23/05/2024.
//

#pragma once

#ifndef IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 1
#endif

#include "Meior/Renderer/Window.hpp"
#include <imgui.h>
#include <cinttypes>
#include <functional>

struct GLFWwindow;

namespace Ygg::Meior {

	class ImGuiLib {
	public:
		static bool Initalize(const char* glsl_version, const Window&);
		static bool Destroy();
		static void BeginFrame();
		static void EndFrame(uint32_t width, uint32_t height);
		static void UseDockSpace(std::function<void(void)> menuBarFun);
	public:
	private:
	};

} // namespace Ygg::Meior

