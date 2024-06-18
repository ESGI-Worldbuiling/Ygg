//
// Created by Sayama on 18/06/2024.
//

#pragma once


#include "Panel.hpp"
#include <memory>
#include <filesystem>

namespace Ygg::Meior {

	class TreePanel : public TPanel<TreePanel>
	{
	public:
		TreePanel();
		virtual ~TreePanel() override;
		virtual bool Update() override;
	private:
	};

} // namespace Ygg::Meior

