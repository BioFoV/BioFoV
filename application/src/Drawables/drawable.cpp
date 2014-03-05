#include "drawable.hpp"

Drawable::Drawable(){
    visible = true;
}

TStrDoubleMap Drawable::getValues(){
    return values;
}

bool Drawable::isVisible(){
    return visible;
}

void Drawable::setVisible(bool value){
    visible = value;
}
