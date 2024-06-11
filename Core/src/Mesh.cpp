#include "Render/Mesh.hpp"

namespace Ygg {
	Mesh::Mesh() {}

	Mesh::Mesh(const std::vector<Vertex> &points) {
		YGG_ASSERT(points.size() % 3 == 0, "Not enough vertices");
		m_vertices = points;
	}

	Mesh::Mesh(const std::vector<Vertex> &points, const std::vector<uint32_t> &indices) {
		YGG_ASSERT(indices.size() % 3 == 0, "Not enough indices");
		m_vertices = points;
		m_indices = indices;
	}

	Mesh::~Mesh() {}

	void Mesh::AddTriangle(const std::array<Vertex, 3> &points) {
		m_indices.push_back(m_vertices.size() + 0);
		m_indices.push_back(m_vertices.size() + 1);
		m_indices.push_back(m_vertices.size() + 2);
		m_vertices.insert(m_vertices.end(),points.begin(), points.end());
	}

	void Mesh::AddSurface(const std::vector<Vertex> &points) {
		YGG_ASSERT(points.size() > 3, "Not enough vertices");
		const int offset = m_vertices.size();
		const int firstPoint = 0;
		int lastPoint = 1;
		for(int i = 2; i < points.size(); ++i) {
			m_indices.push_back(offset + firstPoint);
			m_indices.push_back(offset + lastPoint);
			m_indices.push_back(offset + i);
			lastPoint = i;
		}
		m_vertices.insert(m_vertices.end(), points.begin(), points.end());
	}
}