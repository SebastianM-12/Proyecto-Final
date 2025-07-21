#ifndef ATAQUES_H
#define ATAQUES_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QMap>

class goku;
class Enemigo;

class Ataque : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit Ataque(bool direccionDerecha, goku* jugador, QObject* parent = nullptr);
    ~Ataque();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    static void lanzarDash(Enemigo* enemigo);
    void destruir();
    void setReboteYRotacion(bool activar);

private slots:
    void mover();

private:
    QPixmap pixmap;
    QTimer* timer;
    int velocidadX;
    float velocidadY;
    float gravedad;
    bool eliminado;
    goku* jugador;

    bool reboteActivado;
    bool yaReboto;
    int rotacionAngulo;

    static QMap<Enemigo*, int> velocidadOriginal;
};

#endif // ATAQUE_H

