//
// Created by ianpo on 25/05/2024.
//

#include "Meior/Renderer/Renderer.hpp"

#include <glad/glad.h>

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE 1
#endif

#include <GLFW/glfw3.h>

namespace Ygg::Meior {

	void Renderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Renderer::RenderScene(const Scene &scene, Framebuffer* fb, IProjection *projMatrix, IView *viewMatrix) {
		fb->Bind();



		fb->Unbind();
	}

} // namespace Ygg::Meior
