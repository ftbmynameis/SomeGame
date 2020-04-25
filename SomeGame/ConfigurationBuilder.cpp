#include "ConfigurationBuilder.hpp"

#include <array>
#include <memory>
#include <variant>
#include <optional>
#include "config.hpp"

namespace
{
	template <std::size_t _Size>
	inline bool array_all_true(const std::array<bool, _Size>& arr)
	{
		bool result = true;
		for (auto b : arr)
		{
			result = (result && b);
		}

		return result;
	}
} // namespace anonymous


class WindowConfigConsumer : public config::RejectingParser
{
	config::Parser* ret;
	ConfigurationBuilder& builder;
	std::array<bool, 3> var_set{ false, false, false };

	std::variant<std::monostate,
		config::NumberConsumer<unsigned int>,
		config::StringConsumer> consumers;

	unsigned int width{};
	unsigned int height{};
	std::string title;
public:
	WindowConfigConsumer(config::Parser* p, ConfigurationBuilder& builder_)
		: ret(p), builder(builder_)
	{
	}

	Parser* parseKey(std::string&& str) override
	{
		if (str == "width")
		{
			var_set[0] = true;
			return &consumers.emplace<config::NumberConsumer<unsigned int>>(this, width);
		}
		else if (str == "height")
		{
			var_set[1] = true;
			return &consumers.emplace<config::NumberConsumer<unsigned int>>(this, height);
		}
		else if (str == "title")
		{
			var_set[2] = true;
			return &consumers.emplace<config::StringConsumer>(this, title);
		}

		return RejectingParser::parseKey(std::move(str));
	}

	Parser* endObject() override
	{
		if (!array_all_true(var_set))
			throw config::parse_error("window definition missing components");
		else
			builder.setWindowConfig(width, height, title);
		return ret;
	}
};

using WindowConfigParser = config::ObjectParser<WindowConfigConsumer>;

class PathConfigConsumer : public config::RejectingParser
{
	config::Parser* ret;
	ConfigurationBuilder& builder;
	std::array<bool, 3> var_set{ false, false, false };

	std::variant<std::monostate,
		config::StringConsumer> consumers;

	std::string font;
	std::string gfx;
	std::string log;
public:
	PathConfigConsumer(config::Parser* p, ConfigurationBuilder& builder_)
		: ret(p), builder(builder_)
	{
	}

	Parser* parseKey(std::string&& str) override
	{
		if (str == "font")
		{
			var_set[0] = true;
			return &consumers.emplace<config::StringConsumer>(this, font);
		}
		else if (str == "gfx")
		{
			var_set[1] = true;
			return &consumers.emplace<config::StringConsumer>(this, gfx);
		}
		else if (str == "log")
		{
			var_set[2] = true;
			return &consumers.emplace<config::StringConsumer>(this, log);
		}

		return RejectingParser::parseKey(std::move(str));
	}

	Parser* endObject() override
	{
		if (!array_all_true(var_set))
			throw config::parse_error("path definition missing components");
		else
			builder.setPathConfig(font, gfx, log);
		return ret;
	}
};

using PathConfigParser = config::ObjectParser<PathConfigConsumer>;

class ConfigurationConsumer : public config::RejectingParser
{
	config::Parser* ret;
	ConfigurationBuilder& builder;
	std::array<bool, 2> var_set{ false, false };

	std::variant<std::monostate,
		WindowConfigParser,
		PathConfigParser> consumers;

public:
	ConfigurationConsumer(config::Parser* p, ConfigurationBuilder& builder_)
		: ret(p), builder(builder_)
	{
	}

	Parser* parseKey(std::string&& str) override
	{
		if (str == "window")
		{
			var_set[0] = true;
			return &consumers.emplace<WindowConfigParser>(this, builder);
		}
		else if (str == "path")
		{
			var_set[1] = true;
			return &consumers.emplace<PathConfigParser>(this, builder);
		}

		return RejectingParser::parseKey(std::move(str));
	}

	Parser* endObject() override
	{
		if (!array_all_true(var_set))
			throw config::parse_error("missing component definition");
		return ret;
	}
};

using ConfigurationParser = config::RootObjectParser<ConfigurationConsumer>;

void load(ConfigurationBuilder& builder, const std::filesystem::path& config_file)
{
	ConfigurationParser parser(builder);
	config::read(parser, config_file);
}