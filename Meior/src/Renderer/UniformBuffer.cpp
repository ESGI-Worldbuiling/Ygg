//
// Created by Sayama on 11/07/2024.
//

#include "Meior/Renderer/UniformBuffer.hpp"
#include <glad/glad.h>

namespace Ygg::Meior {
	UniformBuffer::UniformBuffer(uint32_t size, uint32_t binding)
	{
		YGG_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RenderID);
		glNamedBufferData(m_RenderID, size, nullptr, GL_DYNAMIC_DRAW); // TODO: investigate usage hint
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RenderID);
	}

	UniformBuffer::~UniformBuffer()
	{
		YGG_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RenderID);
	}

	void UniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		YGG_PROFILE_FUNCTION();
		glNamedBufferSubData(m_RenderID, offset, size, data);
	}
}// namespace Ygg::Meior
