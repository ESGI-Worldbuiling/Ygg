//
// Created by Sayama on 18/06/2024.
//

#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <array>

namespace Ygg {

	class UUID
	{
	public:
		UUID();
		UUID(uint64_t);

		UUID(const UUID&) = default;
		UUID& operator=(const UUID&) = default;

		std::string string() const;
		inline operator std::string() const { return string(); }
		static UUID FromString(const std::string&);

		friend constexpr bool operator==(const UUID& lfs, const UUID& rhs);
		friend constexpr bool operator!=(const UUID& lfs, const UUID& rhs);

	private:
		union {
			uint64_t m_UUID;
			std::array<uint8_t, sizeof(m_UUID)> m_Data;
		};
	};


}// namespace Ygg

namespace std
{
	template<>
	struct hash<Ygg::UUID>
	{
		inline std::size_t operator()(const Ygg::UUID& uuid) const
		{
			return std::hash<std::string_view>{}({reinterpret_cast<const char*>(&uuid), sizeof(Ygg::UUID)});
		}
	};
} // namespace std
