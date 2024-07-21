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
		void Render();
	private:
		float m_ImageWidth = 512, m_ImageHeight = 512;
		uint32_t m_Width = 20, m_Height = 20;
		bool m_UseGlb = false;
		std::string m_Path = "./terrain";
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

