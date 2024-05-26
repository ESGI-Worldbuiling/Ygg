//
// Created by Sayama on 23/05/2024.
//


#include "Core/Logger.hpp"
#include "Core/Macro.hpp"
#include "Meior/Application.hpp"
#include "Meior/ImGuiLib.hpp"
#include "Meior/Panels/TerrainPanel.hpp"




// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
	#pragma comment(lib, "legacy_stdio_definitions")
#endif



namespace Ygg::Meior {
	Application::Application(const WindowProps& props) : m_Window(std::make_unique<Window>(props))
	{
		ImGuiLib::Initalize("#version 460", *m_Window);
		m_PanelCreators.push_back(TerrainPanel::GetPanelCreator());
	}

	Application::~Application() {
		ImGuiLib::Destroy();
	}

	void Application::Run()
	{
		// Our state
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGuiIO& io = ImGui::GetIO();

		while (!m_Window->ShouldClose())
		{
			m_Window->PollEvents();

			Renderer::Clear();

			// Start the Dear ImGui frame
			ImGuiLib::BeginFrame();

			ImGuiLib::UseDockSpace(YGG_BIND_EVENT_FN(DrawMenuBar));

			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			if(show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);


			for (int i = 0; i < m_Panels.size(); ++i)
			{
				auto& panel = m_Panels[i];
				ImGui::Begin(panel->m_Name.c_str(), &panel->m_Open);
				{
					panel->Update();
				}
				ImGui::End();

				if(!panel->m_Open) {
					panel->Destroy();
					m_Panels.erase(m_Panels.begin() + i);
					--i;
				}

			}

			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}

			// 3. Show another simple window.
			if (show_another_window)
			{
				ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
				ImGui::Text("Hello from another window!");
				if (ImGui::Button("Close Me"))
					show_another_window = false;
				ImGui::End();
			}

			// Rendering
			ImGuiLib::EndFrame(m_Window->GetWindowProps().Width, m_Window->GetWindowProps().Height);
			m_Window->SwapBuffers();
		}
	}


	void Application::DrawMenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				if(ImGui::MenuItem("Exit"))
				{
					m_Window->Close();
				}

				ImGui::Separator();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Panels"))
			{
				// TODO: allow to create all the panel.
				for (const auto& panelCreator : m_PanelCreators) {
					if(ImGui::MenuItem(panelCreator.name.c_str())) {
						m_Panels.emplace_back(panelCreator.create());
						m_Panels.back()->Initialize();
					}
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

} // Meior
// Ygg