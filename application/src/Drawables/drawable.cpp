#include "drawable.hpp"

/**
 * @brief Constructor
 */
Drawable::Drawable(){
	visible = true;
}

/**
 * @brief Drawable::getValues
 * @return
 */
TStrDoubleMap Drawable::getValues(){
	return values;
}

/**
 * @brief Drawable::isVisible
 * @return
 */
bool Drawable::isVisible(){
	return visible;
}

/**
 * @brief Drawable::setVisible
 * @param value
 */
void Drawable::setVisible(bool value){
	visible = value;
}
