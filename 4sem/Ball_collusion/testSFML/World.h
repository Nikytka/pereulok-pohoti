#pragma once
#include "Ball.h"
#include <SFML/Window/Window.hpp>

class World {
public:
    //World();
    //~World();
    void World::collusions_balls(Ball* ball1, Ball* ball2, float dt);
    void World::check_out_window(Ball* ball, sf::RenderWindow* window);
    void update(sf::RenderWindow* window, float dt);
    void collusions_wall(sf::RenderWindow* window);
    void create_ball(sf::Vector2i pos);

private:
    std::vector<Ball> balls;
};
