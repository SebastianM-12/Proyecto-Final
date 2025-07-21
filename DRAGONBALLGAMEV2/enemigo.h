#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>

class Nivel1;

enum TipoEnemigo {
    Chaoz,
    Ten
};

class Enemigo : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit Enemigo(TipoEnemigo tipo = Chaoz, QObject* parent = nullptr);
    ~Enemigo();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    void setNivel(Nivel1* n);
    void recortarSprite(int x, int y, int w, int h);
    void setVelocidadX(int v);
    int getVelocidadX() const;
    void recibirDanio(int cantidad);
    bool estaVivo() const;
    int getVida() const;

protected:
    void advance(int step) override;

signals:
    void enemigoDerrotado();

private slots:
    void moverAutomaticamente();

private:
    TipoEnemigo tipoEnemigo;
    int escalaVisual;
    QPixmap original;
    QPixmap pixmap;
    int anchoRecorte;
    int altoRecorte;

    QTimer* movimientoTimer;
    float velY;
    bool enElAire;
    bool moviendoDerecha;
    bool mirandoDerecha;
    int velocidadX;
    int vida;

    Nivel1* nivel;
};

#endif // ENEMIGO_H
