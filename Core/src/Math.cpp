//
// Created by Sayama on 11/07/2024.
//

#include "Core/Macro.hpp"
#include "Core/Math.hpp"
#include "Core/Logger.hpp"
#include "Core/Profiler.hpp"

namespace Ygg::Math {
	Mat4 TRS(const Vec3& position, const glm::quat& rotation, const Vec3& scale)
	{
		Mat4 trs = glm::identity<glm::mat4>();
		TRS(trs, position, rotation, scale);
		return trs;
	}

	void TRS(Mat4& trs, const Vec3& position, const glm::quat& rotation, const Vec3& scale)
	{
		YGG_PROFILE_FUNCTION();
		trs = glm::translate(trs, position); // Translation Matrix
		trs = trs * glm::toMat4(rotation); // Rotation Matrix
		if(scale.x != 1 && scale.y != 1 && scale.z != 1)
			trs = glm::scale(trs, scale); // Scale Matrix
	}

}