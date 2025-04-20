#include "Button.hpp"

Button::Button(float x, float y, float width, float height, const std::string &text) {
    shape.setPosition(x, y);
    shape.setSize({width, height});
    shape.setFillColor(sf::Color(100, 100, 100));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);

    font.loadFromFile("arial.ttf");

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(18);
    label.setFillColor(sf::Color::White);
    sf::FloatRect bounds = label.getLocalBounds();
    label.setPosition(x + (width - bounds.width) / 2, y + (height - bounds.height) / 2 - 5);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(label);
}

bool Button::isClicked(sf::Vector2f mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

void Button::setFillColor(sf::Color color) {
    shape.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
    label.setFillColor(color);
}
