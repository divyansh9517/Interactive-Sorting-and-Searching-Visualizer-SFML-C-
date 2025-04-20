#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(float x, float y, float width, float height, const std::string &text);
    void draw(sf::RenderWindow &window);
    bool isClicked(sf::Vector2f mousePos);
    void setFillColor(sf::Color color);
    void setTextColor(sf::Color color);

private:
    sf::RectangleShape shape;
    sf::Text label;
    sf::Font font;
};