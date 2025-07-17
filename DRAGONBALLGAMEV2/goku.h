#ifndef GOKU_H
#define GOKU_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QSet>
#include "atributos.h"

class goku : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit goku(QObject *parent = nullptr);
    ~goku();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void recibirDano(int cantidad);
    int getVida() const;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void aplicarGravedad();
    void moverEnAire();
    void lanzarAtaque();

private:
    void recortarSprite(int x, int y, int w, int h);
    void actualizarBarraVida();

    // 🔄 ORDEN CORRECTO según constructor:
    QPixmap original;
    int vida;
    int escalaVisual;
    float velY;
    bool enElAire;
    bool mirandoIzquierda;
    QTimer* gravedadTimer;
    QTimer* movimientoTimer;
    Atributos* barraVida;
    QPixmap pixmap;
    int anchoRecorte;
    int altoRecorte;
    QSet<int> teclasPresionadas;

    static int contadorAtaques;
    static bool enEnfriamiento;
};

#endif // GOKU_H
