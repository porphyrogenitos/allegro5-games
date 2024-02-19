#pragma once

#include "KeyboardManager.hpp"

struct Platform {
    KeyboardManager keyboard_man {};

    // Determines whether the application should shut down.
    // TODO: (This is a temporary solution but it's what I got for now.)
    bool exit {false}; 
};