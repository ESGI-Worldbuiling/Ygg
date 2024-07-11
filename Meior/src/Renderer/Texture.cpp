//
// Created by Sayama on 20/06/2024.
//

#include "Meior/Renderer/Texture.hpp"
#include "Core/Logger.hpp"
#include <glad/glad.h>


namespace Ygg::Meior {

	class TexSpecHelper
	{
	private:
		Texture2DSpecification& spec;
	public:
		TexSpecHelper(Texture2DSpecification& specification) : spec(specification) {}
		~TexSpecHelper() = default;

		[[nodiscard]] GLenum GetInternalFormat() const
		{
			
			switch (spec.pixelFormat) {
				case RED:
				{
					switch (spec.pixelType) {
						case PX_8: return GL_R8;
						case PX_16: return GL_R16;

						case PX_8UI: return GL_R8UI;
						case PX_16UI: return GL_R16UI;
						case PX_32UI: return GL_R32UI;

						case PX_8I: return GL_R8I;
						case PX_16I: return GL_R16I;
						case PX_32I: return GL_R32I;

						case PX_16F: return GL_R16F;
						case PX_32F: return GL_R32F;
					}
				}
				case RG:
				{
					switch (spec.pixelType) {
						case PX_8: return GL_RG8;
						case PX_16: return GL_RG16;

						case PX_8UI: return GL_RG8UI;
						case PX_16UI: return GL_RG16UI;
						case PX_32UI: return GL_RG32UI;

						case PX_8I: return GL_RG8I;
						case PX_16I: return GL_RG16I;
						case PX_32I: return GL_RG32I;

						case PX_16F: return GL_RG16F;
						case PX_32F: return GL_RG32F;
					}
				}
				case RGB:
				{
					switch (spec.pixelType) {
						case PX_8: return GL_RGB8;
						case PX_16: return GL_RGB16;

						case PX_8UI: return GL_RGB8UI;
						case PX_16UI: return GL_RGB16UI;
						case PX_32UI: return GL_RGB32UI;

						case PX_8I: return GL_RGB8I;
						case PX_16I: return GL_RGB16I;
						case PX_32I: return GL_RGB32I;

						case PX_16F: return GL_RGB16F;
						case PX_32F: return GL_RGB32F;
					}
				}
				case RGBA:
				{
					switch (spec.pixelType) {
						case PX_8: return GL_RGBA8;
						case PX_16: return GL_RGBA16;

						case PX_8UI: return GL_RGBA8UI;
						case PX_16UI: return GL_RGBA16UI;
						case PX_32UI: return GL_RGBA32UI;

						case PX_8I: return GL_RGBA8I;
						case PX_16I: return GL_RGBA16I;
						case PX_32I: return GL_RGBA32I;

						case PX_16F: return GL_RGBA16F;
						case PX_32F: return GL_RGBA32F;
					}
				}
			}

			YGG_WARNING("No valid internal format found. Defaulting to GL_R8.");
			return GL_R8;
		}

		[[nodiscard]] GLenum GetFormat() const
		{
			switch (spec.pixelFormat) {
				case RED: return GL_RED;
				case RG: return GL_RG;
				case RGB: return GL_RGB;
				case RGBA: return GL_RGBA;
			}

			YGG_ASSERT(false, "The pixel format {0} do not exist...", (int)spec.pixelType);
			return GL_RGBA;
		}

		[[nodiscard]] GLenum GetType() const
		{
			
			switch (spec.pixelType) {
				case PX_8: return GL_UNSIGNED_BYTE;
				case PX_16: return GL_UNSIGNED_SHORT;
				case PX_8UI: return GL_UNSIGNED_BYTE;
				case PX_16UI: return GL_UNSIGNED_SHORT;
				case PX_32UI: return GL_UNSIGNED_INT;
				case PX_8I: return GL_BYTE;
				case PX_16I: return GL_SHORT;
				case PX_32I: return GL_INT;
				case PX_16F: return GL_HALF_FLOAT;
				case PX_32F: return GL_FLOAT;
			}

			YGG_ASSERT(false, "The pixel type {0} do not exist...", (int)spec.pixelType);
			return GL_UNSIGNED_BYTE;
		}

		[[nodiscard]] std::string_view GetTypeToString() const
		{
			
			switch (spec.pixelType) {
				case PX_8: return "PX_8";
				case PX_16: return "PX_16";
				case PX_8UI: return "PX_8UI";
				case PX_16UI: return "PX_16UI";
				case PX_32UI: return "PX_32UI";
				case PX_8I: return "PX_8I";
				case PX_16I: return "PX_16I";
				case PX_32I: return "PX_32I";
				case PX_16F: return "PX_16F";
				case PX_32F: return "PX_32F";
			}

			YGG_ASSERT(false, "The pixel type {0} do not exist...", (int)spec.pixelType);
			return "Unknown";
		}

		[[nodiscard]] uint32_t GetPixelSize() const {
			
			switch (spec.pixelType) {
				case PX_8:
				case PX_8UI:
				case PX_8I:
					return 1U;
				case PX_16:
				case PX_16UI:
				case PX_16I:
				case PX_16F:
					return 2U;
				case PX_32UI:
				case PX_32I:
				case PX_32F:
					return 4U;
			}

			YGG_ASSERT(false, "The pixel type {0} do not exist...", (int)spec.pixelType);
			return 1U;
		}

		[[nodiscard]] GLint GetMagFilter() const
		{
			
			switch (spec.filterMag) {

				case Nearest: return GL_NEAREST;
				case Linear: return GL_LINEAR;
			}
			YGG_WARNING("No value found for MagFilter, defaulting to 'Linear'.");
			return GL_LINEAR;
		}

		[[nodiscard]] GLint GetMinFilter() const
		{
			
			switch (spec.filterMin) {

				case Nearest: return GL_NEAREST;
				case Linear: return GL_LINEAR;
			}
			YGG_WARNING("No value found for MinFilter, defaulting to 'Linear'.");
			return GL_LINEAR;
		}

		[[nodiscard]] GLint GetWrapS() const
		{
			
			switch (spec.wrapperS) {
				case Repeat: return GL_REPEAT;
				case ClampToEdge: return GL_CLAMP_TO_EDGE;
				case MirroredRepeat: return GL_MIRRORED_REPEAT;
			}
			YGG_WARNING("No value found for WrapS, defaulting to 'Repeat'.");
			return GL_REPEAT;
		}

		[[nodiscard]] GLint GetWrapT() const
		{
			
			switch (spec.wrapperT) {
				case Repeat: return GL_REPEAT;
				case ClampToEdge: return GL_CLAMP_TO_EDGE;
				case MirroredRepeat: return GL_MIRRORED_REPEAT;
			}
			YGG_WARNING("No value found for WrapT, defaulting to 'Repeat'.");
			return GL_REPEAT;
		}
	};


	Ref<Texture> Texture::Create(Texture2DSpecification spec, Buffer image)
	{
		return CreateRef<Texture>(spec, image);
	}

	Ref<Texture> Texture::Create(Texture2DSpecification spec)
	{
		return CreateRef<Texture>(spec);
	}

	Texture::Texture(Texture2DSpecification spec, Buffer image) : m_Spec(spec)
	{
		CreateTexture();
		SetData(image);
	}

	Texture::Texture(Texture2DSpecification spec) : m_Spec(spec)
	{
		CreateTexture();
	}

	void Texture::CreateTexture() {
		TexSpecHelper helper(m_Spec);

		YGG_ASSERT(m_Spec.channels > 0 && m_Spec.channels < 5, "The number of channel {0} is not handle at the moment.", m_Spec.channels);

		GLenum internalFormat = helper.GetInternalFormat();

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
		glTextureStorage2D(m_RenderID, 1, internalFormat, static_cast<GLsizei>(m_Spec.width), static_cast<GLsizei>(m_Spec.height));

		glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, helper.GetMinFilter());
		glTextureParameteri(m_RenderID, GL_TEXTURE_MAG_FILTER, helper.GetMagFilter());
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_S, helper.GetWrapS());
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_T, helper.GetWrapT());
	}

	void Texture::SetData(Buffer image)
	{
		TexSpecHelper helper(m_Spec);
		GLenum dataFormat = helper.GetFormat();
		GLenum pixelType = helper.GetType();
		YGG_ASSERT(image.data != nullptr, "No data where found on the image.");
		YGG_ASSERT(m_Spec.size() * helper.GetPixelSize() == image.size, "The size of the image ({}) is different from the information of the texture of size {} (width: {}, height: {}, channel: {}, pixelType: '{}')", image.size, m_Spec.size(), m_Spec.width, m_Spec.height, m_Spec.channels, helper.GetTypeToString());
		glTextureSubImage2D(m_RenderID, 0, 0, 0, static_cast<GLsizei>(m_Spec.width), static_cast<GLsizei>(m_Spec.height), dataFormat, pixelType, image.data);
		if(m_Spec.generateMipMaps) {
			glGenerateTextureMipmap(m_RenderID);
		}
	}

	void Texture::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, m_RenderID);
	}
} // Render