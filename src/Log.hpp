/*
    ISPPV1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class Log.
*/

#pragma once

#include <SFML/Graphics.hpp>

class Log
{
public:
    Log(float _x, float _y, bool inverted) noexcept;

    sf::FloatRect get_collision_rect() const noexcept;

    virtual void update(float _x, float _y) noexcept {}

    void render(sf::RenderTarget& target) const noexcept;

    virtual float speed_y() const noexcept = 0;

    virtual void change_direction() noexcept {}

    virtual bool is_at_initial_y() const noexcept = 0;

protected:
    float x;
    float y;
    bool inverted = false;
    sf::Sprite sprite;
};