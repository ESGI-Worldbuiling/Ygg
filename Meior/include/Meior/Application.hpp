//
// Created by Sayama on 23/05/2024.
//

#pragma once

#include "Meior/Panel.hpp"

#include <vector>
#include <memory>

struct GLFWwindow;

namespace Ygg::Meior {

	class Application {
	public:
		Application();
		~Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void Run();
	private:
		void DrawMenuBar();
	private:
		uint32_t m_Width = 1280, m_Height = 720;
		GLFWwindow* m_Window = nullptr;
		std::vector<PanelCreator> m_PanelCreators;
		std::vector<std::unique_ptr<Panel>> m_Panels;
	};

} // Meior
// Ygg
