#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include "atributos.h"

class Enemigo : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit Enemigo(QObject *parent = nullptr);
    ~Enemigo();

    void recibirDano(int cantidad);
    int getVida() const;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

signals:
    void enemigoDerrotado();

private slots:
    void moverAutomaticamente();

private:
    void recortarSprite(int x, int y, int w, int h);

    QPixmap original;
    QPixmap pixmap;
    int anchoRecorte;
    int altoRecorte;
    int escalaVisual;
    int vida;
    QTimer *movimientoTimer;
    float velY;
    bool enElAire;
    bool moviendoDerecha;
    bool mirandoDerecha;
    Atributos *barraVida;
};

#endif // ENEMIGO_H
