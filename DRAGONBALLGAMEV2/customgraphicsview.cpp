#include "customgraphicsview.h"
#include <QDebug>

void CustomGraphicsView::setTargetItemForFocus(QGraphicsItem* item)
{
    targetItem = item;
    if (targetItem)
        qDebug() << "Goku asignado como objetivo para recibir foco.";
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if (targetItem && targetItem->flags().testFlag(QGraphicsItem::ItemIsFocusable)) {
        targetItem->setFocus(Qt::MouseFocusReason);
        qDebug() << "Foco asignado a Goku desde CustomGraphicsView por clic.";
    }
}

void CustomGraphicsView::focusInEvent(QFocusEvent *event)
{
    QGraphicsView::focusInEvent(event);

    if (targetItem && targetItem->flags().testFlag(QGraphicsItem::ItemIsFocusable)) {
        targetItem->setFocus(Qt::OtherFocusReason);
        qDebug() << "Foco asignado a Goku desde CustomGraphicsView por evento focusIn.";
    }
}
