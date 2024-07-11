//
// Created by Sayama on 11/07/2024.
//

#include "Meior/Renderer/GraphicsContext.hpp"
#include "Meior/Renderer/Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Ygg::Meior {

	GraphicsContext::GraphicsContext(Window *windowPtr) : m_WindowPtr(windowPtr) {
	}
	GraphicsContext::~GraphicsContext() {
	}
	void GraphicsContext::Init() {
		YGG_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowPtr->GetNativeWindow<GLFWwindow>());
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		YGG_INFO("glad loading status: {0}", status);
		
		YGG_INFO("OpenGL Info:");
		YGG_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		YGG_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		YGG_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	void GraphicsContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowPtr->GetNativeWindow<GLFWwindow>());
	}
}// namespace Ygg::Meior