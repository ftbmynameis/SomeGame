#include "Button.hpp"


namespace gui
{
	Button::Button(Widget* parent_,
		const sf::Vector2f& position_,
		const sf::Vector2f& size_,
		const std::wstring& text,
		const sf::Font& font,
		unsigned int character_size,
		const OnClick& on_click_)
		: Label(parent_, position_, size_, text, font, character_size),
		on_click(on_click_)
	{
		setFocusable();
	}

	// protected
	void Button::onMousePressed(const sf::Event::MouseButtonEvent& mouse_btn_event)
	{
		if (getBounds().contains(static_cast<float>(mouse_btn_event.x), 
			static_cast<float>(mouse_btn_event.y)) 
			&& on_click)
		{
			on_click();
		}
	}
}