#pragma once

#include <src/Log.hpp>

class StaticLog: public Log
{
public:

    StaticLog(float _x, float _y, bool _inverted) noexcept;

    void update(float _x, float _y) noexcept override;

    float speed_y() const noexcept override;

    void change_direction() noexcept override;

    bool is_at_initial_y() const noexcept override;
};
