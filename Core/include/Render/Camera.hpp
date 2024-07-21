//
// Created by Sayama on 11/07/2024.
//

#pragma once

#include "Core/Math.hpp"

namespace Ygg {

	class IProjection {
	public:
		virtual ~IProjection() = default;
		[[nodiscard]] virtual glm::mat4 GetProjectionMatrix() const = 0;
	};

	class IView {
	public:
		virtual ~IView() = default;
		[[nodiscard]] virtual glm::mat4 GetViewMatrix() const = 0;
	};

	class Camera : public IProjection, public IView {
	public:
		Camera() = default;
		explicit Camera(uint32_t width, uint32_t height, float radianFov = glm::radians(60.0f), float nearClip = 0.001f, float farClip = 1000.0f);
		explicit Camera(float aspectRatio, float radianFov = glm::radians(60.0f), float nearClip = 0.001f, float farClip = 1000.0f);
		~Camera() = default;

	public:
		[[nodiscard]] virtual glm::mat4 GetProjectionMatrix() const override;
		[[nodiscard]] virtual glm::mat4 GetViewMatrix() const override;

		[[nodiscard]] glm::vec3 GetUp() const {return Rotation * glm::vec3{0,1,0};}
		[[nodiscard]] glm::vec3 GetForward() const {return Rotation * glm::vec3{0,0,1};}
	public:
		glm::vec3 Position{};
		glm::quat Rotation{};

		/// FOV in radians
		float RadFov = glm::radians(60.0f);
		float AspectRatio = 16.0f/9.0f;
		float Near = 0.001f;
		float Far = 1000.0f;
	};

}// namespace Ygg
