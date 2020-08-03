#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>
#include <string_view>
#include <filesystem>

std::string evaluate_input(std::string_view input);

std::string get_env_var(std::string_view name);

std::filesystem::path get_user_folder_path();

#endif // Include guard.
