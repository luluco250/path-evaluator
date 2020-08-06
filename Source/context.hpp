#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <istream>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

class Context final {
private:
	std::unordered_map<std::string, std::string> _value_map;

public:
	Context();

	Context(std::istream& config_stream);

	std::optional<std::string> try_get_value(std::string_view key) const;

	void set_value(std::string_view key, std::string_view value);

	bool has_value(std::string_view key) const;

};

#endif // Include guard.
