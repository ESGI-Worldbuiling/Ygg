//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include "Core/SmartPointers.hpp"
#include "Core/Buffer.hpp"
#include "Core/Math.hpp"
#include "Render/Mesh.hpp"
#include "Render/Scene.hpp"
#include "VertexArray.hpp"

namespace Ygg::Meior {

	static inline BufferLayout GetVertexBufferLayout() {
		return {{BufferDataType::FLOAT3, "Position"},
				{BufferDataType::FLOAT3, "Normal"},
				{BufferDataType::FLOAT4, "Color"},
				{BufferDataType::FLOAT2, "UV"}};
	}

	class Mesh {
	public:
		[[nodiscard]] static Ref<Mesh> Create(const std::vector<Vertex>& vertex);
		[[nodiscard]] static Ref<Mesh> Create(const std::vector<Vertex>& vertex, std::vector<uint32_t>& indices);
	public:
		Mesh(const std::vector<Vertex>& vertex);
		Mesh(const std::vector<Vertex>& vertex, std::vector<uint32_t>& indices);
		~Mesh();
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
	public:
		[[nodiscard]] Ref<VertexArray> GetVertexArray() const;
	private:
		void CreateMesh(const std::vector<Vertex>& vertex, std::vector<uint32_t>& indices);
	private:
		Ref<VertexArray> m_VertexArray = nullptr;
	};

} // Render
