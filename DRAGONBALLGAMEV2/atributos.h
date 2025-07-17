#ifndef ATRIBUTOS_H
#define ATRIBUTOS_H

#include <QGraphicsItem>
#include <QPainter>

class Atributos : public QGraphicsItem
{
public:
    Atributos(int maxVida, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setVida(int nuevaVida);
    int getVida() const;

private:
    int vidaMaxima;
    int vidaActual;
    QGraphicsItem *parentItem;
};

#endif // ATRIBUTOS_H
