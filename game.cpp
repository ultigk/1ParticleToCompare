#include "game.h"



Game::Game()
    : main_window_("Ball", sf::Vector2u(800, 600))
{
    const float ball_radius = 150.0f;
    ball_.setRadius(ball_radius);
    ball_.setFillColor(sf::Color::Yellow);
    ball_.setOrigin(sf::Vector2f(ball_radius, ball_radius));
    ball_.setPosition(sf::Vector2f(2 * ball_radius, 2 * ball_radius));

    ball_texture_.loadFromFile("../data/basketball.png");
    ball_texture_.setSmooth(true);
    ball_.setTexture(&ball_texture_);

    increment_ = sf::Vector2f(0.5f, 0.5f);
}



void Game::Run()
{
    while (!main_window_.CheckIsDone())
    {
        Update();
        Render();
    }
}



void Game::Update()
{
    main_window_.Update();

    MoveBall();
}



void Game::Render()
{
    main_window_.BeginDraw();

    main_window_.Draw(ball_);
    // draw other objects here

    main_window_.EndDraw();
}



void Game::MoveBall()
{
    if (ball_.getPosition().x < ball_.getRadius() ||
        ball_.getPosition().x + ball_.getRadius() > main_window_.GetWindowSize().x)
    {
        increment_.x = -increment_.x;
    }

    if (ball_.getPosition().y < ball_.getRadius() ||
        ball_.getPosition().y + ball_.getRadius() > main_window_.GetWindowSize().y)
    {
        increment_.y = -increment_.y;
    }

    ball_.setPosition(ball_.getPosition() + increment_);
}

