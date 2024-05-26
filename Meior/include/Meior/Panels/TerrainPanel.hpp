//
// Created by ianpo on 26/05/2024.
//

#pragma once

#include "Panel.hpp"
#include <memory>
#include <filesystem>


namespace Ygg::Meior {

	class TerrainPanel : public Panel
	{
	public:
		TerrainPanel();
		virtual ~TerrainPanel() override;
		virtual bool Update() override;

		static std::unique_ptr<Panel> CreatePanel();
		static inline PanelCreator GetPanelCreator() {return {"Terrain Panel", TerrainPanel::CreatePanel}; };
	private:
		uint32_t m_Width = 512, m_Height = 512;
		bool m_UseGlb = false;
		std::string m_Path = "./terrain";
	};

} // namespace Ygg::Meior

