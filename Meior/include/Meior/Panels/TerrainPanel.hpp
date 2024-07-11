//
// Created by ianpo on 26/05/2024.
//

#pragma once

#include "Panel.hpp"
#include "Render/Scene.hpp"
#include "Render/Camera.hpp"
#include "Meior/Renderer/Framebuffer.hpp"


namespace Ygg::Meior {

	class TerrainPanel : public TPanel<TerrainPanel>
	{
	public:
		TerrainPanel();
		virtual ~TerrainPanel() override;
		virtual bool Update() override;
	private:
		void Render();
	private:
		Scene m_Scene;
		Scope<Framebuffer> m_Framebuffer;
		Camera m_Camera {16.0f/9.0f};
	private:
		float m_ImageWidth = 0, m_ImageHeight = 0;
		uint32_t m_Width = 512, m_Height = 512;
		bool m_UseGlb = false;
		std::string m_Path = "./terrain";
	};

} // namespace Ygg::Meior

