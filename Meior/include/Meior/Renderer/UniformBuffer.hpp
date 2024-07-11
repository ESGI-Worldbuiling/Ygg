//
// Created by Sayama on 11/07/2024.
//

#pragma once

#include "Core/Core.hpp"

namespace Ygg::Meior {

	class UniformBuffer {
	public:
		UniformBuffer(uint32_t size, uint32_t binding);
		~UniformBuffer();
		UniformBuffer(const UniformBuffer&) = delete;
		UniformBuffer& operator=(const UniformBuffer&) = delete;
	public:
		template<typename T>
		static UniformBuffer Create(uint32_t binding) {return {sizeof(T), binding};};
		template<typename T>
		static Ref<UniformBuffer> CreateRef(uint32_t binding) {return Ygg::CreateRef<UniformBuffer>(sizeof(T), binding);};
		static Ref<UniformBuffer> CreateRef(uint32_t size, uint32_t binding) {return Ygg::CreateRef<UniformBuffer>(size, binding);};
	public:
		template<typename T>
		void SetData(const T* data) {SetData(data, sizeof(T), 0);}
		void SetData(const void* data, uint32_t size, uint32_t offset = 0);
	private:
		uint32_t m_RenderID = 0;

	};

}// namespace Ygg::Meior
