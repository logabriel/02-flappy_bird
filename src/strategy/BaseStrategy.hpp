#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class StateMachine;
class World;
class Bird;

class BaseStrategy
{
public:
    BaseStrategy(StateMachine* sm) : state_machine(sm) {}

    virtual ~BaseStrategy() {}

    virtual void handle_inputs(const sf::Event& event) noexcept {}

    virtual void update(float dt) noexcept {}

    virtual void render(sf::RenderTarget& target) const noexcept {}

protected:
    StateMachine* state_machine;
    std::shared_ptr<Bird> bird;
    std::shared_ptr<World> world;
};

