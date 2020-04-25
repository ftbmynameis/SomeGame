#pragma once

#include "Label.hpp"

namespace gui
{
	class TextBox : public Label
	{
	public:
		TextBox(Widget* parent_,
			const sf::Vector2f& position_,
			const sf::Vector2f& size_,
			const std::wstring& text,
			const sf::Font& font,
			unsigned int character_size);

		void setDrawMarker(bool b);
		void setMarkerColor(const sf::Color& color);

		// todo: what about focus?
		virtual void onTextEntered(sf::Uint32 unicode);
	protected:
		// todo: draw maker doesn't blink and bugs if text is empty
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void updateMarker();

		// todo: a bit intransparent what can be overriden and what not.. clarify!
		// todo: empty string -> marker disappears. should be displayed at alignment center tho
		void computeTextAlignment() override;
	private:
		bool draw_marker{ true };
		sf::RectangleShape render_marker;
		std::size_t typing_idx{ 0 };
	};
}