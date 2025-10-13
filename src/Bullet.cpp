#include "Bullet.h"

Bullet::Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
    this->shape.setPosition(pos_x, pos_y);
    this->shape.setSize(sf::Vector2f(5.f, 10.f));
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setOrigin(this->shape.getSize().x / 2.f, this->shape.getSize().y / 2.f);
    
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->movementSpeed = movement_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
    return this->shape.getGlobalBounds();
}

void Bullet::update(const float& dt)
{
    this->shape.move(this->direction * this->movementSpeed * dt);
}

void Bullet::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}