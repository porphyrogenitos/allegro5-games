#include "ButtonGroup.hpp"

ButtonGroup::ButtonGroup(Platform* platform, int x, int y, int width, int height) {
    this->platform = platform;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

ButtonGroup::~ButtonGroup() {
    al_destroy_font(font);
}

void ButtonGroup::set_background_transparent(bool set) {
    is_transparent = set;
}

void ButtonGroup::add_button(std::string text, std::function<void()> handler) {
    menu_buttons.push_back(Button {text, font, handler});

    if (menu_buttons.size() == 1) {
        menu_buttons[0].hovering = true;
    }

    resize_menu_buttons();
}

//TODO: Get even spacing between buttons.
void ButtonGroup::resize_menu_buttons() {
    if (menu_buttons.size() == 0)
        return;
    
    int num_items = menu_buttons.size();
    int lr_padding = 20; //left and right padding
    int vert_padding = 20; //vertical padding from menu border
    int item_height = height / 5; //TODO: Might not want to hardcode this
    int item_width = width - 2 * lr_padding;

    menu_buttons[0].x = x + lr_padding;
    menu_buttons[0].width = item_width;
    menu_buttons[0].y = y + vert_padding;
    menu_buttons[0].height = item_height;

    menu_buttons[num_items - 1].x = x + lr_padding;
    menu_buttons[num_items - 1].width = item_width;
    menu_buttons[num_items - 1].y = y + height - vert_padding - item_height;
    menu_buttons[num_items - 1].height = item_height;

    for (int i = 1; i < num_items - 1; i++) {
        menu_buttons[i].x = x + lr_padding;
        menu_buttons[i].width = item_width;
        menu_buttons[i].y = y + (height / num_items ) * i + vert_padding;
        menu_buttons[i].height = item_height;
    }
}

void ButtonGroup::draw() {
    if (!is_transparent)
        al_draw_filled_rectangle(x, y, width, height, background);

    for (Button button : menu_buttons)
        button.draw();
}

void ButtonGroup::tick() {
    // TODO: Make it scroll down the buttons more slowly -- right now 
    // it's too easy to go past the button you want.
    if (platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_ENTER))
        menu_buttons[hovered_item].select();
    if (platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_DOWN)) {
        menu_buttons[hovered_item].hovering = false;
        hovered_item = (hovered_item + 1) % menu_buttons.size();
        menu_buttons[hovered_item].hovering = true;
    }
    if (platform->keyboard_man.key_was_pressed(ALLEGRO_KEY_UP)) {
        menu_buttons[hovered_item].hovering = false;
        hovered_item = (hovered_item - 1) % menu_buttons.size();
        menu_buttons[hovered_item].hovering = true;
    }
}