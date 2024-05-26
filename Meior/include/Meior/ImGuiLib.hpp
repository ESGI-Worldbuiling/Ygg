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
#include <string>

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
		// ImGui::InputText() with std::string
		// Because text input needs dynamic resizing, we need to setup a callback to grow the capacity
		static bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
		static bool InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
		static bool InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
	};

} // namespace Ygg::Meior

