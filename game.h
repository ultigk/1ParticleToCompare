#pragma once

#include "window.h"


class Game
{
public:
    Game();
    virtual ~Game() = default;
    
    void Run();
    void Update();
    void Render();


private:
    Window main_window_;

    sf::CircleShape ball_;
    sf::Texture ball_texture_;
    void MoveBall();

    sf::Vector2f increment_;
};

