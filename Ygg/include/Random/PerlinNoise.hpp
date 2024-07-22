//
// Created by ianpo on 22/07/2024.
//

#pragma once

#include <vector>
#include <cmath>
#include <cstdint>
#include <glm/glm.hpp>


namespace Ygg::Perlin {

	class HeightMap {
	public:
		HeightMap(uint64_t width, uint64_t height) : Heights(width*height), Width(width), Height(height) {}
		~HeightMap() = default;
	public:
		 [[nodiscard]] float& operator()(uint64_t x, uint64_t y) {return Heights[GetIndex(x,y)];}
		 [[nodiscard]] const float& operator()(uint64_t x, uint64_t y) const {return Heights[GetIndex(x,y)];}

		 [[nodiscard]] float& at(uint64_t x, uint64_t y) {return Heights.at(GetIndex(x,y));}
		 [[nodiscard]] const float& at(uint64_t x, uint64_t y) const {return Heights.at(GetIndex(x,y));}

		template<typename T, glm::qualifier Q = glm::defaultp>
		[[nodiscard]] float& operator()(glm::vec<2,T, Q> pos) {return Heights[GetIndex(pos)];}
		template<typename T, glm::qualifier Q = glm::defaultp>
		[[nodiscard]] const float& operator()(glm::vec<2,T, Q> pos) const {return Heights[GetIndex(pos)];}

		template<typename T, glm::qualifier Q = glm::defaultp>
		[[nodiscard]] float& at(glm::vec<2,T, Q> pos) {return Heights.at(GetIndex(pos));}
		template<typename T, glm::qualifier Q = glm::defaultp>
		[[nodiscard]] const float& at(glm::vec<2,T, Q> pos) const {return Heights.at(GetIndex(pos));}

	public:
		[[nodiscard]] uint64_t GetIndex(uint64_t x, uint64_t y) const {return y * Width + x;}
		template<typename T, glm::qualifier Q = glm::defaultp>
		[[nodiscard]] uint64_t GetIndex(glm::vec<2,T, Q> pos) const {return pos.y * Width + pos.x;}
	public:
		std::vector<float> Heights;
		uint64_t Width, Height;
	};


}

