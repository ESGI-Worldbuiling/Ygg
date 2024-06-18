#pragma once

#include <cmath>
#include "Core/Logger.hpp"
#include "glm/glm.hpp"

namespace Ygg {
	struct Vertex {
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
		void AddTriangles(const std::vector<Vertex>& points, const std::vector<uint32_t >& indices);
		void AddSurface(const std::vector<Vertex>& points);
	private:
		std::vector<Vertex> m_vertices;
		std::vector<uint32_t> m_indices;
	};
}