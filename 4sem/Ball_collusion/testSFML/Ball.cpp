#include "Ball.h"

Ball::Ball(float mass1, float radius1, size_t size)
{
    //mass = mass1;
    circleshape = sf::CircleShape(30);
    mass = pow(circleshape.getRadius(), 3) * 4 / 3 * 3.141592f * 2000;
    circleshape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    set_accelerate(0, 37077.16f);
    set_velocity((100 + rand() % 400) * ((rand() % 2) ? 1 : -1), (100 + rand() % 400) * ((rand() % 2) ? 1 : -1));
    circleshape.setOrigin(get_rad(), get_rad());
    set_index(size);
}

float Ball::get_mass()
{
    return mass;
}

sf::Vector2f Ball::get_velocity()
{
    return velocity;
}

void Ball::set_pos(float x, float y)
{
    circleshape.setPosition(sf::Vector2f(x, y));
}

void Ball::set_accelerate(float x, float y)
{
    accelerate = sf::Vector2f(x, y);
}

float Ball::get_rad()
{
    return circleshape.getRadius();
}

void Ball::draw(sf::RenderWindow* window)
{
    window->draw(circleshape);
}

int Ball::get_index()
{
    return index;
}

sf::CircleShape Ball::get_circleshape()
{
    return circleshape;
}

void Ball::set_circleshape(sf::CircleShape csh)
{
    circleshape = csh;
}

void Ball::set_velocity(float vx, float vy)
{
    velocity.x = vx;
    velocity.y = vy;
}

sf::Vector2f Ball::get_accelerate()
{
    return accelerate;
}

void Ball::update(float dt)
{
    circleshape.setPosition(circleshape.getPosition().x + dt * get_velocity().x, circleshape.getPosition().y + dt * get_velocity().y);
}

void Ball::set_index(size_t size)
{
    index = size + 1;
}
