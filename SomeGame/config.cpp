#include "config.hpp"
#include <streambuf>

namespace
{
	class ConfigHandler : public json::json_sax_t
	{
		config::Parser* parser;
	public:
		explicit ConfigHandler(config::Parser& p)
			: parser(&p)
		{
		}

		bool null() override
		{
			parser = parser->parseNull();
			return true;
		}

		bool boolean(bool val) override
		{
			parser = parser->parseBool(val);
			return true;
		}

		bool number_integer(number_integer_t val) override
		{
			parser = parser->parseNumber(val);
			return true;
		}

		bool number_unsigned(number_unsigned_t val) override
		{
			parser = parser->parseNumber(val);
			return true;
		}

		bool number_float(number_float_t val, const string_t& s) override
		{
			parser = parser->parseNumber(val);
			return true;
		}

		bool string(string_t& val) override
		{
			parser = parser->parseString(std::move(val));
			return true;
		}

		bool start_object(std::size_t elements) override
		{
			parser = parser->beginObject(elements);
			return true;
		}

		bool end_object() override
		{
			parser = parser->endObject();
			return true;
		}

		bool start_array(std::size_t elements) override
		{
			parser = parser->beginArray(elements);
			return true;
		}

		bool end_array() override
		{
			parser = parser->endArray();
			return true;
		}

		bool key(string_t& val) override
		{
			parser = parser->parseKey(std::move(val));
			return true;
		}

		bool parse_error(std::size_t position, const std::string& last_token, const json::exception& ex) override
		{
			parser = parser->parseError(position, last_token, ex);
			return false;
		}
	};
} // namespace anonymous

namespace config
{
	Parser* RejectingParser::parseNull()
	{
		throw parse_error{ "unexpected" };
	}

	Parser* RejectingParser::parseBool(bool b)
	{
		throw parse_error{ b, " : unexpected" };
	}

	Parser* RejectingParser::parseNumber(json::number_integer_t i)
	{
		throw parse_error{ i, " : number unexpected" };
	}

	Parser* RejectingParser::parseNumber(json::number_unsigned_t i)
	{
		throw parse_error{ i, " : number unexpected" };
	}
	
	Parser* RejectingParser::parseNumber(json::number_float_t d)
	{
		throw parse_error{ d, " : number unexpected" };
	}

	Parser* RejectingParser::parseString(std::string&& str)
	{
		throw parse_error{ "unexpected string '", str, '\'' };
	}

	Parser* RejectingParser::parseKey(std::string&& str)
	{
		throw parse_error{ "unexpected key '", str, '\'' };
	}

	Parser* RejectingParser::beginObject(std::size_t num_members)
	{
		throw parse_error{ "unexpected object" };
	}

	Parser* RejectingParser::endObject()
	{
		return nullptr;
	}

	Parser* RejectingParser::beginArray(std::size_t num_elements)
	{
		throw parse_error{ "unexpected array" };
	}

	Parser* RejectingParser::endArray()
	{
		return nullptr;
	}

	Parser* RejectingParser::parseError(std::size_t pos, const std::string& last_token, const json::exception& excep)
	{
		throw parse_error{ "unexpected parse error" };
	}

	BoolConsumer::BoolConsumer(Parser* p, bool& b)
		: ret(p), val(b)
	{
	}

	Parser* BoolConsumer::parseBool(bool b)
	{
		val = b;
		return ret;
	}

	StringConsumer::StringConsumer(Parser* p, std::string& v)
		: ret(p), val(v)
	{
	}

	Parser* StringConsumer::parseString(std::string&& str)
	{
		val = str;
		return ret;
	}

	void read(Parser& parser, std::istream& file)
	{
		std::string txt((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		ConfigHandler handler{ parser };
		json::sax_parse(txt, &handler, json::input_format_t::json, true);
	}

	void read(Parser& parser, const std::filesystem::path& file)
	{
		std::ifstream stream(file, std::ios::binary);

		if (!stream)
			throw std::runtime_error("failed to open config file");

		read(parser, stream);
	}
} // namespace config