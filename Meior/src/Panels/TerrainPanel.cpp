//
// Created by ianpo on 26/05/2024.
//

#include "Meior/Panels/TerrainPanel.hpp"
#include "Meior/ImGuiLib.hpp"
#include "Core/Logger.hpp"


namespace Ygg::Meior {
	TerrainPanel::TerrainPanel()
	{
		m_Name = "Terrain Panel";
	}

	TerrainPanel::~TerrainPanel() = default;

	bool TerrainPanel::Update() {
		bool changed = false;

		changed |= ImGui::DragScalar("Width", ImGuiDataType_U32, &m_Width);
		changed |= ImGui::DragScalar("Height", ImGuiDataType_U32, &m_Height);
		changed |= ImGui::Checkbox("Use GLB", &m_UseGlb);
		changed |= ImGuiLib::InputText("Path", &m_Path);

		//TODO: Draw a viewport of the currently generated terrain in flat color.

		if(ImGui::Button("Generate")) {
			std::string extension = m_UseGlb ? "glb" : "gltf";
			YGG_INFO("Should generate a terrain ({}x{}) at path {}.{}.", m_Width, m_Height, m_Path, extension);
		}

		return changed;
	}
} // namespace Ygg::Meior
