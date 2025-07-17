#include "atributos.h"

Atributos::Atributos(int maxVida, QGraphicsItem *parent)
    : QGraphicsItem(parent), vidaMaxima(maxVida), vidaActual(maxVida), parentItem(parent)
{
    // La barra de vida se posicionará encima del personaje
    setZValue(10); // Asegurar que se dibuje encima de otros elementos
}

QRectF Atributos::boundingRect() const
{
    return QRectF(-30, -50, 60, 10);
}

void Atributos::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Dibujar fondo de la barra (rojo)
    painter->setBrush(Qt::red);
    painter->drawRect(-30, -50, 60, 10);

    // Dibujar vida actual (verde)
    float porcentajeVida = (float)vidaActual / vidaMaxima;
    painter->setBrush(Qt::green);
    painter->drawRect(-30, -50, 60 * porcentajeVida, 10);

    // Dibujar borde
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(-30, -50, 60, 10);
}

void Atributos::setVida(int nuevaVida)
{
    vidaActual = nuevaVida;
    if(vidaActual < 0) vidaActual = 0;
    if(vidaActual > vidaMaxima) vidaActual = vidaMaxima;
    update();
}

int Atributos::getVida() const
{
    return vidaActual;
}

