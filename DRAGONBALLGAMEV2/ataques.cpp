#include "ataques.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>

Ataque::Ataque(bool direccionDerecha, goku* jugador)
    : velocidadY(-8), gravedad(0.5), eliminado(false), jugador(jugador)
{
    pixmap = QPixmap(":/sprite/ki.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    velocidadX = direccionDerecha ? 10 : -10;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ataque::mover);
    timer->start(30);
    setZValue(1);
}

QRectF Ataque::boundingRect() const {
    return QRectF(-15, -15, 30, 30);
}

void Ataque::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(-15, -15, pixmap);
}

void Ataque::mover() {
    moveBy(velocidadX, velocidadY);
    velocidadY += gravedad;

    QList<QGraphicsItem*> itemsColisionados = collidingItems();
    for (QGraphicsItem* item : itemsColisionados) {
        Enemigo* enemigo = dynamic_cast<Enemigo*>(item);
        if (enemigo && !eliminado) {
            enemigo->recibirDano(1);
            eliminado = true;

            if (scene()) {
                scene()->removeItem(this);
            }
            deleteLater();
            return;
        }
    }

    if (!eliminado && (x() < 0 || x() > 1600 || y() > 900)) {
        eliminado = true;
        if (scene()) {
            scene()->removeItem(this);
        }
        deleteLater();
    }
}
