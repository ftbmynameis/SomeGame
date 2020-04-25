
#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include "Configuration.hpp"

#include "Button.hpp"

int GameFunc()
{
	using namespace std::chrono;
	// Resource folders
	std::string config_path = "C:/Users/ftbmy/Documents/Development/Projects/CS2D_ReImplement/CS2D_Resources/config/";

	sf::RenderWindow window(sf::VideoMode(800, 600), L"Title");

	const std::string main_config_path = "../../resources/config/test.json";
	Configuration game_config{ main_config_path };

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	gui::Button test{ nullptr,sf::Vector2f(100.0f, 100.0f), sf::Vector2f(500.0f, 300.0f), L"test", font, 30,
	[]() { std::cout << "click!\n"; } };
	test.setBackgroundColor(sf::Color::Green);
	test.setTextColor(sf::Color::Red);
	test.setBorderColor(sf::Color::Magenta);
	test.setBorderThickness(-2.0f);

	long long ticks = 0;
	double global_t = 0.0;
	double dt = 0.01;
	high_resolution_clock::time_point current_time = high_resolution_clock::now();
	double accumulator = 0.0;

	while (window.isOpen())
	{
		high_resolution_clock::time_point new_time = high_resolution_clock::now();
		duration<double> time_span = new_time - current_time;
		current_time = new_time;
		accumulator += time_span.count();

		// GAME LOOP
		// Perform multiple integration steps if the game is lagging behind
		int integration_count = 0;
		while (accumulator >= dt)
		{
			accumulator -= dt;
			// Process events
			// This doesnt make sense to do multiple times...
			// TODO: decouple input and event processing from integration?
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Close window: exit
				if (event.type == sf::Event::Closed)
					window.close();

				// TODO: one button could trigger to seperate events.. not sure if a reasonable "feature"..
				test.onEvent(event);
			}
			global_t += dt;

			// DO UPDATE
			
			integration_count++;
		}
		if (integration_count > 1) std::cout << "Multiple integrations: " << integration_count << std::endl;

		// DO RENDERING

		// Clear screen
		window.clear();

		window.draw(test);

		window.display();
		ticks++;
	}

	return 0;
}

int main()
{
	try
	{
		GameFunc();
	}
	catch (std::exception& e)
	{
		std::cout << "error: " << e.what() << std::endl;
#ifdef _WIN32
		OutputDebugStringA((std::string(e.what()) + '\n').c_str());
#endif
		return -1;
	}
	catch (...)
	{
		std::cout << "unknow exception\n" << std::flush;
#ifdef _WIN32
		OutputDebugStringA("unknow exception\n");
#endif
		return -1;
	}
	return EXIT_SUCCESS;
}