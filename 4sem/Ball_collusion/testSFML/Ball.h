#pragma once
#include <SFML\Graphics.hpp>

class Ball {
public:
    Ball(float mass1, float radius1, size_t size);

    void update(float dt);
    float get_mass();
    sf::Vector2f get_velocity();
    void set_velocity(float vx, float vy);
    sf::Vector2f get_accelerate();
    sf::CircleShape get_circleshape();
    void set_circleshape(sf::CircleShape csh);
    float get_rad();
    void set_pos(float x, float y);
    void set_accelerate(float x, float y);
    void draw(sf::RenderWindow* window);
    int get_index();
    void set_index(size_t size);

private:
    float mass;
    float radius;
    int index;
    sf::Vector2f velocity;
    sf::Vector2f accelerate;
    sf::CircleShape circleshape;
};
