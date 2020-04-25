#pragma once

#include <filesystem>
#include <string>


struct ConfigurationBuilder
{
public:
	virtual void setWindowConfig(unsigned int width, unsigned int height, const std::string& title) = 0;
	virtual void setPathConfig(const std::string& font, const std::string& gfx, const std::string& log) = 0;

protected:
	ConfigurationBuilder() = default;
	ConfigurationBuilder(ConfigurationBuilder&&) = default;
	ConfigurationBuilder(const ConfigurationBuilder&) = default;
	ConfigurationBuilder& operator =(ConfigurationBuilder&&) = default;
	ConfigurationBuilder& operator =(const ConfigurationBuilder&) = default;
	~ConfigurationBuilder() = default;
};

void load(ConfigurationBuilder& builder, const std::filesystem::path& config_file);