//
// Created by ianpo on 26/05/2024.
//

#pragma once

#include <string>
#include <cinttypes>

namespace Ygg::Meior {

	struct WindowProps {
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		WindowProps(const std::string& title = "Meior", uint32_t width = 1600, uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window {
	public:
		Window(const WindowProps& props);
		~Window();
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
	public:
		void SwapBuffers();
		void PollEvents();
		[[nodiscard]] bool ShouldClose() const;
		void SetVSync(bool state);
		void Close();
	public:
		template<typename T>
		T* GetNativeWindow() { return reinterpret_cast<T*>(m_Window);}

		template<typename T>
		const T* GetNativeWindow() const { return reinterpret_cast<T*>(m_Window);}

		const WindowProps& GetWindowProps() const {return m_WindowProps;}
	private:
		void* m_Window = nullptr;
		WindowProps m_WindowProps;
	};

} // namespace Ygg::Meior

