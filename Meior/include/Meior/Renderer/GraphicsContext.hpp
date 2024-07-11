//
// Created by Sayama on 11/07/2024.
//

#pragma once

#include "Core/Core.hpp"

namespace Ygg::Meior {

	class Window;

	class GraphicsContext {
	public:
		GraphicsContext(Window* windowPtr);
		~GraphicsContext();
		void Init();
		void SwapBuffers();
	private:
		Window* m_WindowPtr = nullptr;
	};

}// namespace Ygg::Meior
