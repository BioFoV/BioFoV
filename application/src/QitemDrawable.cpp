#include "QitemDrawable.hpp"

QitemDrawable::QitemDrawable(Drawable * inDraw)
{
    draw = inDraw;
}

Drawable* QitemDrawable::getDrawable(){
    return draw;
}
