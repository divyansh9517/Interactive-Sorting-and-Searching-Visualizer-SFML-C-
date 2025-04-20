#pragma once
#include <SFML/Graphics.hpp>

class Slider {
public:
    Slider(float x, float y, float width, float minValue, float maxValue, float currentValue);

    void draw(sf::RenderWindow &window);
    void update(sf::Vector2f mousePos);
    float getValue() const;

private:
    sf::RectangleShape track;
    sf::RectangleShape thumb;
    sf::Text valueLabel;
    sf::Font font;
    float minValue;
    float maxValue;
    float currentValue;
};
