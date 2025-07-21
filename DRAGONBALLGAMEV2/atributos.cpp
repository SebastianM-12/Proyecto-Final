#include "atributos.h"
#include <QBrush>
#include <QGraphicsScene>

Atributo::Atributo(int maximo, int inicioX, int inicioY, QColor color, QGraphicsScene* escena)
    : vidaActual(maximo), vidaMaxima(maximo), escena(escena), color(color),
    inicioX(inicioX), inicioY(inicioY)
{
    for (int i = 0; i < vidaMaxima; ++i) {
        QGraphicsRectItem* bloque = new QGraphicsRectItem(inicioX + i * 12, inicioY, 10, 20);
        bloque->setBrush(QBrush(color));
        bloque->setZValue(3);
        escena->addItem(bloque);
        barra.push_back(bloque);
    }
}

void Atributo::reducir(int cantidad)
{
    while (cantidad-- > 0 && vidaActual > 0) {
        vidaActual--;
        if (!barra.empty()) {
            QGraphicsRectItem* ultimo = barra.back();
            escena->removeItem(ultimo);
            delete ultimo;
            barra.pop_back();
        }
    }
}

void Atributo::reiniciar()
{
    liberar();  // Primero limpia
    vidaActual = vidaMaxima;

    for (int i = 0; i < vidaMaxima; ++i) {
        QGraphicsRectItem* bloque = new QGraphicsRectItem(inicioX + i * 12, inicioY, 10, 20);
        bloque->setBrush(QBrush(color));
        bloque->setZValue(3);
        escena->addItem(bloque);
        barra.push_back(bloque);
    }
}

void Atributo::liberar()
{
    for (QGraphicsRectItem* item : barra) {
        escena->removeItem(item);
        delete item;
    }
    barra.clear();
}

int Atributo::getVidaActual() const {
    return vidaActual;
}

int Atributo::getVidaMaxima() const {
    return vidaMaxima;
}

