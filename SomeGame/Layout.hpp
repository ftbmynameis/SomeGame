#pragma once

#include "Widget.hpp"
#include <map>
#include <memory>
#include <string>

namespace gui
{
	class Layout : public Widget
	{
	public:
		Layout(Widget* parent_,
			const sf::Vector2f& position_,
			const sf::Vector2f& size_);

		template <typename T, typename... Args>
		T* addChild(const std::string& key, Args... f_args)
		{
			children[key] = std::make_unique<T>(this, std::forward<Args>(f_args)...);
			return reinterpret_cast<T*>(children[key].get());
		}

		void setBackgroundColor(const sf::Color& color);
		void setBorderColor(const sf::Color& color);
		void setBorderThickness(float thickness);

		// todo: dumb implementation dispatching to all children -> use focus, enabled/disabled, ...
		void onMousePressed(const sf::Event::MouseButtonEvent& mouse_btn_event) override;
		void onTextEntered(sf::Uint32 unicode) override;
		void onKeyPressed(const sf::Event::KeyEvent& key_event) override;
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		std::map<std::string, std::unique_ptr<Widget>> children;
		Widget* focused_widget{ nullptr }; // todo: focus not implemented yet
		sf::RectangleShape render_background;
	};
}