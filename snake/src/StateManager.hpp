#include <memory>
#include "Platform.hpp"
#include "states/State.hpp"

class StateFactory;

//TODO: Did you add to Makefile?

class StateManager {
private:
    std::shared_ptr<State> curr_state;
    Platform* platform;
    std::shared_ptr<StateFactory> state_factory;

public:
    StateManager(StateEnum initial_state, Platform* platform, std::shared_ptr<StateFactory> state_factory);

    void set_state(StateEnum next_state);

    std::shared_ptr<State> get_curr_state();
};