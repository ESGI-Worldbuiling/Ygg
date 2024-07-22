//
// Created by ianpo on 26/05/2024.
//

#include "Meior/Panels/TerrainPanel.hpp"
#include "Core/Logger.hpp"
#include "Meior/ImGuiLib.hpp"
#include "Meior/Renderer/Mesh.hpp"
#include "Meior/Renderer/Renderer.hpp"
#include "Meior/Renderer/ShadersCpp/DefaultShaders.hpp"
#include "TerrainGenerator.hpp"
#include "glad/glad.h"


namespace Ygg::Meior {
	TerrainPanel::TerrainPanel() : m_Camera(m_ImageWidth / m_ImageHeight)
	{
		m_Name = "Terrain Panel";
		m_Camera.Position = {15,20,-10};
		m_Camera.Rotation = glm::quatLookAt(glm::normalize(-m_Camera.Position), Vec3{0,1,0});

		FramebufferSpecification spec{uint32_t(m_ImageWidth), uint32_t(m_ImageHeight)};
		spec.Attachements = {
				FramebufferTextureFormat::Color,
				FramebufferTextureFormat::Depth
		};

		m_Framebuffer = CreateScope<Framebuffer>(spec);
	}

	TerrainPanel::~TerrainPanel() = default;
	void TerrainPanel::Initialize() {
		m_Shader = Shader::Create(Shaders::c_DefaultVert, Shaders::c_DefaultFrag);

		GenerateTerrain();
		Render();
	}
	bool TerrainPanel::Update() {

		bool changed = false;
		bool generateParamChanged = false;

		changed |= generateParamChanged |= ImGui::DragScalar("Size X", ImGuiDataType_U32, &m_TerrainSizeX);
		changed |=  generateParamChanged |= ImGui::DragScalar("Size Y", ImGuiDataType_U32, &m_TerrainSizeY);
		changed |=  generateParamChanged |= ImGui::DragFloat("Height", &m_HeightMax, 0.1, 0.001, FLT_MAX);
		changed |=  generateParamChanged |= ImGui::DragScalar("Layer Count", ImGuiDataType_U32, &m_LayerCount);
		changed |=  generateParamChanged |= ImGui::DragFloat("Perlin Scale", &m_PerlinScale, 0.25, 0.001, FLT_MAX);
		changed |=  generateParamChanged |= ImGui::DragFloat("Map Scale", &m_MapScale, 0.1, 0.001, FLT_MAX);
		changed |=  generateParamChanged |= ImGui::SliderFloat("Lacunarity", &m_Lacunarity, 0.001, 10);
		changed |=  generateParamChanged |= ImGui::SliderFloat("Persistance", &m_Persistance, 0.001, 1.000);
		changed |= ImGui::Checkbox("Use GLB", &m_UseGlb);
		changed |= ImGuiLib::InputText("Path", &m_Path);
		ImGui::Separator();
		bool colorChanged = false;
		changed |= colorChanged |= ImGui::ColorEdit4("Min Color", glm::value_ptr(m_MinColor));
		changed |= colorChanged |= ImGui::ColorEdit4("Max Color", glm::value_ptr(m_MaxColor));
		ImGui::Separator();

		//TODO: Draw a viewport of the currently generated terrain in flat color.

		if(generateParamChanged || colorChanged) {
			GenerateTerrain();
			Render();
		}

		ImGui::BeginDisabled(m_HeightMap.empty());
		if(ImGui::Button("Save")) {
			auto gltf = TerrainGenerator::generateGLTFModel(m_HeightMap, m_TerrainSizeX, m_TerrainSizeY, m_MapScale, m_MinColor, m_MaxColor);
			auto path = m_Path + (m_UseGlb ? ".glb" : ".gltf");
			TerrainGenerator::saveModel(path, gltf);
			YGG_INFO("Model {} save.", path);
		}
		ImGui::EndDisabled();

		if(m_Framebuffer) {
			uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
			ImGui::Image(reinterpret_cast<void*>(textureID), {m_ImageWidth, m_ImageHeight}, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		}

		return changed;
	}

	void TerrainPanel::GenerateTerrain() {
		m_HeightMap = TerrainGenerator::generateHeightMap(m_TerrainSizeX, m_TerrainSizeY, m_HeightMax, m_PerlinScale, m_Lacunarity, m_Persistance, m_LayerCount);
		auto mesh = TerrainGenerator::generateMesh(m_HeightMap, m_TerrainSizeX, m_TerrainSizeY, m_MapScale, m_MinColor, m_MaxColor);
		m_Mesh = Ygg::Meior::Mesh::Create(mesh.GetRawVertices(), mesh.GetRawIndices());
		m_ModelMatrix[3] = {-float(m_TerrainSizeX)/2,0,-float(m_TerrainSizeY)/2,1};
		m_ModelMatrix[3][0] *= m_MapScale;
		m_ModelMatrix[3][2] *= m_MapScale;
	}


	void TerrainPanel::Render() {
		if (!m_Mesh || !m_Framebuffer || !m_Shader) return;

		m_Framebuffer->Bind();
		glClearColor(0.14, 0.14, 0.14, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		auto vao = m_Mesh->GetVertexArray();

		m_Shader->Bind();

		glm::mat4 p = m_Camera.GetProjectionMatrix();
		m_Shader->SetUniformVec3("u_CamPos", m_Camera.Position);
		m_Shader->SetUniformVec3("u_CamFwd", m_Camera.GetForward());
		m_Shader->SetUniformVec3("u_CamUp", m_Camera.GetUp());

		m_Shader->SetUniformVec4("u_ColorMin", m_MinColor);
		m_Shader->SetUniformVec4("u_ColorMax", m_MaxColor);
		if (!m_HeightMap.empty()) {
			m_Shader->SetUniformFloat("u_HeightMin", *std::min_element(m_HeightMap.begin(), m_HeightMap.end()));
			m_Shader->SetUniformFloat("u_HeightMax", *std::max_element(m_HeightMap.begin(), m_HeightMap.end()));
		}
		if(m_Texture) {
			m_Texture->Bind();
			m_Shader->SetUniformTexture("u_Texture", 0);
		}

		m_Shader->SetUniformMat4("u_ProjectionMatrix", p);
		m_Shader->SetUniformMat4("u_ModelMatrix", m_ModelMatrix);
		m_Shader->SetUniformMat4("u_NormalMatrix", m_NormalMatrix);

		vao->Bind();

		glDrawElements(GL_TRIANGLES, vao->GetDrawCount(), GL_UNSIGNED_INT, nullptr);

		vao->Unbind();
		m_Shader->Unbind();
		m_Framebuffer->Unbind();
	}

} // namespace Ygg::Meior
