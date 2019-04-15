#include "partical_system.h" 
#include <SFML/Graphics.hpp>
#include "util.h"

extern const sf::Vector2u WINDOW_SIZES;

Particle::Particle(const sf::Vector2f position, const sf::Vector2f velocity,
    const sf::Vector2f acceleration, const float radius
)
    : position_(position)
    , velocity_(velocity)
    , acceleration_(acceleration)
    , radius_(radius)
{
    shape_.setRadius(radius);
    shape_.setFillColor(sf::Color::Yellow);
    shape_.setOrigin(sf::Vector2f(radius, radius));
    shape_.setPosition(position);
}

void Particle::Push(const sf::Vector2f delta_velocity)
{
    velocity_ += delta_velocity;
}

void Particle::Update(const float dt)
{
    position_ += velocity_ * dt;
    velocity_ += acceleration_ * dt;

 
}

void Particle::Render(sf::RenderWindow& window)
{
    shape_.setPosition(position_);
    shape_.setRadius(radius_);

    window.draw(shape_);
}



void ParticleSystem::ApplyGravity()
{
    const sf::Vector2f acceleration_g(0.0f, 980.0f);
    for (Particle& particle : particles_)
    {
        particle.acceleration_ += acceleration_g;
    }
}

void ParticleSystem::Update(const float dt)
{
    for (Particle& particle : particles_)
    {
        particle.acceleration_ = sf::Vector2f(0.0f, 0.0f);
    }

    ApplyGravity();

    for (Particle& particle : particles_)
    {
        particle.Update(dt);
    }

    HandleCollisions();
}

void ParticleSystem::HandleCollisions()
{
    for (Particle& particle : particles_)
    {
        if (particle.position_.x < particle.radius_)
        {
            particle.position_.x = particle.radius_;
            particle.velocity_.x = particle.velocity_.x / 2.0f;
        }
        if (particle.position_.x + particle.radius_ > WINDOW_SIZES.x)
        {
            particle.position_.x = particle.radius_;
            particle.velocity_.x = particle.velocity_.x / 2.0f;
        }

        if (particle.position_.y < particle.radius_)
        {
            particle.position_.y = particle.radius_;
            particle.velocity_.y = particle.velocity_.y / 2.0f;
        }
        const float bottom_gap = 50.0f;
        if (particle.position_.y + particle.radius_ + bottom_gap > WINDOW_SIZES.y)
        {
            particle.position_.y = WINDOW_SIZES.y - particle.radius_ - bottom_gap;
            particle.velocity_.y = particle.velocity_.y / 2.0f;
        }
    }
}

void ParticleSystem::AddLink(
            const ParticleID particle1_id, const ParticleID particle2_id, const float stiffness)
{
    link_.push_back(Link{})
}


void ParticleSystem::SolveLinks()
{
    for (Link& link : links_)
    {
        Particle& particle1 = particles.[link.particle1_id];
        Particle& particle2 = particles.[link.particle2_id];
        const sf::Vector2f distance_vector12 = (
            particle2.position_ - particle1.position_
            );
        const float distance = util::ComputeLength(distance_vector12);
        const float delta = distance - link.initial_length;
        const float force = link.stiffness * delta;
        const sf::Vector2f unit_vector12 = distance_vector12 / distance;
        particle1.acceleration_ += (force * unit_vector12) / particle1.mass_;
        particle2.acceleration_ -= (force * unit_vector12) / particle2.mass_;
    }
}

float ParticleSystem::ComputeDistanceBetween(
    const ParticleID particle1_id, const ParticleID particle2_id)
{
    const Particle& particle1 = GetParticleByID(particle1_id);
    const Particle& particle2 = GetParticleByID(particle2_id);

    const sf::Vector2f distance_vector12 = (
        particle2.position_ - particle1.position_
        );
    return util::ComputeLength(distance_vector12);

}
ParticleSystem::ParticleID ParticleSystem::AddParticle(
    sf::Vector2f
)