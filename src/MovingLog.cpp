/*
    Assignment: Flappy Bird

    This file contains the definition of the class MovingLog.
*/

#include <Settings.hpp>
#include <src/MovingLog.hpp>

MovingLog::MovingLog(float _x, float _y, bool _inverted) noexcept: Log(_x, _y, _inverted), Yspeed{Settings::MAIN_SCROLL_SPEED/4},
initialY{_y}
{
    if(inverted)
    {
        Yspeed *= -1;
    }
}

void MovingLog::update(float _x, float _y) noexcept
{
    x = _x;
    if (inverted)
    {
        x += Settings::LOG_WIDTH;
    }
    y += _y;

    sprite.setPosition(x, y);
}

float MovingLog::speed_y() const noexcept
{
    return Yspeed;
}

void MovingLog::change_direction() noexcept
{
    Yspeed *= -1;
}

bool MovingLog::is_at_initial_y() const noexcept
{
    return y == initialY;
}