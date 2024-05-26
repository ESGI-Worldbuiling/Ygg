//
// Created by Sayama on 23/05/2024.
//

#pragma once

#include "Meior/Panel.hpp"
#include "Meior/Renderer/Renderer.hpp"
#include "Meior/Renderer/Window.hpp"

#include <vector>
#include <memory>


namespace Ygg::Meior {

	class Application {
	public:
		Application(const WindowProps&);
		~Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void Run();
	private:
		void DrawMenuBar();
	private:
		std::unique_ptr<Window> m_Window = nullptr;
		std::vector<PanelCreator> m_PanelCreators {};
		std::vector<std::unique_ptr<Panel>> m_Panels {};
	};

} // Meior
// Ygg
