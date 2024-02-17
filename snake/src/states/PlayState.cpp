#include "PlayState.hpp"

PlayState::PlayState(StateEnum curr_state, Platform* platform) : State(curr_state, platform) {

    // Right now I'm passing all handler functions via constructor args. This is obviously not very good.
    // TODO: Might be good to replace with Observer pattern.
    gameclass = std::make_unique<GameClass>(platform, 
                                            std::bind(&PlayState::set_next_state, this, StateEnum::MENU),
                                            std::bind(&PlayState::set_next_state, this, StateEnum::GAME_OVER));
} 

void PlayState::tick() {
    gameclass->tick();
}

void PlayState::draw() {
    gameclass->draw();
}

void PlayState::set_next_state(StateEnum next_state) {
    this->next_state = next_state;

}