#ifndef ATRIBUTOS_H
#define ATRIBUTOS_H

#include <QGraphicsRectItem>
#include <vector>

class Atributo {
public:
    Atributo(int maximo, int inicioX, int inicioY, QColor color, QGraphicsScene* escena);

    void reducir(int cantidad = 1);
    void reiniciar();
    void liberar();
    int getVidaActual() const;
    int getVidaMaxima() const;

private:
    int vidaActual;
    int vidaMaxima;
    std::vector<QGraphicsRectItem*> barra;
    QGraphicsScene* escena;
    QColor color;
    int inicioX;
    int inicioY;
};

#endif // ATRIBUTO_H
