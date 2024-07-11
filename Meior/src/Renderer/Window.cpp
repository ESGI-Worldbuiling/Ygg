//
// Created by ianpo on 26/05/2024.
//

#include "Meior/Renderer/Window.hpp"

#include "glad/glad.h"

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE 1
#endif

#include "GLFW/glfw3.h"

#include "Core/Logger.hpp"

#include <cstdio>
#include <stdexcept>


namespace Ygg::Meior {

	static void glfw_error_callback(int error, const char* description)
	{
		YGG_ERROR("GLFW Error {}: {}", error, description);
	}

	Window::Window(const WindowProps& props) : m_WindowProps(props)
	{
		YGG_TRACE("Creating window {}", m_WindowProps.Title);
		glfwSetErrorCallback(glfw_error_callback);

		if (!glfwInit()) {
			YGG_ERROR("GLFW could not be initialized.");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		// Create window with graphics context
		m_Window = glfwCreateWindow(m_WindowProps.Width, m_WindowProps.Height, "Meior", nullptr, nullptr);
		if (m_Window == nullptr) {
			YGG_ERROR("GLFW could not Create a window.");
			return;
		}

		m_Context = CreateScope<GraphicsContext>(this);
		m_Context->Init();

		glfwSwapInterval(1); // Enable vsync
	}

	Window::~Window() {
		YGG_TRACE("Destroying window {}", m_WindowProps.Title);
		if(m_Window) {
			m_Context.reset();
			glfwDestroyWindow(GetNativeWindow<GLFWwindow>());
			glfwTerminate();
			m_Window = nullptr;
		}
	}

	void Window::SwapBuffers() {
		m_Context->SwapBuffers();
	}

	void Window::PollEvents() {
		glfwPollEvents();
	}

	bool Window::ShouldClose() const {
		return glfwWindowShouldClose(const_cast<GLFWwindow*>(GetNativeWindow<GLFWwindow>()));
	}

	void Window::SetVSync(bool state) {
		glfwSwapInterval(state ? 1 : 0); // Enable vsync
	}
	void Window::Close() {
		YGG_TRACE("Closing window {}", m_WindowProps.Title);
		glfwSetWindowShouldClose(GetNativeWindow<GLFWwindow>(), true);
	}
} // namespace Ygg::Meior
