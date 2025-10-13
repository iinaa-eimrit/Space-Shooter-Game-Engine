#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
    sf::RectangleShape shape;
    sf::Vector2f direction;
    float movementSpeed;
    
public:
    Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
    virtual ~Bullet();
    
    const sf::FloatRect getBounds() const;
    
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};