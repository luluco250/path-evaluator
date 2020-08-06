#ifndef MAIN_HPP
#define MAIN_HPP

#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>
#include "context.hpp"

Context create_context();

std::string evaluate_input(std::string_view input, const Context& context);

void evaluate_replace_tilde(std::string& str);

void evaluate_replace_vars(std::string& str, const Context& context);

std::string get_env_var(std::string_view name, std::size_t buffer_size = 1024);

std::filesystem::path get_user_folder_path();

#endif // Include guard.
