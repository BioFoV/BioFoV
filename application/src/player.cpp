#include "player.hpp"

/**
 * @brief Player::addDrawable
 * @param newDrawable
 */
void Player::addDrawable(Drawable* newDrawable){
    activeDrawable = newDrawable;
    drawers.push_back(newDrawable);
}

/**
 * @brief Player::applyDrawables
 * @param frame
 */
void Player::applyDrawables(cv::Mat& frame){
    for (std::deque<Drawable*>::iterator drawIter = drawers.begin();
            drawIter != drawers.end();
            drawIter ++) {
        (*drawIter)->draw(frame);
    }
}

/**
 * @brief Player::getDrawables
 * @return
 */
std::deque<Drawable *> Player::getDrawables(){
    return drawers;
}

/**
 * @brief Player::saveFrame
 * @param fname
 */
void Player::saveFrame(std::string fname){
    cv::Mat ftmp;
    getFrame(ftmp);
    cv::imwrite( fname, ftmp );
}
