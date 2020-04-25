#pragma once

#include "Widget.hpp"
#include <array>

namespace gui
{
	class Label : public Widget
	{
	public:
		Label(Widget* parent_,
			const sf::Vector2f& position_,
			const sf::Vector2f& size_,
			const std::wstring& text, // todo: really wstring? or string.. or u16/32 string...
			const sf::Font& font,
			unsigned int character_size);

		void setTextString(const std::wstring& str);
		void setTextFont(const sf::Font& font);
		void setTextCharachterSize(unsigned int character_size);
		void setTextLineSpacing(float spacing_factor);
		void setTextLetterSpacing(float spacing_factor);
		void setTextStyle(sf::Uint32 style);
		void setTextColor(const sf::Color& color);
		void setTextOutlineColor(const sf::Color& color);
		void setTextOutlineThickness(float thickness);
		void setTextAlignment(bool horizontal, bool vertical = false);
		// todo: implement sf::Text getters
		std::wstring getTextString() const;

		void setBackgroundColor(const sf::Color& color);
		void setBorderColor(const sf::Color& color);
		void setBorderThickness(float thickness);
		// todo: implement getters

	protected:
		virtual void computeTextAlignment();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		const sf::Text& getRenderText() const;
	private:
		sf::RectangleShape render_background;
		sf::Text render_text;
		unsigned int alignment_mask{ 0 };
	};
} // namesapce gui