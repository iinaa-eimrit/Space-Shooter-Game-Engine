#include "ParticleSystem.h"
#include <cmath>

ParticleSystem::ParticleSystem() : 
    vertices(sf::Points), 
    emitting(false),
    randomEngine(std::random_device{}())
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::setEmitterPosition(const sf::Vector2f& position)
{
    emitterPosition = position;
}

void ParticleSystem::createExplosion(const sf::Vector2f& position, int count)
{
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159f);
    std::uniform_real_distribution<float> speedDist(50.0f, 200.0f);
    std::uniform_real_distribution<float> lifetimeDist(0.5f, 2.0f);
    std::uniform_real_distribution<float> sizeDist(1.0f, 4.0f);
    
    for (int i = 0; i < count; ++i)
    {
        Particle particle;
        particle.position = position;
        
        float angle = angleDist(randomEngine);
        float speed = speedDist(randomEngine);
        particle.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        
        particle.lifetime = 0.0f;
        particle.maxLifetime = lifetimeDist(randomEngine);
        particle.size = sizeDist(randomEngine);
        
        std::uniform_int_distribution<int> colorDist(150, 255);
        particle.color = sf::Color(colorDist(randomEngine), colorDist(randomEngine) / 2, 0);
        
        particles.push_back(particle);
    }
}

void ParticleSystem::createTrail(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    std::uniform_real_distribution<float> offsetDist(-5.0f, 5.0f);
    std::uniform_real_distribution<float> speedDist(10.0f, 50.0f);
    std::uniform_real_distribution<float> lifetimeDist(0.2f, 0.5f);
    
    for (int i = 0; i < 3; ++i)
    {
        Particle particle;
        particle.position = position + sf::Vector2f(offsetDist(randomEngine), offsetDist(randomEngine));
        
        float angle = std::atan2(direction.y, direction.x) + 3.14159f;
        angle += offsetDist(randomEngine) * 0.1f;
        float speed = speedDist(randomEngine);
        particle.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        
        particle.lifetime = 0.0f;
        particle.maxLifetime = lifetimeDist(randomEngine);
        particle.size = 2.0f;
        particle.color = sf::Color(100, 100, 255, 150);
        
        particles.push_back(particle);
    }
}

void ParticleSystem::update(float dt)
{
    for (auto it = particles.begin(); it != particles.end(); )
    {
        it->position += it->velocity * dt;
        it->lifetime += dt;
        
        float alpha = 255.0f * (1.0f - (it->lifetime / it->maxLifetime));
        it->color.a = static_cast<sf::Uint8>(alpha);
        
        if (it->lifetime >= it->maxLifetime)
        {
            it = particles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void ParticleSystem::render(sf::RenderTarget& target)
{
    vertices.clear();
    
    for (const auto& particle : particles)
    {
        sf::Vertex vertex;
        vertex.position = particle.position;
        vertex.color = particle.color;
        vertices.append(vertex);
    }
    
    target.draw(vertices);
}

bool ParticleSystem::isEmitting() const
{
    return emitting;
}

void ParticleSystem::stopEmitting()
{
    emitting = false;
}