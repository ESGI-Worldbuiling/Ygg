//
// Created by ianpo on 25/05/2024.
//

#pragma once


#include "Core/Core.hpp"
#include "Render/Scene.hpp"
#include "Render/Camera.hpp"
#include "Meior/Renderer/Framebuffer.hpp"

namespace Ygg::Meior {

	class Renderer {
	public:
		static void Clear();
		static void RenderScene(const Scene& scene, Framebuffer* fb, IProjection* projMatrix, IView* viewMatrix);
	};

} // namespace Ygg::Meior

