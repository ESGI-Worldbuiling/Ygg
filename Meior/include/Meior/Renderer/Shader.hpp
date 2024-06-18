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
#include <string>
#include <unordered_map>

namespace Ygg::Meior {

   class Shader {
   public:
      enum Type : uint8_t
      {
         COMPUTE = 0,
         VERTEX,
         TESS_CONTROL,
         TESS_EVALUATION,
         GEOMETRY,
         FRAGMENT
      };
      static const constexpr inline uint8_t TypeCount = 6;
   public:
      static Ref<Shader> Create(std::unordered_map<Type, std::string> sources);
      static Ref<Shader> Create(std::string vertexShader, std::string fragmentShader);
   public:
      Shader(std::unordered_map<Type, std::string> sources);
      Shader(std::string vertexShader, std::string fragmentShader);
      ~Shader();
      Shader(const Shader&) = delete;
      Shader operator=(const Shader&) = delete;
   public:
      void Bind();
      void Unbind();
      [[nodiscard]] uint32_t GetRenderID() const;
   public:
      void SetUniformMat4(const std::string& name, const Mat4& matrix);
      void SetUniformMat3(const std::string& name, const Mat3& matrix);
      void SetUniformVec4(const std::string& name, const Vec4& matrix);
      void SetUniformVec3(const std::string& name, const Vec3& matrix);
   private:
      bool CompileShaders();
      bool LinkShaders();
   private:
      uint32_t m_RenderID = 0;
      std::array<std::string, TypeCount> m_Sources;
      std::array<std::optional<uint32_t>, TypeCount> m_Shaders;
   };

   std::string ShaderSourceTypeToString(Shader::Type sst);

} // Render
