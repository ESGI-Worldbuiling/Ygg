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

		std::vector<Vertex> cube {
				//Front Face
				Vertex(glm::vec3({-0.5f, -0.5f, +0.5f}), glm::vec3({0,0,+1}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,0})), // 0
				Vertex(glm::vec3({+0.5f, -0.5f, +0.5f}), glm::vec3({0,0,+1}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,1})), // 1
				Vertex(glm::vec3({+0.5f, +0.5f, +0.5f}), glm::vec3({0,0,+1}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,1})), // 2
				Vertex(glm::vec3({-0.5f, +0.5f, +0.5f}), glm::vec3({0,0,+1}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,0})), // 3
				//Front Face
				Vertex(glm::vec3({-0.5f, -0.5f, -0.5f}), glm::vec3({0,0,-1}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,0})), // 4
				Vertex(glm::vec3({+0.5f, -0.5f, -0.5f}), glm::vec3({0,0,-1}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,1})), // 5
				Vertex(glm::vec3({+0.5f, +0.5f, -0.5f}), glm::vec3({0,0,-1}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,1})), // 6
				Vertex(glm::vec3({-0.5f, +0.5f, -0.5f}), glm::vec3({0,0,-1}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,0})), // 7
				//Up Face
				Vertex(glm::vec3({-0.5f, +0.5f, -0.5f}), glm::vec3({0,+1, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,0})), // 8
				Vertex(glm::vec3({+0.5f, +0.5f, -0.5f}), glm::vec3({0,+1, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,1})), // 9
				Vertex(glm::vec3({+0.5f, +0.5f, +0.5f}), glm::vec3({0,+1, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,1})), // 10
				Vertex(glm::vec3({-0.5f, +0.5f, +0.5f}), glm::vec3({0,+1, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,0})), // 11
				//Down Face
				Vertex(glm::vec3({-0.5f, -0.5f, -0.5f}), glm::vec3({0,-1, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,0})), // 12
				Vertex(glm::vec3({+0.5f, -0.5f, -0.5f}), glm::vec3({0,-1, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,1})), // 13
				Vertex(glm::vec3({+0.5f, -0.5f, +0.5f}), glm::vec3({0,-1, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,1})), // 14
				Vertex(glm::vec3({-0.5f, -0.5f, +0.5f}), glm::vec3({0,-1, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,0})), // 15
				//Right Face
				Vertex(glm::vec3({+0.5f, -0.5f, -0.5f}), glm::vec3({+1, 0, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,0})), // 16
				Vertex(glm::vec3({+0.5f, +0.5f, -0.5f}), glm::vec3({+1, 0, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,1})), // 17
				Vertex(glm::vec3({+0.5f, +0.5f, +0.5f}), glm::vec3({+1, 0, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,1})), // 18
				Vertex(glm::vec3({+0.5f, -0.5f, +0.5f}), glm::vec3({+1, 0, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,0})), // 19
				//Left Face
				Vertex(glm::vec3({-0.5f, -0.5f, -0.5f}), glm::vec3({-1, 0, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,0})), // 20
				Vertex(glm::vec3({-0.5f, +0.5f, -0.5f}), glm::vec3({-1, 0, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({0,1})), // 21
				Vertex(glm::vec3({-0.5f, +0.5f, +0.5f}), glm::vec3({-1, 0, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,1})), // 22
				Vertex(glm::vec3({-0.5f, -0.5f, +0.5f}), glm::vec3({-1, 0, 0}), glm::vec4({0.8, 0.2, 0.3, 1.0}), glm::vec2({1,0})), // 23
		};

		std::vector<uint32_t> vertices {
				// Front
				0,2,1,
				0,3,2,
				// Back
				4,5,6,
				4,6,7,
				// Up
				8,9,10,
				8,10,11,
				// Down
				12,14,13,
				12,15,14,
				// Front
				16,18,17,
				16,19,18,
				// Back
				20,21,22,
				20,22,23,
		};

		//      std::vector<Vertex> cube {
		//            Vertex(glm::vec3({-0.5f, -0.5f, 0.0f}), glm::vec3({0,0,1}), glm::vec2({0,0})), // 0
		//            Vertex(glm::vec3({+0.5f, -0.5f, 0.0f}), glm::vec3({0,0,1}), glm::vec2({1,0})), // 1
		//            Vertex(glm::vec3({+0.5f, +0.5f, 0.0f}), glm::vec3({0,0,1}), glm::vec2({1,1})), // 2
		//            Vertex(glm::vec3({-0.5f, +0.5f, 0.0f}), glm::vec3({0,0,1}), glm::vec2({0,1})), // 3
		//      };
		//
		//      std::vector<uint32_t> vertices {
		//            0,1,2,
		//            0,2,3
		//      };

		m_Mesh = Ygg::Meior::Mesh::Create(cube, vertices);
//		m_Shader = Shader::Create(c_VertexShader, c_FragmentShader);
		m_Shader = Shader::Create(Shaders::c_DefaultVert, Shaders::c_DefaultFrag);

	}
	bool TerrainPanel::Update() {

		Render();

		bool changed = false;

		changed |= ImGui::DragScalar("Width", ImGuiDataType_U32, &m_Width);
		changed |= ImGui::DragScalar("Height", ImGuiDataType_U32, &m_Height);
		changed |= ImGui::Checkbox("Use GLB", &m_UseGlb);
		changed |= ImGuiLib::InputText("Path", &m_Path);

		//TODO: Draw a viewport of the currently generated terrain in flat color.

		if(ImGui::Button("Generate")) {
			std::string extension = m_UseGlb ? "glb" : "gltf";
			m_HeightMap = TerrainGenerator::generateHeightMap(m_Width, m_Height);
			auto mesh = TerrainGenerator::generateMesh(m_HeightMap, m_Width, m_Height);
			m_Mesh = Ygg::Meior::Mesh::Create(mesh.GetRawVertices(), mesh.GetRawIndices());
			m_ModelMatrix[3] = {-float(m_Width)/2,0,-float(m_Height)/2,1};
			YGG_INFO("Should generate a terrain ({}x{}) at path {}.{}.", m_Width, m_Height, m_Path, extension);
		}

		ImGui::BeginDisabled(m_HeightMap.empty());
		if(ImGui::Button("Save")) {
			auto gltf = TerrainGenerator::generateGLTFModel(m_HeightMap, m_Width, m_Height);
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

	void TerrainPanel::Render()
	{
		if(!m_Mesh || !m_Framebuffer || !m_Shader) return;

		m_Framebuffer->Bind();
		glClearColor(0.2, 0.3, 0.8, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		auto vao = m_Mesh->GetVertexArray();

		m_Shader->Bind();

		glm::mat4 p = m_Camera.GetProjectionMatrix();
		m_Shader->SetUniformVec3("u_CamPos", m_Camera.Position);
		m_Shader->SetUniformVec3("u_CamFwd", m_Camera.GetForward());
		m_Shader->SetUniformVec3("u_CamUp", m_Camera.GetUp());

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
