#include "main.hpp"
#include <array>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include "context.hpp"
#include "os.hpp"

namespace fs = std::filesystem;

int main() {
	try {
		auto context = create_context();

		std::string user_input;

		while (std::getline(std::cin, user_input))
			std::cout << evaluate_input(user_input, context) << '\n';

		return EXIT_SUCCESS;
	} catch (const std::exception& e) {
		std::cerr << "Fatal error: " << e.what() << '\n';
	} catch (std::string_view msg) {
		std::cerr << "Fatal error: " << msg << '\n';
	} catch (...) {
		std::cerr << "Fatal error: unknown\n";
	}

	return EXIT_FAILURE;
}

Context create_context() {
	std::ifstream config_file("config.ini");

	return config_file.fail() ? Context() : Context(config_file);
}

std::string evaluate_input(std::string_view input, const Context& context) {
	std::string str(input);

	evaluate_replace_vars(str, context);
	evaluate_replace_tilde(str);

	auto path = fs::absolute(str);

	return path.string();
}

void evaluate_replace_tilde(std::string& str) {
	auto tilde_pos = str.find_first_of('~');

	if (tilde_pos == std::string::npos)
		return;

	auto user_path = get_user_folder_path();
	str.replace(tilde_pos, 1, user_path.string());
}

void evaluate_replace_vars(std::string& str, const Context& context) {
	static const std::regex VariableRegex(R"(\$\w+)");

	std::smatch match;
	std::string match_str;
	std::string_view var_name;

	while (std::regex_search(str, match, VariableRegex)) {
		match_str = match.str();
		var_name = std::string_view(match_str).substr(1);

		auto replacement = context
			.try_get_value(var_name)
			.value_or("");

		std::cout << match_str << " -> " << replacement << '\n';

		auto index = match.position();
		auto size = match_str.size();

		str.replace(index, index + size, replacement);
	}
}

std::string get_env_var(std::string_view name, std::size_t buffer_size) {
	std::string buffer(buffer_size, '\0');
	std::size_t written;

	::getenv_s(&written, buffer.data(), buffer.size(), name.data());
	buffer.erase(written - 1);

	return buffer;
}

fs::path get_user_folder_path() {
	auto env_var = (CurrentOS == OperatingSystem::Windows)
		? "USERPROFILE"
		: "HOME";

	return fs::path(get_env_var(env_var));
}
