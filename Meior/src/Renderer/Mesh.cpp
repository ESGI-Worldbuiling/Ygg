//
// Created by ianpo on 01/06/2024.
//

#include "Meior/Renderer/Mesh.hpp"
#include "Core/Profiler.hpp"

namespace Ygg::Meior {

   Ref<Mesh> Mesh::Create(const std::vector<Vertex> &vertex) {
      return CreateRef<Mesh>(vertex);
   }

   Ref<Mesh> Mesh::Create(const std::vector<Vertex> &vertex, std::vector<uint32_t> &indices) {
      return CreateRef<Mesh>(vertex, indices);
   }

   Mesh::Mesh(const std::vector<Vertex> &vertex) {
      YGG_PROFILE_FUNCTION();
      std::vector<uint32_t> indices(vertex.size());
      for (int i = 0; i < vertex.size(); ++i) indices[i] = i;
      CreateMesh(vertex, indices);
   }

   Mesh::Mesh(const std::vector<Vertex> &vertex, std::vector<uint32_t> &indices) {
      CreateMesh(vertex, indices);
   }


   Ref<VertexArray> Mesh::GetVertexArray() const {
      return m_VertexArray;
   }

   void Mesh::CreateMesh(const std::vector<Vertex> &vertex, std::vector<uint32_t> &indices)
   {
      YGG_PROFILE_FUNCTION();
      m_VertexArray = CreateRef<VertexArray>();

      Ref<IndexBuffer> indexBuffer = CreateRef<IndexBuffer>(Buffer{indices.data(), indices.size()});
      m_VertexArray->SetIndexBuffer(indexBuffer);

      Ref<VertexBuffer> vertexBuffer = CreateRef<VertexBuffer>(Buffer{const_cast<Vertex*>(vertex.data()), vertex.size()});
      vertexBuffer->SetLayout(GetVertexBufferLayout());
      m_VertexArray->AddVertexBuffer(vertexBuffer);
   }

   Mesh::~Mesh() = default;

} // Render