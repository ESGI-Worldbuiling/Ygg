//
// Created by ianpo on 01/06/2024.
//

#include "Meior/Renderer/Buffer.hpp"
#include "Core/Profiler.hpp"

#include <glad/glad.h>

#include <utility>

namespace Ygg::Meior {

   uint32_t GetBufferDataTypeSize(BufferDataType type) {
      switch (type) {
         case BufferDataType::FLOAT:   return 4 * 1;
         case BufferDataType::FLOAT2:  return 4 * 2;
         case BufferDataType::FLOAT3:  return 4 * 3;
         case BufferDataType::FLOAT4:  return 4 * 4;

         case BufferDataType::MAT2:    return 4 * 2 * 2;
         case BufferDataType::MAT3:    return 4 * 3 * 3;
         case BufferDataType::MAT4:    return 4 * 4 * 4;

         case BufferDataType::INT:     return 4 * 1;
         case BufferDataType::INT2:    return 4 * 2;
         case BufferDataType::INT3:    return 4 * 3;
         case BufferDataType::INT4:    return 4 * 4;

         case BufferDataType::BOOL:    return 1;
      }
      return 0;
   }

   uint32_t GetBufferDataTypeCount(BufferDataType type) {
      switch (type) {
         case BufferDataType::FLOAT:   return 1;
         case BufferDataType::FLOAT2:  return 2;
         case BufferDataType::FLOAT3:  return 3;
         case BufferDataType::FLOAT4:  return 4;

         case BufferDataType::MAT2:    return 2 * 2;
         case BufferDataType::MAT3:    return 3 * 3;
         case BufferDataType::MAT4:    return 4 * 4;

         case BufferDataType::INT:     return 1;
         case BufferDataType::INT2:    return 2;
         case BufferDataType::INT3:    return 3;
         case BufferDataType::INT4:    return 4;

         case BufferDataType::BOOL:    return 1;
      }
      return 0;
   }

   std::string GetBufferDataTypeString(BufferDataType type)
   {
      switch (type) {
         case BufferDataType::FLOAT:   return "BufferDataType::FLOAT";
         case BufferDataType::FLOAT2:  return "BufferDataType::FLOAT2";
         case BufferDataType::FLOAT3:  return "BufferDataType::FLOAT3";
         case BufferDataType::FLOAT4:  return "BufferDataType::FLOAT4";

         case BufferDataType::MAT2:    return "BufferDataType::MAT2";
         case BufferDataType::MAT3:    return "BufferDataType::MAT3";
         case BufferDataType::MAT4:    return "BufferDataType::MAT4";

         case BufferDataType::INT:     return "BufferDataType::INT";
         case BufferDataType::INT2:    return "BufferDataType::INT2";
         case BufferDataType::INT3:    return "BufferDataType::INT3";
         case BufferDataType::INT4:    return "BufferDataType::INT4";

         case BufferDataType::BOOL:    return "BufferDataType::BOOL";
      }
      return "BufferDataType::UNKNOWN";
   }

   BufferElement::BufferElement(BufferDataType type, std::string  name, bool normalized) : Name(std::move(name)), Type(type), Size(GetBufferDataTypeSize(type)), Offset(0), Normalized(normalized)
   {
   }

   uint32_t BufferElement::GetComponentCount() const {
      YGG_PROFILE_FUNCTION();
      return GetBufferDataTypeCount(Type);
   }

   uint64_t BufferLayout::size() const {
      return m_Elements.size();
   }

   BufferElement& BufferLayout::operator[](uint64_t index) {
      return m_Elements[index];
   }

   const BufferElement& BufferLayout::operator[](uint64_t index) const {
      return m_Elements[index];
   }

   void BufferLayout::CalculateOffsetAndStride() {
      YGG_PROFILE_FUNCTION();
      m_Stride = 0;
      for (auto& element:m_Elements) {
         element.Offset = m_Stride;
         m_Stride += element.Size;
      }
   }

   Ref<VertexBuffer> VertexBuffer::Create(Buffer data) {
      YGG_PROFILE_FUNCTION();
      return CreateRef<VertexBuffer>(data);
   }

   Ref<VertexBuffer> VertexBuffer::Create(Buffer data, BufferLayout layout) {
      YGG_PROFILE_FUNCTION();
      return CreateRef<VertexBuffer>(data, layout);
   }

   VertexBuffer::VertexBuffer(Buffer data)
   {
      YGG_PROFILE_FUNCTION();
      glCreateBuffers(1, &m_RenderID);
      glNamedBufferData(m_RenderID, static_cast<GLsizeiptr>(data.size), data.data, GL_STATIC_DRAW);
   }


   VertexBuffer::VertexBuffer(Buffer data, BufferLayout layout) : m_Layout(std::move(layout))
   {
      YGG_PROFILE_FUNCTION();
      glCreateBuffers(1, &m_RenderID);
      glNamedBufferData(m_RenderID, static_cast<GLsizeiptr>(data.size), data.data, GL_STATIC_DRAW);
   }

   VertexBuffer::~VertexBuffer() {
      YGG_PROFILE_FUNCTION();
      glDeleteBuffers(1, &m_RenderID);
      m_RenderID = 0;
   }

   void VertexBuffer::Bind() {
      YGG_PROFILE_FUNCTION();
      glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);

   }

   void VertexBuffer::Unbind() {
      YGG_PROFILE_FUNCTION();
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   void VertexBuffer::SetLayout(const BufferLayout &layout) {
      m_Layout = layout;
   }

   const BufferLayout &VertexBuffer::GetLayout() const {
      return m_Layout;
   }

   uint32_t VertexBuffer::GetRenderID() const {
      return m_RenderID;
   }

   Ref<VertexBuffer> IndexBuffer::Create(Buffer data) {
      return CreateRef<VertexBuffer>(data);
   }

   IndexBuffer::IndexBuffer(Buffer data, IndexDataType type) {
      YGG_PROFILE_FUNCTION();
      glCreateBuffers(1, &m_RenderID);
      glNamedBufferData(m_RenderID, static_cast<GLsizeiptr>(data.size), data.data, GL_STATIC_DRAW);
      uint64_t size = 0;
      switch (type) {
         case IndexDataType::UINT8:
            size = 1;
            break;
         case IndexDataType::UINT16:
            size = 2;
            break;
         case IndexDataType::UINT32:
            size = 4;
            break;
      }
      YGG_ASSERT(size, "The IndexDataType is not defined.");
      m_Count = size ? data.size / size : 0;
      m_Type = type;
   }

   IndexBuffer::~IndexBuffer() {
      YGG_PROFILE_FUNCTION();
      glDeleteBuffers(1, &m_RenderID);
      m_RenderID = 0;
   }

   void IndexBuffer::Bind() {
      YGG_PROFILE_FUNCTION();
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
   }

   void IndexBuffer::Unbind() {
      YGG_PROFILE_FUNCTION();
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }

   uint32_t IndexBuffer::GetRenderID() const {
      return m_RenderID;
   }

   uint32_t IndexBuffer::GetIndexCount() const {
      return m_Count;
   }
} // Render

