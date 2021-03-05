#include "World.h"
#include <SFML/Window/Window.hpp>
#include <iostream>
//Коэфф-ты: 1) - боунсфактор, 2) - трение о стенки
#define KOEF 0.92
#define KOEF_FR 0.999

bool col = false;

void World::collusions_wall(sf::RenderWindow* window)
{
    for (auto& elem : balls) {
        if ((elem.get_circleshape().getPosition().x <= elem.get_circleshape().getRadius()) && (elem.get_velocity().x < 0))

            elem.set_velocity(-elem.get_velocity().x * KOEF, elem.get_velocity().y * KOEF_FR);

        if ((elem.get_circleshape().getPosition().x >= window->getSize().x - elem.get_circleshape().getRadius()) && (elem.get_velocity().x > 0))

            elem.set_velocity(-elem.get_velocity().x * KOEF, elem.get_velocity().y * KOEF_FR);

        if ((elem.get_circleshape().getPosition().y <= elem.get_circleshape().getRadius()) && (elem.get_velocity().y < 0))

            elem.set_velocity(elem.get_velocity().x * KOEF_FR, -elem.get_velocity().y * KOEF);

        if ((elem.get_circleshape().getPosition().y >= window->getSize().y - elem.get_circleshape().getRadius()) && (elem.get_velocity().y > 0))

            elem.set_velocity(elem.get_velocity().x * KOEF_FR, -elem.get_velocity().y * KOEF);
    }
}

void World::check_out_window(Ball* ball, sf::RenderWindow* window)
{

    if (ball->get_circleshape().getPosition().x < ball->get_rad())

        ball->set_pos(ball->get_rad(), ball->get_circleshape().getPosition().y);

    if (ball->get_circleshape().getPosition().x > window->getSize().x - ball->get_rad())

        ball->set_pos(window->getSize().x - ball->get_rad(), ball->get_circleshape().getPosition().y);

    if (ball->get_circleshape().getPosition().y < ball->get_rad())

        ball->set_pos(ball->get_circleshape().getPosition().x, ball->get_rad());

    if (ball->get_circleshape().getPosition().y > window->getSize().y - ball->get_rad())

        ball->set_pos(ball->get_circleshape().getPosition().x, window->getSize().y - ball->get_rad());
}

void World::collusions_balls(Ball* ball1, Ball* ball2, float dt)
{
    sf::Vector2f dp, n, d, dv;
    float abs_d = sqrt(pow(ball2->get_circleshape().getPosition().x - ball1->get_circleshape().getPosition().x, 2) + pow(ball2->get_circleshape().getPosition().y - ball1->get_circleshape().getPosition().y, 2));
    float scal_d;

    d.x = ball2->get_circleshape().getPosition().x - ball1->get_circleshape().getPosition().x;
    d.y = ball2->get_circleshape().getPosition().y - ball1->get_circleshape().getPosition().y;
    dv.x = ball2->get_velocity().x - ball1->get_velocity().x;
    dv.y = ball2->get_velocity().y - ball1->get_velocity().y;

    if (abs_d <= (ball1->get_rad() + ball2->get_rad())) {
        /*std::cout << ball1->get_velocity().x << " " << ball1->get_velocity().y << std::endl
                  << ball2->get_velocity().x << " " << ball2->get_velocity().y << std::endl
                  << std::endl;*/
        col = true;
        if ((dv.x * d.x + dv.y * d.y) <= 0) {

            n.x = d.x / abs_d;
            n.y = d.y / abs_d;
            scal_d = (1 + KOEF) * (n.x * dv.x / (1.0f / ball1->get_mass() + 1.0f / ball2->get_mass()) + n.y * dv.y / (1.0f / ball1->get_mass() + 1.0f / ball2->get_mass()));
            dp.x = scal_d * n.x;
            dp.y = scal_d * n.y;
            ball1->set_velocity(ball1->get_velocity().x + (float)dp.x / ball1->get_mass(), ball1->get_velocity().y + (float)dp.y / ball1->get_mass());
            ball2->set_velocity(ball2->get_velocity().x - (float)dp.x / ball2->get_mass(), ball2->get_velocity().y - (float)dp.y / ball2->get_mass());
            /*if (abs_d < (ball1->get_rad() + ball2->get_rad())) {
                ball1->set_velocity(ball1->get_velocity().x - ball1->get_accelerate().x * dt * n.x, ball1->get_velocity().y - ball1->get_accelerate().y * dt * n.y);
                ball2->set_velocity(ball2->get_velocity().x + ball2->get_accelerate().x * dt * n.x, ball2->get_velocity().y + ball2->get_accelerate().y * dt * n.y);
            }*/
            /*std::cout << ball1->get_velocity().x << " " << ball1->get_velocity().y << std::endl
                      << ball2->get_velocity().x << " " << ball2->get_velocity().y << std::endl
                      << std::endl;*/
        }
    }
}

void World::update(sf::RenderWindow* window, float dt)
{
    collusions_wall(window);
    for (auto& elem : balls) {
        for (auto& elem1 : balls) {
            if (elem.get_index() != elem1.get_index())
                collusions_balls(&elem, &elem1, dt);
        }
        if ((elem.get_accelerate().y > 0) && (sqrt(elem.get_velocity().x * elem.get_velocity().x + elem.get_velocity().y * elem.get_velocity().y) <= 10) && (elem.get_circleshape().getPosition().y >= window->getSize().y - elem.get_rad())) {
            if (elem.get_accelerate().x == 0)
                elem.set_velocity(elem.get_velocity().x, 0);
            else if ((elem.get_circleshape().getPosition().x <= elem.get_rad()) && (elem.get_accelerate().x < 0))
                elem.set_velocity(0, 0);
            else if (elem.get_circleshape().getPosition().x >= window->getSize().x - elem.get_rad())
                elem.set_velocity(0, 0);

        } else if ((elem.get_accelerate().y < 0) && (sqrt(elem.get_velocity().x * elem.get_velocity().x + elem.get_velocity().y * elem.get_velocity().y) <= 10) && (elem.get_circleshape().getPosition().y <= elem.get_rad())) {
            if (elem.get_accelerate().x == 0)
                elem.set_velocity(elem.get_velocity().x, 0);
            else if ((elem.get_circleshape().getPosition().x <= elem.get_rad()) && (elem.get_accelerate().x < 0))
                elem.set_velocity(0, 0);
            else if (elem.get_circleshape().getPosition().x >= window->getSize().x - elem.get_rad())
                elem.set_velocity(0, 0);

        } else if (col == false)
            elem.set_velocity(elem.get_velocity().x + elem.get_accelerate().x * dt, elem.get_velocity().y + elem.get_accelerate().y * dt);
        elem.update(dt);
        check_out_window(&elem, window);
        window->draw(elem.get_circleshape());
        col = false;
    }
}

void World::create_ball(sf::Vector2i pos)
{
    Ball new_ball(1, 50, balls.size());
    new_ball.set_pos(pos.x, pos.y);
    balls.push_back(new_ball);
}
