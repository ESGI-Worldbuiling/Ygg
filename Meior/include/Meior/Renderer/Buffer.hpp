//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include "Core/SmartPointers.hpp"
#include "Core/Buffer.hpp"
namespace Ygg::Meior {

   enum class BufferDataType : uint16_t
   {
      FLOAT,
      FLOAT2,
      FLOAT3,
      FLOAT4,
      MAT2,
      MAT3,
      MAT4,
      INT,
      INT2,
      INT3,
      INT4,
      BOOL
   };

   enum class IndexDataType : uint8_t {
      UINT8,
      UINT16,
      UINT32
   };

   [[nodiscard]] uint32_t GetBufferDataTypeSize(BufferDataType type);
   [[nodiscard]] uint32_t GetBufferDataTypeCount(BufferDataType type);
   [[nodiscard]] std::string GetBufferDataTypeString(BufferDataType type);

   struct BufferElement {

      std::string Name;
      BufferDataType Type;
      uint32_t Size;
      uint32_t Offset;
      bool Normalized;

      BufferElement(BufferDataType type, std::string name, bool normalized = false);
      [[nodiscard]] uint32_t GetComponentCount() const;
   };

   class BufferLayout {
   public:
      BufferLayout() : m_Elements(), m_Stride(0) {}
      BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements), m_Stride(0) {
         CalculateOffsetAndStride();
      }

      [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return GetElements().begin();}
      [[nodiscard]] std::vector<BufferElement>::const_iterator end() const { return GetElements().end();}

      [[nodiscard]] const std::vector<BufferElement>& GetElements() const {return m_Elements;}
      [[nodiscard]] uint32_t GetStride() const { return m_Stride; }

      [[nodiscard]] uint64_t size() const;
      BufferElement& operator[](uint64_t index);
      const BufferElement& operator[](uint64_t index) const;

   private:
      void CalculateOffsetAndStride();
   private:
      std::vector<BufferElement> m_Elements;
      uint32_t m_Stride = 0;
   };

   class VertexBuffer {
   public:
      static Ref<VertexBuffer> Create(Buffer data);
      static Ref<VertexBuffer> Create(Buffer data, BufferLayout layout);
   public:
      VertexBuffer(Buffer data);
      VertexBuffer(Buffer data, BufferLayout layout);
      ~VertexBuffer();
      VertexBuffer(const VertexBuffer&) = delete;
      VertexBuffer& operator=(const VertexBuffer&) = delete;
   public:
      uint32_t GetRenderID() const;
      void Bind();
      void Unbind();
      void SetLayout(const BufferLayout& layout);
      [[nodiscard]] const BufferLayout& GetLayout() const;
   private:
      uint32_t m_RenderID = 0;
      BufferLayout m_Layout;
   };

   class IndexBuffer {
   public:
      static Ref<VertexBuffer> Create(Buffer data);
   public:
      IndexBuffer(Buffer data, IndexDataType type = IndexDataType::UINT32);
      ~IndexBuffer();
      IndexBuffer(const IndexBuffer&) = delete;
      IndexBuffer& operator=(const IndexBuffer&) = delete;
   public:
      uint32_t GetRenderID() const;
      void Bind();
      void Unbind();

      uint32_t GetIndexCount() const;
   private:
      uint32_t m_RenderID = 0;
      uint32_t m_Count = 0;
      IndexDataType m_Type;
   };

} // Render
