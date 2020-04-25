#include "Configuration.hpp"


Configuration::Configuration(const std::filesystem::path& config_file)
{
	load(*this, config_file);
}

void Configuration::setWindowConfig(unsigned int width, unsigned int height, const std::string& title)
{
	this->windowConfig = WindowConfig{ width, height, title };
}

void Configuration::setPathConfig(const std::string& font, const std::string& gfx, const std::string& path)
{
	this->pathConfig = PathConfig{ font, gfx, path };
}