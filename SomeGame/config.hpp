#pragma once

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include "io.hpp"

using nlohmann::json;

namespace config
{
	class parse_error : public std::runtime_error
	{
		template <typename... Args>
		static std::string buildString(Args&&... args)
		{
			std::ostringstream builder;
			util::concat(builder, std::forward<Args>(args)...);
			return builder.str();
		}

	public:
		using std::runtime_error::runtime_error;

		template <typename... Args>
		explicit parse_error(Args&&... args)
			: runtime_error(buildString(std::forward<Args>(args)...))
		{
		}
	};

	struct Parser
	{
		virtual Parser* parseNull() = 0;
		virtual Parser* parseBool(bool b) = 0;
		virtual Parser* parseNumber(json::number_integer_t i) = 0;
		virtual Parser* parseNumber(json::number_unsigned_t i) = 0;
		virtual Parser* parseNumber(json::number_float_t d) = 0;
		virtual Parser* parseString(std::string&& str) = 0;
		virtual Parser* parseKey(std::string&& str) = 0;
		virtual Parser* beginObject(std::size_t num_members) = 0;
		virtual Parser* endObject() = 0;
		virtual Parser* beginArray(std::size_t num_elements) = 0;
		virtual Parser* endArray() = 0;
		virtual Parser* parseError(std::size_t pos, const std::string& last_token, const json::exception& excep) = 0;

	protected:
		Parser() = default;
		Parser(Parser&&) = default;
		Parser(const Parser&) = default;
		Parser& operator =(Parser&&) = default;
		Parser& operator =(const Parser&) = default;
		~Parser() = default;
	};

	class RejectingParser : public Parser
	{
	public:
		Parser* parseNull() override;
		Parser* parseBool(bool b) override;
		Parser* parseNumber(json::number_integer_t i) override;
		Parser* parseNumber(json::number_unsigned_t i) override;
		Parser* parseNumber(json::number_float_t d) override;
		Parser* parseString(std::string&& str) override;
		Parser* parseKey(std::string&& str) override;
		Parser* beginObject(std::size_t num_members) override; // NOLINT
		Parser* endObject() override;
		Parser* beginArray(std::size_t num_elements) override; // NOLINT
		Parser* endArray() override;
		Parser* parseError(std::size_t pos, const std::string& last_token, const json::exception& excep) override;
	};

	// Consumer types
	class BoolConsumer : RejectingParser
	{
		Parser* ret;
		bool& val;

	public:
		BoolConsumer(Parser* p, bool& b);

		Parser* parseBool(bool b) override;
	};

	template <typename T>
	class NumberConsumer : public RejectingParser
	{
		Parser* ret;
		T& val;

	public:
		NumberConsumer(Parser* p, T& v)
			: ret(p), val(v)
		{
		}

		Parser* parseNumber(json::number_integer_t i) override
		{
			val = static_cast<T>(i);
			return ret;
		}

		Parser* parseNumber(json::number_unsigned_t i) override
		{
			val = static_cast<T>(i);
			return ret;
		}

		Parser* parseNumber(json::number_float_t i) override
		{
			val = static_cast<T>(i);
			return ret;
		}
	};

	class StringConsumer : public RejectingParser
	{
		Parser* ret;
		std::string& val;

	public:
		StringConsumer(Parser* p, std::string& v);

		Parser* parseString(std::string&& str) override;
	};

	// Parser types
	template <typename Consumer>
	class ArrayParser : public RejectingParser
	{
		Consumer consumer;

	public:
		template <typename... Args>
		explicit ArrayParser(Parser* ret, Args&&... args)
			: consumer(ret, std::forward<Args>(args)...)
		{
		}

		Parser* beginArray(std::size_t elements) override
		{
			return &consumer;
		}
	};

	template <typename Consumer>
	class ObjectParser : public RejectingParser
	{
		Consumer consumer;

	public:
		template <typename... Args>
		explicit ObjectParser(Parser* ret, Args&&... args)
			: consumer(ret, std::forward<Args>(args)...)
		{
		}

		Parser* beginObject(std::size_t elements) override
		{
			return &consumer;
		}
	};

	template <typename Consumer>
	class RootObjectParser : public RejectingParser
	{
		Consumer consumer;

	public:
		template <typename... Args>
		explicit RootObjectParser(Args&&... args)
			: consumer(this, std::forward<Args>(args)...)
		{
		}

		Parser* beginObject(std::size_t elements) override
		{
			return &consumer;
		}
	};

	void read(Parser& parser, std::istream& file);
	void read(Parser& parser, const std::filesystem::path& file);
}