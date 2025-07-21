#ifndef GOKU_H
#define GOKU_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QSet>

class Nivel1;

class goku : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit goku(QObject *parent = nullptr);
    ~goku();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    void recibirDanio(int cantidad);
    void setVida(int v);
    int getVida() const;
    void setNivel(Nivel1* nivel);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;

private slots:
    void aplicarGravedad();
    void moverEnAire();
    void habilitarSlotDisparo(int slot);

private:
    void recortarSprite(int x, int y, int w, int h);
    int obtenerSlotLibre();

    QPixmap original;
    QPixmap pixmap;
    int escalaVisual;
    float velY;
    bool enElAire;
    bool mirandoIzquierda;

    QSet<int> teclasPresionadas;
    QTimer *gravedadTimer;
    QTimer *movimientoTimer;

    static const int MAX_KI = 5;
    bool slotsDisparo[MAX_KI];

    int vida;
    Nivel1* nivel;

    bool puedeRecibirDanio;
};

#endif // GOKU_H
