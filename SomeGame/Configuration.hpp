#pragma once

#include <filesystem>
#include <string>
#include "ConfigurationBuilder.hpp"


class WindowConfig
{
	unsigned int width{};
	unsigned int height{};
	std::string title;

public:
	WindowConfig(unsigned int width_,
		unsigned int height_,
		const std::string& title_)
		: width(width_),
		height(height_),
		title(title_)
	{
	}

	WindowConfig() = default;
	WindowConfig(const WindowConfig&) = default;
	WindowConfig& operator= (const WindowConfig&) = default;
	WindowConfig(WindowConfig&&) = default;
	WindowConfig& operator= (WindowConfig&&) = default;

	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }
	std::string getTitle() const { return title; }

};

class PathConfig
{
public:
	using path_t = std::filesystem::path;

private:
	path_t font;
	path_t gfx;
	path_t log;

public:
	PathConfig(const path_t& font_,
		const path_t& gfx_,
		const path_t& log_)
		: font(font_),
		gfx(gfx_),
		log(log_)
	{
	}

	PathConfig() = default;
	PathConfig(const PathConfig&) = default;
	PathConfig& operator= (const PathConfig&) = default;
	PathConfig(PathConfig&&) = default;
	PathConfig& operator= (PathConfig&&) = default;

	path_t getFont() const { return font; }
	path_t getGfx() const { return gfx; }
	path_t getLog() const { return log; }
};

class Configuration : private virtual ConfigurationBuilder
{
	WindowConfig windowConfig;
	PathConfig pathConfig;

public:
	Configuration(const std::filesystem::path& config_file);
	
	void setWindowConfig(unsigned int width, unsigned int height, const std::string& title) override;
	void setPathConfig(const std::string& font, const std::string& gfx, const std::string& path) override;
};