#include "player.hpp"

void Player::addDrawable(Drawable* newDrawable){
    activeDrawable = newDrawable;
    drawers.push_back(newDrawable);
}

void Player::applyDrawables(cv::Mat& frame){
    for (std::deque<Drawable*>::iterator drawIter = drawers.begin();
            drawIter != drawers.end();
            drawIter ++) {
        (*drawIter)->draw(frame);
    }
}

std::deque<Drawable *> Player::getDrawables(){
    return drawers;
}

void Player::saveFrame(std::string fname){
    cv::Mat ftmp;
    getFrame(ftmp);
    cv::imwrite( fname, ftmp );
}
