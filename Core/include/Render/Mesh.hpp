#pragma once

#include <cmath>
#include "Core/Logger.hpp"
#include "glm/glm.hpp"

namespace Ygg {
	struct Vertex {
		Vertex() = default;
		Vertex(const Vertex&) = default;
		Vertex& operator=(const Vertex&) = default;
		~Vertex() = default;
		Vertex(glm::vec3 pos, glm::vec3 normal = {0,1,0}, glm::vec4 color = {1,1,1,1}, glm::vec2 uv={0,0}) : pos(pos), normal(normal), color(color), uv(uv) {}

		friend bool operator!=(const Vertex& lft, const Vertex& rht) {
			return !(lft == rht);
		}

		friend bool operator==(const Vertex& lft, const Vertex& rht) {
			return std::memcmp(&lft, &rht, sizeof(Vertex)) == 0;
		}

		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec4 color;
		glm::vec2 uv;
	};

	class Mesh {
	public:
		Mesh();
		Mesh(const std::vector<Vertex>& points);
		Mesh(const std::vector<Vertex>& points, const std::vector<uint32_t>& indices);
		~Mesh();
	public:
		void AddTriangle(const std::array<Vertex, 3>& points);
		void AddTriangles(const std::vector<Vertex>& points, std::vector<uint32_t> indices);
		void AddSurface(const std::vector<Vertex>& points);
	public:
		const Vertex* GetVertices() const {return m_vertices.data();}
		const float* GetVerticesFloatPtr() const {return reinterpret_cast<const float *>(m_vertices.data());}
		uint64_t GetVerticesCount() const {return m_vertices.size();}
		const uint32_t* GetIndices() const {return m_indices.data();}
		uint64_t GetIndicesCount() {return m_indices.size();}
	private:
		uint64_t AddVertex(const Vertex& vertex);
	private:
		std::vector<Vertex> m_vertices;
		std::vector<uint32_t> m_indices;
	};
}