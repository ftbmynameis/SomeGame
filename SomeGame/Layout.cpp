#include "Layout.hpp"

namespace gui
{
	Layout::Layout(Widget* parent_,
		const sf::Vector2f& position_,
		const sf::Vector2f& size_)
		: Widget(parent_, position_, size_)
	{
		render_background.setPosition(getPosition());
		render_background.setSize(getSize());
	}

	void Layout::setBackgroundColor(const sf::Color& color)
	{
		render_background.setFillColor(color);
	}

	void Layout::setBorderColor(const sf::Color& color)
	{
		render_background.setOutlineColor(color);
	}

	void Layout::setBorderThickness(float thickness)
	{
		render_background.setOutlineThickness(thickness);
	}

	void Layout::onMousePressed(const sf::Event::MouseButtonEvent& mouse_btn_event)
	{
		for (auto& child : children)
		{
			child.second->onMousePressed(mouse_btn_event);
		}
	}

	void Layout::onTextEntered(sf::Uint32 unicode)
	{
		for (auto& child : children)
		{
			child.second->onTextEntered(unicode);
		}
	}

	void Layout::onKeyPressed(const sf::Event::KeyEvent& key_event)
	{
		for (auto& child : children)
		{
			child.second->onKeyPressed(key_event);
		}
	}

	// protected:
	void Layout::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(render_background, states);
		for (const auto& child : children)
		{
			target.draw(*child.second.get(), states);
		}
	}

	
} // namespace gui