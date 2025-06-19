#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsPathItem>
#include <QRectF>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>


#include "sprites.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    sprite *Donald;

    float x,y,ancho,alto;
};
#endif // WIDGET_H
