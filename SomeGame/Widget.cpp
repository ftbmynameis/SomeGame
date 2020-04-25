#include "Widget.hpp"

namespace gui
{
	Widget::Widget(Widget* parent_,
		const sf::Vector2f& position_,
		const sf::Vector2f& size_,
		bool enabled_,
		bool focusable_)
		: parent(parent_), position(position_), size(size_), state(State::None), enabled(enabled_), focusable(focusable_)
	{
	}

	void Widget::onEvent(const sf::Event & event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			onMousePressed(event.mouseButton);
			break;
		case sf::Event::TextEntered:
			onTextEntered(event.text.unicode);
			break;
		case sf::Event::KeyPressed:
			onKeyPressed(event.key);
			break;
		default:
			break;
		}
	}
	void Widget::onMousePressed(const sf::Event::MouseButtonEvent& mouse_btn_event) {};
	void Widget::onTextEntered(sf::Uint32 unicode) {};
	void Widget::onKeyPressed(const sf::Event::KeyEvent& key_event) {};

	void Widget::enable() { enabled = true; }
	void Widget::disable() { enabled = false; }
	void Widget::setFocusable() { focusable = true; }
	void Widget::setPosition(const sf::Vector2f & position_) { position = position_; }
	void Widget::setSize(const sf::Vector2f & size_) { size = size_; }
	void Widget::setState(State state_) { state = state_; }
	sf::Vector2f Widget::getPosition() const { return parent ? parent->getPosition() + position : position; }
	sf::Vector2f Widget::getSize() const { return size; }
	sf::FloatRect Widget::getBounds() const { return sf::Rect<float>{ getPosition(), getSize() }; }
	Widget::State Widget::getState() const { return state; }
	bool Widget::isEnabled() const { return enabled; }
	bool Widget::isFocusable() const { return focusable; }

	// protected
	void Widget::startDraw(const sf::Vector2f & target_size) const
	{
		const auto bounds = getBounds();
		glEnable(GL_SCISSOR_TEST);
		glScissor(static_cast<GLint>(bounds.left),
			static_cast<GLint>(target_size.y - bounds.top - bounds.height),
			static_cast<GLsizei>(bounds.width),
			static_cast<GLsizei>(bounds.height));
	}
	void Widget::endDraw() const { glDisable(GL_SCISSOR_TEST); }
	void Widget::drawDisabled(sf::RenderTarget& target, sf::RenderStates states) const { draw(target, states); }
} // namespace gui