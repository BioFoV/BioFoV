#include "QitemDrawable.hpp"

/**
 * @brief QitemDrawable::QitemDrawable
 * @param inDraw
 */
QitemDrawable::QitemDrawable(Drawable * inDraw)
{
    draw = inDraw;
}

/**
 * @brief QitemDrawable::getDrawable
 * @return
 */
Drawable* QitemDrawable::getDrawable(){
    return draw;
}
