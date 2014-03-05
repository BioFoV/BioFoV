#include "player.hpp"

void Player::addDrawable(Drawable* newDrawable){
    activeDrawable = newDrawable;
    drawers.push_back(newDrawable);
}
