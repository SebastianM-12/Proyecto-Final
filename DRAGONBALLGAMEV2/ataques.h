#ifndef ATAQUES_H
#define ATAQUES_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include "goku.h"
#include "enemigo.h"

class Ataque : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem) // <- Esta línea soluciona el warning

public:
    explicit Ataque(bool direccionDerecha, goku* jugador);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private slots:
    void mover();

private:
    QPixmap pixmap;
    QTimer *timer;
    int velocidadX;
    float velocidadY;
    float gravedad;
    bool eliminado;
    goku* jugador;
};

#endif // ATAQUES_H

