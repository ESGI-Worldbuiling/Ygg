//
// Created by ianpo on 26/05/2024.
//

#include "Meior/Panels/TerrainPanel.hpp"
#include "Meior/Renderer/Renderer.hpp"
#include "Meior/ImGuiLib.hpp"
#include "Core/Logger.hpp"


namespace Ygg::Meior {
	TerrainPanel::TerrainPanel()
	{
		m_Name = "Terrain Panel";
		m_Camera.Position = {0,25,0};
		m_Camera.Rotation = glm::quatLookAt(Vec3{0,-1,0}, Vec3{0,0,1});
	}

	TerrainPanel::~TerrainPanel() = default;

	bool TerrainPanel::Update() {

		if(m_ImageWidth != 0 && m_ImageHeight != 0) {
			Render();
		}

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

		if(m_Framebuffer) {
			uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
			ImGui::Image(reinterpret_cast<void*>(textureID), {m_ImageWidth, m_ImageHeight}, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		}
//		ImGui::Image

		return changed;
	}

	void TerrainPanel::Render()
	{
		Renderer::RenderScene(m_Scene, m_Framebuffer.get(), &m_Camera, &m_Camera);
	}

} // namespace Ygg::Meior
