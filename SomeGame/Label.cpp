#include "Label.hpp"

namespace gui
{
	Label::Label(Widget* parent_,
		const sf::Vector2f& position_,
		const sf::Vector2f& size_,
		const std::wstring& text,
		const sf::Font& font,
		unsigned int character_size)
		: Widget(parent_, position_, size_, true, false),
		render_text(text, font, character_size),
		render_background(size_)
	{
		render_text.setPosition(getPosition());
		render_background.setPosition(getPosition());
	}

	void Label::setTextString(const std::wstring& str)
	{ 
		render_text.setString(str); 
		computeTextAlignment(); 
	}

	void Label::setTextFont(const sf::Font& font) 
	{ 
		render_text.setFont(font); 
		computeTextAlignment(); 
	}
	
	void Label::setTextCharachterSize(unsigned int character_size) 
	{ 
		render_text.setCharacterSize(character_size);
		computeTextAlignment(); 
	}
	
	void Label::setTextLineSpacing(float spacing_factor) 
	{ 
		render_text.setLineSpacing(spacing_factor); 
		computeTextAlignment(); 
	}
	
	void Label::setTextLetterSpacing(float spacing_factor) 
	{ 
		render_text.setLetterSpacing(spacing_factor); 
		computeTextAlignment(); 
	}
	
	void Label::setTextStyle(sf::Uint32 style) 
	{ 
		render_text.setStyle(style); 
		computeTextAlignment(); 
	}
	
	void Label::setTextColor(const sf::Color& color) 
	{ 
		render_text.setFillColor(color); 
	}
	
	void Label::setTextOutlineColor(const sf::Color& color) 
	{ 
		render_text.setOutlineColor(color); 
	}
	
	void Label::setTextOutlineThickness(float thickness) 
	{ 
		render_text.setOutlineThickness(thickness); 
		computeTextAlignment(); 
	}
	
	void Label::setTextAlignment(bool horizontal, bool vertical)
	{
		alignment_mask = 0;
		if (horizontal) alignment_mask |= 0b1U;
		if (vertical) alignment_mask |= 0b10U;

		computeTextAlignment();
	}

	std::wstring Label::getTextString() const
	{
		return render_text.getString().toWideString();
	}
	
	void Label::setBackgroundColor(const sf::Color& color) 
	{
		render_background.setFillColor(color); 
	}

	void Label::setBorderColor(const sf::Color& color)
	{
		render_background.setOutlineColor(color);
	}

	void Label::setBorderThickness(float thickness)
	{
		render_background.setOutlineThickness(thickness);
	}

	// protected
	void Label::computeTextAlignment()
	{
		// todo: implement text alignment. consider issues with input textbox (empty string..)!
		if (!alignment_mask)
		{
			// no alignment
			render_text.setOrigin(0.0f, 0.0f);
			render_text.setPosition(getPosition());
			return;
		}
		else
		{
			auto lb = render_text.getLocalBounds();
			float cx = 0.0f;
			float cy = 0.0f;
			float x = getPosition().x;
			float y = getPosition().y;

			// horizontal
			if (alignment_mask & 0b1U)
			{
				cx = lb.left + lb.width / 2.0f;
				x = x + getSize().x / 2.0f;
			}
			// vertical
			if (alignment_mask & 0b10U)
			{
				cy = lb.top + lb.height / 2.0f;
				y = y + getSize().y / 2.0f;
			}

			render_text.setOrigin(cx, cy);
			render_text.setPosition(x, y);
		}
	};

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		startDraw(sf::Vector2f(static_cast<float>(target.getSize().x), static_cast<float>(target.getSize().y)));

		target.draw(render_background, states);
		target.draw(render_text, states);

		endDraw();
	};

	const sf::Text& Label::getRenderText() const
	{
		return render_text;
	}

	// private
}