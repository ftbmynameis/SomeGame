#pragma once

#include "Label.hpp"
#include <functional>

namespace gui
{
	class Button : public Label
	{
	public:
		using OnClick = std::function<void(void)>;

		Button(Widget* parent_,
			const sf::Vector2f& position_,
			const sf::Vector2f& size_,
			const std::wstring& text,
			const sf::Font& font,
			unsigned int character_size,
			const OnClick& on_click_);
	protected:
		virtual void onMousePressed(const sf::Event::MouseButtonEvent& mouse_btn_event);
	private:
		OnClick on_click;
	};
} // namespace