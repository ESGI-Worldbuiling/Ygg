//
// Created by Sayama on 18/06/2024.
//

#pragma once

#include "UUID.hpp"

namespace Ygg {

	using AssetHandle = UUID;

	class Asset {
	public:
		AssetHandle m_Handle;
	};
}
