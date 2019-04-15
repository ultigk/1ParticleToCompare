#include "game.h"
#include <SFML/Graphics.hpp>

extern const sf::Vector2u WINDOW_SIZES(800, 600);

Game::Game()
    : main_window_("Ball", WINDOW_SIZES)
    , particle_
    (const auto particle1_id = particle_system_.AddParticle()
        sf::Vector2f(WINDOW_SIZES.x / 2.0f, WINDOW_SIZES.y / 2.0f),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 10.0f),
        25.0f,
        100.0f)
{
    
    
}



void Game::Run()
{
    const float updates_per_seconds = 60.0f;
    const sf::Time time_per_update = sf::seconds(
        1.0f / updates_per_seconds
    );
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while (!main_window_.CheckIsDone())
    {
        time_since_last_update += clock.restart();
        while (time_since_last_update >= time_per_update)
        {
            HandleInput();
            Update(time_per_update.asSeconds());
            time_since_last_update -= time_per_update;
        }
        
        //Update();
        Render();
    }
}

void Game::HandleInput()
{
    sf::Vector2f increment(0, 0);
    const float delta = 1.5f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        increment.y -= delta;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        increment.x += delta;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        increment.y += delta;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        increment.x -= delta;

    }

    particle_.Push(increment);

}

void Game::Update(const float dt)
{
    main_window_.Update(dt);
    particle_.Update(dt);
}



void Game::Render()
{
    main_window_.BeginDraw();

    main_window_.Draw(particle_);
    // draw other objects here

    main_window_.EndDraw();
}


particle_system_.AddLink(particle1_id, particle2_id, 1000.0f)


void ParticleSystem::Render(sf::RenderWindow& window)
{
    for (Link& link : links_)
    {
       const Particle& particle1 = GetParticleByID(link.particle1_id);
       const Particle& particle2 = GetParticleByID(link.particle2_id);
        sf::Vertex line[] =
        {
            sf::Vertex(particle1.position_),
            sf::Vertex(particle2.position_)
        };

        window.draw(line, 2, sf::Lines);
    }
    for(Particle& particle)
}