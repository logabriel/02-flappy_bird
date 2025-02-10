/*
    ISPPV1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class Bird.
*/

#pragma once

#include <SFML/Graphics.hpp>

class Bird
{
public:
    Bird(float _x, float _y, float w, float h) noexcept;

    Bird(const Bird&) = delete;

    Bird& operator = (Bird) = delete;

    sf::FloatRect get_collision_rect() const noexcept;

    void jump() noexcept;

    void update(float dt) noexcept;

    void render(sf::RenderTarget& target) const noexcept;
    //codigo nuevo *********************************************************
    void add_point() noexcept;

    int get_score() const noexcept;

    void move_right() noexcept;

    void move_left() noexcept;

    void stop_move() noexcept;

    void moving(float dt) noexcept;
    //codigo nuevo *********************************************************
private:
    float x;
    float y;
    float width;
    float height;
    float vy;
    float vx; //codigo nuevo *********************
    sf::Sprite sprite;
    bool jumping{false};
    int score{0}; //codigo nuevo *****************
};
