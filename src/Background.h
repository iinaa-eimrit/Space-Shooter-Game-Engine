#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

struct Star
{
    sf::Vector2f position;
    float speed;
    sf::Color color;
    float size;
};

class Background
{
private:
    std::vector<Star> stars;
    sf::RectangleShape gradientBackground;
    
    void initStars(int count);
    void initBackground();
    
public:
    Background();
    void update(float dt);
    void render(sf::RenderTarget& target);
};