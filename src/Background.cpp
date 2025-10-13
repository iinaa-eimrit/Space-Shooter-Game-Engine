#include "Background.h"

Background::Background()
{
    initBackground();
    initStars(200);
}

void Background::initBackground()
{
    gradientBackground.setSize(sf::Vector2f(800.f, 600.f));
    gradientBackground.setFillColor(sf::Color(10, 10, 30));
}

void Background::initStars(int count)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posXDist(0.f, 800.f);
    std::uniform_real_distribution<float> posYDist(0.f, 600.f);
    std::uniform_real_distribution<float> speedDist(20.f, 100.f);
    std::uniform_real_distribution<float> sizeDist(1.f, 3.f);
    
    for (int i = 0; i < count; ++i)
    {
        Star star;
        star.position = sf::Vector2f(posXDist(gen), posYDist(gen));
        star.speed = speedDist(gen);
        star.size = sizeDist(gen);
        
        int brightness = static_cast<int>(star.speed / 100.f * 255);
        star.color = sf::Color(brightness, brightness, 255);
        
        stars.push_back(star);
    }
}

void Background::update(float dt)
{
    for (auto& star : stars)
    {
        star.position.y += star.speed * dt;
        if (star.position.y > 600.f)
        {
            star.position.y = -10.f;
            star.position.x = static_cast<float>(rand() % 800);
        }
    }
}

void Background::render(sf::RenderTarget& target)
{
    target.draw(gradientBackground);
    
    sf::VertexArray starVertices(sf::Points);
    for (const auto& star : stars)
    {
        sf::Vertex vertex;
        vertex.position = star.position;
        vertex.color = star.color;
        starVertices.append(vertex);
    }
    target.draw(starVertices);
}