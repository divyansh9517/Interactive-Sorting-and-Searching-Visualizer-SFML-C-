#include "Slider.hpp"

Slider::Slider(float x, float y, float width, float minValue, float maxValue, float currentValue)
    : minValue(minValue), maxValue(maxValue), currentValue(currentValue) {
    
    track.setPosition(x, y);
    track.setSize(sf::Vector2f(width, 10));
    track.setFillColor(sf::Color(150, 150, 150));

    thumb.setSize(sf::Vector2f(20, 20));
    thumb.setFillColor(sf::Color(100, 100, 255));
    thumb.setPosition(x + (currentValue - minValue) / (maxValue - minValue) * width, y - 5);

    font.loadFromFile("arial.ttf");

    valueLabel.setFont(font);
    valueLabel.setCharacterSize(14);
    valueLabel.setFillColor(sf::Color::White);
    valueLabel.setString(std::to_string(static_cast<int>(currentValue)));
    valueLabel.setPosition(x + width + 10, y - 5);
}

void Slider::draw(sf::RenderWindow &window) {
    window.draw(track);
    window.draw(thumb);
    window.draw(valueLabel);
}

void Slider::update(sf::Vector2f mousePos) {
    if (track.getGlobalBounds().contains(mousePos)) {
        float newX = mousePos.x - track.getPosition().x;
        currentValue = minValue + (newX / track.getSize().x) * (maxValue - minValue);
        if (currentValue < minValue) currentValue = minValue;
        if (currentValue > maxValue) currentValue = maxValue;

        thumb.setPosition(track.getPosition().x + (currentValue - minValue) / (maxValue - minValue) * track.getSize().x, track.getPosition().y - 5);
        valueLabel.setString(std::to_string(static_cast<int>(currentValue)));
    }
}

float Slider::getValue() const {
    return currentValue;
}
