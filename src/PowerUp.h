#pragma once
#include <SFML/Graphics.hpp>

enum class PowerUpType {
    RAPID_FIRE,
    SHIELD,
    EXTRA_LIFE,
    SCORE_BOOST
};

class PowerUp
{
private:
    sf::CircleShape shape;
    PowerUpType type;
    float movementSpeed;
    
    void initShape();
    
public:
    PowerUp(float pos_x, float pos_y, PowerUpType type);
    virtual ~PowerUp();
    
    sf::FloatRect getBounds() const;
    PowerUpType getType() const;
    
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};