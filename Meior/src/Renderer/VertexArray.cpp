//
// Created by ianpo on 01/06/2024.
//

#include "Meior/Renderer/VertexArray.hpp"
#include "Core/Profiler.hpp"

#include <glad/glad.h>

#include <utility>

namespace Ygg::Meior {
   GLenum BufferDataTypeToOpenGLBaseType(BufferDataType type)
   {
      switch (type) {
         case BufferDataType::FLOAT:     return GL_FLOAT;
         case BufferDataType::FLOAT2:    return GL_FLOAT;
         case BufferDataType::FLOAT3:    return GL_FLOAT;
         case BufferDataType::FLOAT4:    return GL_FLOAT;

         case BufferDataType::MAT2:      return GL_FLOAT;
         case BufferDataType::MAT3:      return GL_FLOAT;
         case BufferDataType::MAT4:      return GL_FLOAT;

         case BufferDataType::INT:       return GL_INT;
         case BufferDataType::INT2:      return GL_INT;
         case BufferDataType::INT3:      return GL_INT;
         case BufferDataType::INT4:      return GL_INT;

         case BufferDataType::BOOL:      return GL_BOOL;
      }
      YGG_ASSERT(false, "Unknown ShaderDataType {0}.", (int)type);
      return 0;
   }

   Ref<VertexArray> VertexArray::Create() {
      return CreateRef<VertexArray>();
   }

   VertexArray::VertexArray()
   {
      YGG_PROFILE_FUNCTION();
      glCreateVertexArrays(1, &m_RenderID);
   }

   VertexArray::~VertexArray() {
      YGG_PROFILE_FUNCTION();
      glDeleteVertexArrays(1, &m_RenderID);
   }

   void VertexArray::Bind() {
      YGG_PROFILE_FUNCTION();
      glBindVertexArray(m_RenderID);
   }

   void VertexArray::Unbind() {
      YGG_PROFILE_FUNCTION();
      glBindVertexArray(0);
   }

   std::optional<uint32_t > VertexArray::AddVertexBuffer(Ref<VertexBuffer> vb) {
      YGG_PROFILE_FUNCTION();
      if(!vb) return std::nullopt;
      uint32_t vbIndex = m_VertexBuffer.size();
      bool result = SetVertexBuffer(vbIndex, vb);
      return result ? std::optional<uint32_t >{vbIndex} : std::nullopt;
   }

   bool VertexArray::SetVertexBuffer(uint32_t vbIndex, Ref<VertexBuffer> vb) {
      YGG_PROFILE_FUNCTION();
      if(!vb) return false;

      for (uint32_t i = m_VertexBuffer.size(); i <= vbIndex; ++i) {
         m_VertexBuffer.emplace_back(nullptr);
      }
      m_VertexBuffer[vbIndex] = std::move(vb);

      const BufferLayout& layout = m_VertexBuffer[vbIndex]->GetLayout();
      uint32_t layoutOffset = 0;
      for (int i = 0; i < vbIndex; ++i) layoutOffset += (m_VertexBuffer[i] ? m_VertexBuffer[i]->GetLayout().GetStride() : 0u);

      glVertexArrayVertexBuffer(m_RenderID, vbIndex, m_VertexBuffer.back()->GetRenderID(), 0, static_cast<GLsizei>(layout.GetStride()));
      const auto elementCount = layout.size();
      for (uint32_t i = layoutOffset; i < layoutOffset+elementCount; ++i) {
         const auto& element = layout[i];
         glEnableVertexArrayAttrib(m_RenderID, i);
         glVertexAttribPointer(i, static_cast<GLint>(element.GetComponentCount()), BufferDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, static_cast<GLsizei>(layout.GetStride()), (const void*)(layoutOffset + element.Offset));
      }
      return true;
   }
   void VertexArray::RemoveVertexBuffer(uint32_t vbIndex) {
      YGG_PROFILE_FUNCTION();
      if(m_VertexBuffer.size() <= vbIndex) return;
      if(!m_VertexBuffer[vbIndex]) return;

      const BufferLayout& layout = m_VertexBuffer[vbIndex]->GetLayout();
      uint32_t layoutOffset = 0;
      for (int i = 0; i < vbIndex; ++i) layoutOffset += (m_VertexBuffer[i] ? m_VertexBuffer[i]->GetLayout().GetStride() : 0u);

      const auto elementCount = layout.size();
      for (uint32_t i = layoutOffset; i < layoutOffset+elementCount; ++i) {
         glDisableVertexArrayAttrib(m_RenderID, i);
      }
      glVertexArrayVertexBuffer(m_RenderID, vbIndex, 0, 0, static_cast<GLsizei>(layout.GetStride()));

      m_VertexBuffer[vbIndex] = nullptr;
   }

   void VertexArray::SetIndexBuffer(Ref<IndexBuffer> vb) {
      YGG_PROFILE_FUNCTION();
      m_IndexBuffer = std::move(vb);
      glVertexArrayElementBuffer(m_RenderID, m_IndexBuffer ? m_IndexBuffer->GetRenderID() : 0);
   }

   uint32_t VertexArray::GetRenderID() const {
      return m_RenderID;
   }

   uint32_t VertexArray::GetDrawCount() const {
      return m_IndexBuffer ? m_IndexBuffer->GetIndexCount() : 0;
   }

} // Render