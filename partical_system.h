#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Particle
{
    friend class ParticleSystem;

public:
    Particle(const sf::Vector2f position, const sf::Vector2f velocity,
        const sf::Vector2f acceleration, const float radius);
    virtual ~Particle() = default;

    void Push(const sf::Vector2f increment);

    void Update(const float dt);
    void Render(sf::RenderWindow& window);


private:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
    float radius_;

    sf::CircleShape shape_;
};

class ParticleSystem
{
public:
    ParticleSystem() = default;
    virtual ~ParticleSystem() = default;

    using ParticleID = size_t;

    ParticleID AddParticle(const sf::Vector2f position, const sf::Vector2f velocity,
        const sf::Vector2f acceleration, const float radius);
   // void RemoveParticle(const ParticleID particle_id);

    void ComputeDistanceBetween( const ParticleID particle1_id, const ParticleID particle2_id)
    void Update(const float dt);
    void Render(sf::RenderWindow& window);

private:
    void HandleCollisions();
    void ApplyGravity();

    void SolveLinks()
    std::vector<Particle> particles_;

    struct Link
    {

    };
};