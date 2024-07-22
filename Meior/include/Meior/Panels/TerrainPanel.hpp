//
// Created by ianpo on 26/05/2024.
//

#pragma once

#include "Core/SmartPointers.hpp"
#include "Meior/Renderer/Framebuffer.hpp"
#include "Meior/Renderer/Shader.hpp"
#include "Meior/Renderer/Texture.hpp"
#include "Meior/Renderer/Mesh.hpp"
#include "Panel.hpp"
#include "Render/Camera.hpp"
#include "Render/Scene.hpp"


namespace Ygg::Meior {

	class TerrainPanel : public TPanel<TerrainPanel>
	{
	public:
		TerrainPanel();
		virtual ~TerrainPanel() override;
		virtual void Initialize() override;
		virtual bool Update() override;
	private:
		void GenerateTerrain();
		void Render();
	private:
		float m_ImageWidth = 512, m_ImageHeight = 512;
		uint32_t m_TerrainSizeX = 200, m_TerrainSizeY = 200, m_LayerCount = 3;
		float m_Lacunarity = 2.0f;
		float m_Persistance = 0.5f;
		float m_PerlinScale = 20.0f;
		float m_MapScale = 0.1f;
		float m_HeightMax = 10.0f;

		bool m_UseGlb = false;
		std::string m_Path = "./terrain";
		glm::vec4 m_MinColor{0.117f, 0.148f, 0.397f, 1.000f};
		glm::vec4 m_MaxColor{0.785f, 0.936f, 0.810f, 1.000f};
	private:
		Scene m_Scene;
		Scope<Framebuffer> m_Framebuffer;
		Camera m_Camera;
	private:
		glm::mat4 m_ModelMatrix = glm::identity<glm::mat4>();
		glm::mat4 m_NormalMatrix = glm::identity<glm::mat4>();
		std::vector<float> m_HeightMap;
	private:
		Ref<Shader> m_Shader = nullptr;
		Ref<Texture> m_Texture = nullptr;
		Ref<Ygg::Meior::Mesh> m_Mesh = nullptr;
	};

} // namespace Ygg::Meior

