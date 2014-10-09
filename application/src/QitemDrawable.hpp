#ifndef QITEMDRAWABLE_HPP
#define QITEMDRAWABLE_HPP

#include <QTreeWidgetItem>

#ifndef INC_DRAWABLE
#define INC_DRAWABLE
#include <Drawables/drawable.hpp>
#endif

class QitemDrawable : public QTreeWidgetItem
{
public:
    QitemDrawable(Drawable * inDraw);
    Drawable* getDrawable();

private:
    Drawable* draw;
};

#endif // QITEMDRAWABLE_HPP
