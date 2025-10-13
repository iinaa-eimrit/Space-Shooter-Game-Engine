#include "PowerUp.h"

void PowerUp::initShape()
{
    this->shape.setRadius(15.f);
    
    switch (type)
    {
    case PowerUpType::RAPID_FIRE:
        this->shape.setFillColor(sf::Color::Green);
        break;
    case PowerUpType::SHIELD:
        this->shape.setFillColor(sf::Color::Blue);
        break;
    case PowerUpType::EXTRA_LIFE:
        this->shape.setFillColor(sf::Color::Red);
        break;
    case PowerUpType::SCORE_BOOST:
        this->shape.setFillColor(sf::Color::Yellow);
        break;
    }
    
    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(2.f);
}

PowerUp::PowerUp(float pos_x, float pos_y, PowerUpType type) : 
    type(type), movementSpeed(100.f)
{
    this->initShape();
    this->shape.setPosition(pos_x, pos_y);
}

PowerUp::~PowerUp()
{
}

sf::FloatRect PowerUp::getBounds() const
{
    return shape.getGlobalBounds();
}

PowerUpType PowerUp::getType() const
{
    return type;
}

void PowerUp::update(const float& dt)
{
    shape.move(0.f, movementSpeed * dt);
}

void PowerUp::render(sf::RenderTarget* target)
{
    target->draw(shape);
}