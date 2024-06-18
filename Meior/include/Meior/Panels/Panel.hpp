//
// Created by Sayama on 23/05/2024.
//

#pragma once

#include <string>
#include <memory>
#include <functional>
#include <regex>

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

	using PanelCreateFunc = std::function<std::unique_ptr<Panel>(void)>;

	struct PanelCreator
	{
		PanelCreator() = default;
		~PanelCreator() = default;
		PanelCreator(std::string n, PanelCreateFunc c) : name(std::move(n)), create(std::move(c)) {}
		template<class T>
		static PanelCreator Create(PanelCreateFunc c);
		std::string name;
		PanelCreateFunc create;
	};

	template<class T>
	PanelCreator PanelCreator::Create(PanelCreateFunc c) {
		static constexpr const char* const ClassRegexPattern = R"(^\w+\s+(?:\w+::)*(\w+))";
		static const std::regex classRegex(ClassRegexPattern);

		std::string n = typeid(T).name();
		std::smatch result;

		if(std::regex_search(n, result, classRegex)) {
			n = result[1];
		}

		// Should allow snake_case, PascalCase, camelCase, camel_Snake_Case, Pascal_Snake_Case
		static constexpr const char* const NameRegexPattern = R"(^([A-Za-z][a-z\d]*)(?:(_([A-Za-z\d])|([A-Z]))([a-z\d]*))+)";
		static const std::regex nameRegex(ClassRegexPattern);

		// TODO: Parse the name to beautify it.

		return {n, std::move(c)};
	}

	template<typename T>
	class TPanel : public Panel
	{
	public:
		static std::unique_ptr<Panel> CreatePanel() {return std::make_unique<T>();}
		static PanelCreator GetPanelCreator() {return PanelCreator::Create<T>(T::CreatePanel); };
	};

} // namespace Ygg::Meior

