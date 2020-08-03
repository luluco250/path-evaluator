#include "main.hpp"
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <filesystem>
#include <cstdlib>
#include <stdexcept>
#include "os.hpp"

namespace fs = std::filesystem;

int main() {
	try {
		std::string user_input;

		while (std::getline(std::cin, user_input))
			std::cout << evaluate_input(user_input) << '\n';

		return EXIT_SUCCESS;
	} catch (const std::exception& e) {
		std::cerr << "Fatal error: " << e.what() << '\n';

		return EXIT_FAILURE;
	}
}

std::string evaluate_input(std::string_view input) {
	std::string str(input);

	auto tilde_pos = str.find_first_of('~');

	if (tilde_pos != std::string::npos) {
		auto user_path = get_user_folder_path();

		str.replace(tilde_pos, 1, user_path.string());
	}

	auto path = fs::absolute(str);

	return path.string();
}

std::string get_env_var(std::string_view name) {
	char buffer[1024];
	auto len = sizeof(buffer);

	::getenv_s(&len, buffer, name.data());

	std::string result(buffer);
	result.shrink_to_fit();

	return result;
}

fs::path get_user_folder_path() {
	auto env_var = (CurrentOS == OperatingSystem::Windows)
		? "USERPROFILE"
		: "HOME";

	return fs::path(get_env_var(env_var));
}
