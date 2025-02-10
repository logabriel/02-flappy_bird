#pragma once

#include <src/Bird.hpp>
#include <src/World.hpp>
#include <src/strategy/BaseStrategy.hpp>

class HardMode: public BaseStrategy
{

public:
    HardMode(StateMachine* sm, std::shared_ptr<World> _world = nullptr, std::shared_ptr<Bird> _bird = nullptr) noexcept;

    void handle_inputs(const sf::Event& event) noexcept override;

    void update(float dt) noexcept override;

    void render(sf::RenderTarget& target) const noexcept override;

private:
    std::shared_ptr<Bird> bird;
    std::shared_ptr<World> world;
};
