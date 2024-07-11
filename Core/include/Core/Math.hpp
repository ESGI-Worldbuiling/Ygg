//
// Created by Sayama on 18/06/2024.
//

#pragma once

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/hash.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

#include <cmath>
#include <cstdint>

using Mat4 = glm::mat4;
using Mat3 = glm::mat3;

using Quat = glm::quat;

using Vec4 = glm::vec4;
using Vec3 = glm::vec3;
using Vec2 = glm::vec2;

namespace Ygg::Math {
	Mat4 TRS(const Vec3& position, const glm::quat& rotation, const Vec3& scale = Vec3(1.0));
	void TRS(Mat4& trs, const Vec3& position, const glm::quat& rotation, const Vec3& scale = Vec3(1.0));
}