#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsItem>

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    using QGraphicsView::QGraphicsView;

    void setTargetItemForFocus(QGraphicsItem* item);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;

private:
    QGraphicsItem* targetItem = nullptr;
};

#endif // CUSTOMGRAPHICSVIEW_H
