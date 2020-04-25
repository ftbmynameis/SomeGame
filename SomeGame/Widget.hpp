#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace gui
{
	class Widget : public sf::Drawable
	{
	public:
		enum class State
		{
			None,
			Focused,
			Hovered
		};

		Widget(Widget* parent_,
			const sf::Vector2f& position_,
			const sf::Vector2f& size_,
			bool enabled_ = true,
			bool focusable_ = true);

		Widget(const Widget&) = delete;
		Widget& operator= (const Widget&) = delete;
		Widget(Widget&&) = default;
		Widget& operator= (Widget&&) = default;

		void onEvent(const sf::Event& event);

		void enable();
		void disable();
		void setFocusable();
		// todo: changed to virtual, adapt derived types!
		// note: is it really neccessary? but otherwise derived type (label) couldn't react properly
		//       on position change
		virtual void setPosition(const sf::Vector2f& position_);
		virtual void setSize(const sf::Vector2f& size_);
		virtual void setState(State state_);
		sf::Vector2f getPosition() const;
		sf::Vector2f getSize() const;
		sf::FloatRect getBounds() const;
		State getState() const;
		bool isEnabled() const;
		bool isFocusable() const;

	protected:
		virtual void onMousePressed(const sf::Event::MouseButtonEvent& mouse_btn_event);
		virtual void onTextEntered(sf::Uint32 unicode);
		virtual void onKeyPressed(const sf::Event::KeyEvent& key_event);

		void startDraw(const sf::Vector2f& target_size) const;
		void endDraw() const;
		virtual void drawDisabled(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		Widget* parent{ nullptr };
		sf::Vector2f position;
		sf::Vector2f size;
		State state{ State::None };
		bool enabled{ true };
		bool focusable{ true }; // todo: does it make sense to change this?
	};
} // namespace gui