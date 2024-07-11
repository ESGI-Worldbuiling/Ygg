//
// Created by Sayama on 20/06/2024.
//

#pragma once

#include <cstdint>
#include "Core/Buffer.hpp"
#include "Core/SmartPointers.hpp"

namespace Ygg::Meior {

	enum TextureFilter : uint8_t
	{
		Nearest,
		Linear,
	};

	enum TextureWrapper : uint8_t
	{
		Repeat,
		ClampToEdge,
		MirroredRepeat,
	};

	enum PixelFormat : uint8_t
	{
		RED = 1,
		RG = 2,
		RGB = 3,
		RGBA = 4,
	};

	enum PixelType : uint8_t
	{
		PX_8,
		PX_16,

		PX_8UI,
		PX_16UI,
		PX_32UI,

		PX_8I,
		PX_16I,
		PX_32I,

		PX_16F, // This is a Half Float.
		PX_32F,
	};

	struct Texture2DSpecification
	{
		inline Texture2DSpecification() = default;
		inline ~Texture2DSpecification() = default;

		uint32_t width = 0, height = 0, channels = 0;

		TextureFilter filterMag = TextureFilter::Linear;
		TextureFilter filterMin = TextureFilter::Linear;

		TextureWrapper wrapperS = TextureWrapper::Repeat;
		TextureWrapper wrapperT = TextureWrapper::Repeat;

		PixelFormat pixelFormat = PixelFormat::RGBA;
		PixelType pixelType = PixelType::PX_8;

		bool generateMipMaps = true;

		uint64_t size() const {return width * height * channels;}
	};

	class Texture
	{
	public:
		Texture(Texture2DSpecification spec, Buffer image);
		Texture(Texture2DSpecification spec);
		~Texture() = default;

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
	public:
		static Ref<Texture> Create(Texture2DSpecification spec, Buffer image);
		static Ref<Texture> Create(Texture2DSpecification spec);
	public:
		void SetData(Buffer image);
		void Bind(uint32_t slot = 0);
	private:
		void CreateTexture();
	private:
		Texture2DSpecification m_Spec;
		uint32_t m_RenderID = 0;
	};

} // Render
