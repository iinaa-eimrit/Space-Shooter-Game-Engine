#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

struct Particle
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float lifetime;
    float maxLifetime;
    float size;
};

class ParticleSystem
{
private:
    std::vector<Particle> particles;
    sf::VertexArray vertices;
    std::mt19937 randomEngine;
    
    bool emitting;
    sf::Vector2f emitterPosition;
    
public:
    ParticleSystem();
    ~ParticleSystem();
    
    void setEmitterPosition(const sf::Vector2f& position);
    void createExplosion(const sf::Vector2f& position, int count = 50);
    void createTrail(const sf::Vector2f& position, const sf::Vector2f& direction);
    void update(float dt);
    void render(sf::RenderTarget& target);
    
    bool isEmitting() const;
    void stopEmitting();
};