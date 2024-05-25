//
// Created by Sayama on 23/05/2024.
//

#pragma once

#include <string>
#include <memory>
#include <functional>

namespace Ygg::Meior {

	class Application;
	class Panel
	{
	public:
		friend class Application;
	public:
		virtual ~Panel() {}
		virtual bool Update() = 0;
		virtual void Initialize() {};
		virtual void Destroy() {};
	protected:
		std::string m_Name = "Panel";
		bool m_Open = true;
	};

	struct PanelCreator
	{
		std::string name;
		std::function<std::unique_ptr<Panel>(void)> create;
	};

} // namespace Ygg::Meior

