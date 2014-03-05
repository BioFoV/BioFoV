#ifndef QITEMDRAWABLE_HPP
#define QITEMDRAWABLE_HPP

#include <QTreeWidgetItem>

#include "Drawables/drawable.hpp"

class QitemDrawable : public QTreeWidgetItem
{
public:
    QitemDrawable(Drawable * inDraw);
    Drawable* getDrawable();

private:
    Drawable* draw;
};

#endif // QITEMDRAWABLE_HPP
