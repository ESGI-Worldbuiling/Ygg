#include "Render/Mesh.hpp"

#include <algorithm>

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
		m_indices.push_back(AddVertex(points[0]));
		m_indices.push_back(AddVertex(points[1]));
		m_indices.push_back(AddVertex(points[2]));
	}
	void Mesh::AddTriangles(const std::vector<Vertex> &points, std::vector<uint32_t> indices) {
		uint64_t offset = m_vertices.size();
		std::for_each(indices.begin(), indices.end(), [offset](uint32_t& indice) {indice += offset;});
		m_vertices.insert(m_vertices.end(), points.begin(), points.end());
		m_indices.insert(m_indices.begin(), indices.begin(), indices.end());
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

	uint64_t Mesh::AddVertex(const Vertex &vertex) {
		auto it = std::find(m_vertices.begin(), m_vertices.end(), vertex);
		if(it == m_vertices.end()) {
			m_vertices.push_back(vertex);
			return m_vertices.size() - 1;
		} else {
			return std::distance(m_vertices.begin(), it);
		}
	}
}