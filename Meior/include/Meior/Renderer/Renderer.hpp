//
// Created by ianpo on 25/05/2024.
//

#pragma once


#include "Core/Core.hpp"
#include "Meior/Renderer/Framebuffer.hpp"
#include "Meior/Renderer/Light.hpp"
#include "Render/Camera.hpp"
#include "Render/Scene.hpp"
#include "UniformBuffer.hpp"


namespace Ygg::Meior {

	static constexpr inline int MAX_LIGHT_COUNT = 20;

	struct RendererData {
		RendererData() = default;
		~RendererData() = default;
		// TODO: Add Normal Matrix
		// TODO: Add MVP Matrix
		// Both Previous todo are to reduce the load on the GPU side.
		//  But it might need a bit of checking and more data to know if it's worth.

		struct CameraData {
			glm::mat4 ViewProjectionMatrix;
			glm::vec4 CameraPosition;
			glm::vec4 CameraDirection;
		};

		struct ModelData {
			inline ModelData() = default;
			inline ~ModelData() = default;
			ModelData(glm::mat4 transformMatrix, glm::mat4 normalMatrix, int entityId);
			glm::mat4 TransformMatrix;
			glm::mat4 NormalMatrix;
		};

		struct LightData {
			Light lights[MAX_LIGHT_COUNT];
			int lightCount;
		};


		CameraData CameraBuffer;
		ModelData ModelBuffer;
		LightData LightBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;
		Ref<UniformBuffer> ModelUniformBuffer;
		Ref<UniformBuffer> LightUniformBuffer;
		std::multimap<float, std::tuple<const Ref<Mesh>, glm::mat4, int>> AlphaMeshes;
		std::vector<std::tuple<const Ref<Mesh>, glm::mat4, int>> OpaqueMeshes;
	};

	class Renderer {
	public:
		static void Initialize();
		static void Destroy();
	public:
		static void Clear();
		static void RenderScene(const Scene& scene, Framebuffer* fb, IProjection* projMatrix, IView* viewMatrix);
	private:
		static inline RendererData s_RenderData{};
	};

} // namespace Ygg::Meior

