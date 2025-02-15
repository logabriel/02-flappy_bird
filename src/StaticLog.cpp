/*
    Assignment: Flappy Bird

    This file contains the definition of the class StaticLog.
*/

#include <Settings.hpp>
#include <src/StaticLog.hpp>

StaticLog::StaticLog(float _x, float _y, bool _inverted) noexcept: Log{_x, _y, _inverted}
{
    
}

void StaticLog::update(float _x, float _y) noexcept
{
    x = _x;

    if (inverted)
    {
        x += Settings::LOG_WIDTH;
    }

    sprite.setPosition(x, y);
}

float StaticLog::speed_y() const noexcept
{
    return 0;
}

void StaticLog::change_direction() noexcept
{
    
}

bool StaticLog::is_at_initial_y() const noexcept
{
    return true;
}