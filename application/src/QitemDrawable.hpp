#ifndef QITEMDRAWABLE_HPP
#define QITEMDRAWABLE_HPP

#include <QTreeWidgetItem>

#ifndef INC_DRAWABLE
#define INC_DRAWABLE
#include <Drawables/drawable.hpp>
#endif

/**
 * @brief The QitemDrawable class
 */
class QitemDrawable : public QTreeWidgetItem
{
public:
    QitemDrawable(Drawable * inDraw);
    Drawable* getDrawable();

private:
    /**
     * @brief draw
     */
    Drawable* draw;
};

#endif // QITEMDRAWABLE_HPP
