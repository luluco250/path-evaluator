#include "context.hpp"
#include <istream>
#include <optional>
#include <regex>
#include <string>
#include <string_view>

Context::Context() {}

Context::Context(std::istream& config_stream) {
	static const std::regex CommentRegex(R"([#;].*)");
	static const std::regex EntryRegex(R"(\s*(.+?)\s*=\s*(.*))");

	std::string line;
	std::smatch match;

	while (std::getline(config_stream, line)) {
		// Remove comments.
		if (std::regex_match(line, match, CommentRegex))
			line.erase(match.position());

		if (!std::regex_match(line, match, EntryRegex))
			continue;

		_value_map.insert_or_assign(match[1].str(), match[2].str());
	}
}

std::optional<std::string> Context::try_get_value(std::string_view key) const {
	auto iterator = _value_map.find(key.data());

	if (iterator == _value_map.end())
		return {};

	return iterator->second;
}

void Context::set_value(std::string_view key, std::string_view value) {
	_value_map.insert_or_assign(key.data(), value);
}

bool Context::has_value(std::string_view key) const {
	return _value_map.find(key.data()) != _value_map.end();
}
