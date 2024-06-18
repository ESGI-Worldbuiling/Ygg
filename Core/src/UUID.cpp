//
// Created by Sayama on 18/06/2024.
//

#include "Core/UUID.hpp"
#include <random>
#include <cstring>
#include <algorithm>
#include <bit>

namespace Ygg {
	// Necessary element ro create a random 64bits number;
	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_RandomEngine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	UUID::UUID() : m_UUID(s_UniformDistribution(s_RandomEngine))
	{
	}

	UUID::UUID(uint64_t id) : m_UUID(id)
	{
	}

	UUID UUID::FromString(const std::string& str)
	{
		std::hash<std::string> hash_fn;
		auto hash = hash_fn(str);
		return {hash};
	}

	std::string UUID::string() const
	{
		return std::to_string(m_UUID);
	}

	constexpr bool operator==(const UUID &lfs, const UUID &rhs) {
		return std::equal(lfs.m_Data.begin(), lfs.m_Data.end(), rhs.m_Data.begin(), rhs.m_Data.end());
	}

	constexpr bool operator!=(const UUID &lfs, const UUID &rhs) {
		return !(lfs == rhs);
	}
}// namespace Ygg