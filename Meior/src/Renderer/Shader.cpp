//
// Created by ianpo on 01/06/2024.
//

#include "Meior/Renderer/Shader.hpp"
#include "Core/Profiler.hpp"
#include <algorithm>
#include <glad/glad.h>

namespace Ygg::Meior {

   GLenum ShaderSourceTypeToGLType(Shader::Type sst)
   {
      switch (sst) {

         case Shader::Type::COMPUTE: return GL_COMPUTE_SHADER;
         case Shader::Type::VERTEX: return GL_VERTEX_SHADER;
         case Shader::Type::TESS_CONTROL: return GL_TESS_CONTROL_SHADER;
         case Shader::Type::TESS_EVALUATION: return GL_TESS_EVALUATION_SHADER;
         case Shader::Type::GEOMETRY: return GL_GEOMETRY_SHADER;
         case Shader::Type::FRAGMENT: return GL_FRAGMENT_SHADER;
      }
      YGG_ASSERT(false, "Unknown ShaderSource type {}", (int)sst);
      return 0;
   }

   Ref<Shader> Shader::Create(std::unordered_map<Type, std::string> sources)
   {
      return CreateRef<Shader>(sources);
   }

   Ref<Shader> Shader::Create(std::string vertexShader, std::string fragmentShader)
   {
      return CreateRef<Shader>(vertexShader, fragmentShader);
   }

   Shader::Shader(std::unordered_map<Shader::Type, std::string> sources)
   {
      for (int i = 0; i < TypeCount; ++i) {
         m_Sources[i] = std::move(sources[(Type)i]);
      }
      YGG_ASSERT(!m_Sources.empty(), "No can be created as there is no source.");
      CompileShaders();
      LinkShaders();
   }

   Shader::Shader(std::string vertexShader, std::string fragmentShader)
   {
      m_Sources[Type::FRAGMENT] = std::move(fragmentShader);
      m_Sources[Type::VERTEX] = std::move(vertexShader);
      YGG_ASSERT(!m_Sources.empty(), "No can be created as there is no source.");
      CompileShaders();
      LinkShaders();
   }

   bool Shader::CompileShaders() {
      YGG_ASSERT(!m_Sources.empty(), "No can be created as there is no source.");
      if(m_Sources.empty()) return false;

      for (uint8_t i = 0; i < TypeCount; ++i)
      {
         Type type = (Type)i;
         const std::string& source = m_Sources[i];
         if(source.empty()) continue;

         m_Shaders[type] = glCreateShader(ShaderSourceTypeToGLType(type));
         const char* c_source = m_Sources[type].c_str();
         YGG_ASSERT(m_Sources[type].size() < INT_MAX, "Cannot handle shader source greater than {}.", INT_MAX);
         int size = static_cast<int>(m_Sources[type].size());
         glShaderSource(m_Shaders[type].value(), 1, &c_source, &size);
         glCompileShader(m_Shaders[type].value());

         GLint vertex_compiled;
         glGetShaderiv(m_Shaders[type].value(), GL_COMPILE_STATUS, &vertex_compiled);
         if (vertex_compiled != GL_TRUE)
         {
            GLint TotalLenght=0;
            glGetShaderiv(m_Shaders[type].value(), GL_INFO_LOG_LENGTH, &TotalLenght);
            std::vector<char> logs(TotalLenght);
            glGetShaderInfoLog(m_Shaders[type].value(), TotalLenght, nullptr, logs.data());
            YGG_ERROR("{} - Shader Compilation Failed:\n{}", ShaderSourceTypeToString(type), logs.data());
            return false;
         }
      }

      return std::any_of(m_Shaders.begin(), m_Shaders.end(), [&](const auto &item) { return item;});
   }

   bool Shader::LinkShaders() {
      m_RenderID = glCreateProgram();

      for (const auto& shader : m_Shaders) {
         if(shader) {
            glAttachShader(m_RenderID, shader.value());
         }
      }

      glLinkProgram(m_RenderID);

      GLint program_linked;
      GLint vertex_compiled;
      glGetProgramiv(m_RenderID, GL_LINK_STATUS, &vertex_compiled);
      if (vertex_compiled != GL_TRUE)
      {
         GLint TotalLenght=0;
         glGetShaderiv(m_RenderID, GL_INFO_LOG_LENGTH, &TotalLenght);
         std::vector<char> logs(TotalLenght);
         glGetProgramInfoLog(m_RenderID, TotalLenght, nullptr, logs.data());
         YGG_ERROR("Shader Linking Failed:\n{}", logs.data());
         return false;
      }
      return true;
   }

   Shader::~Shader() {
      for (auto& shader : m_Shaders) {
         if (shader) {
            glDeleteShader(shader.value());
            shader = std::nullopt;
         }
      }
      glDeleteProgram(m_RenderID);
   }

   void Shader::Bind()
   {
      glUseProgram(m_RenderID);
   }

   void Shader::Unbind()
   {
      glUseProgram(0);
   }

   uint32_t Shader::GetRenderID() const
   {
      return m_RenderID;
   }

   void Shader::SetUniformMat4(const std::string &name, const Mat4 &matrix) {
      YGG_PROFILE_FUNCTION();
      auto location = glGetUniformLocation(m_RenderID, name.c_str());
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
   }

   void Shader::SetUniformMat3(const std::string &name, const Mat3 &matrix) {
      YGG_PROFILE_FUNCTION();
      auto location = glGetUniformLocation(m_RenderID, name.c_str());
      glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
   }

   void Shader::SetUniformVec4(const std::string &name, const Vec4 &matrix) {
      YGG_PROFILE_FUNCTION();
      auto location = glGetUniformLocation(m_RenderID, name.c_str());
      glUniform4fv(location, 1, glm::value_ptr(matrix));
   }

   void Shader::SetUniformVec3(const std::string &name, const Vec3 &matrix) {
      YGG_PROFILE_FUNCTION();
      auto location = glGetUniformLocation(m_RenderID, name.c_str());
      glUniform3fv(location, 1, glm::value_ptr(matrix));
   }

   std::string ShaderSourceTypeToString(Shader::Type sst) {
      switch (sst) {

         case Shader::Type::COMPUTE:           return "COMPUTE";
         case Shader::Type::VERTEX:            return "VERTEX";
         case Shader::Type::TESS_CONTROL:      return "TESS_CONTROL";
         case Shader::Type::TESS_EVALUATION:   return "TESS_EVALUATION";
         case Shader::Type::GEOMETRY:          return "GEOMETRY";
         case Shader::Type::FRAGMENT:          return "FRAGMENT";
      }
      YGG_ASSERT(false, "Unknown ShaderSource type {}", (int)sst);
      return "UNKNOWN";
   }
} // Render