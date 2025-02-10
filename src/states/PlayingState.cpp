/*
    ISPPV1 2023
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class PlayingBaseState.
*/

#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/PlayingState.hpp>
#include <src/strategy/NormalMode.hpp>
#include <src/strategy/HardMode.hpp>

PlayingState::PlayingState(StateMachine* sm) noexcept
    : BaseState{sm}
{

}

void PlayingState::enter(std::shared_ptr<World> _world, std::shared_ptr<Bird> _bird) noexcept
{
    world = _world;
    world->reset(true);
    
    if (_bird == nullptr)
    {
        bird = std::make_shared<Bird>(
            Settings::VIRTUAL_WIDTH / 2 - Settings::BIRD_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2 - Settings::BIRD_HEIGHT / 2,
            Settings::BIRD_WIDTH, Settings::BIRD_HEIGHT
        );
    }
    else
    {
        bird = _bird;
    }

    if (current_strategy == nullptr && Settings::game_mode) 
    {
        current_strategy = std::make_shared<NormalMode>(state_machine, world, bird);
    } 
    else if (current_strategy == nullptr && !Settings::game_mode) 
    {
        current_strategy = std::make_shared<HardMode>(state_machine, world, bird);
    }
    world->set_game_mode(current_strategy);
}

void PlayingState::handle_inputs(const sf::Event& event) noexcept
{
    current_strategy->handle_inputs(event);
}

void PlayingState::update(float dt) noexcept
{
    current_strategy->update(dt);
}

void PlayingState::render(sf::RenderTarget& target) const noexcept
{
    current_strategy->render(target);
}