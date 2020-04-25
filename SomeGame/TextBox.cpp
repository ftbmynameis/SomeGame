#include "TextBox.hpp"

namespace gui
{
	TextBox::TextBox(Widget* parent_,
		const sf::Vector2f& position_,
		const sf::Vector2f& size_,
		const std::wstring& text,
		const sf::Font& font,
		unsigned int character_size)
		: Label(parent_, position_, size_, text, font, character_size)
	{
		setFocusable(); // label def is not
		typing_idx = getTextString().size();
	}

	void TextBox::setDrawMarker(bool b)
	{
		draw_marker = b;
	}

	void TextBox::setMarkerColor(const sf::Color& color)
	{
		render_marker.setFillColor(color);
	}

	void TextBox::onTextEntered(sf::Uint32 unicode)
	{
		switch (unicode)
		{
		case '\b':
			if (getRenderText().getString().getSize() > 0)
			{
				auto str{ getTextString() };
				str.erase(typing_idx - 1, 1);
				typing_idx = typing_idx - 1;
				setTextString(str);
			}
			break;
		case '\r':
			// Submit
			break;
		case '\t':
			break; // Invalid in console
		default:
			if (unicode > 30 && unicode < 128)
			{
				setTextString(getTextString() + static_cast<std::wstring::value_type>(unicode));
				typing_idx = typing_idx + 1;
			}
			break;
		}

		// update alignment
		computeTextAlignment();
	}

	// protected
	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (isEnabled())
		{
			Label::draw(target, states);

			// draw marker
			target.draw(render_marker, states);
		}
	}

	void TextBox::updateMarker()
	{
		const auto& rt = getRenderText();
		auto text_lb = rt.getLocalBounds();

		const float marker_w = 1.0f;
		const float marker_h = text_lb.top + text_lb.height;
		render_marker.setSize(sf::Vector2f(marker_w, marker_h));
		const auto char_pos = rt.findCharacterPos(typing_idx);
		render_marker.setPosition(char_pos);
	}

	void TextBox::computeTextAlignment()
	{
		Label::computeTextAlignment();
		updateMarker();
	}
}