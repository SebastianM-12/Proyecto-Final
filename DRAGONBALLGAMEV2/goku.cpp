#include "goku.h"
#include "ataques.h"
#include "nivel1.h"
#include "atributos.h"
#include <QDebug>
#include <QTimer>
#include <QTransform>
#include <QGraphicsScene>

goku::goku(QObject *parent)
    : QObject(parent),
    original(":/sprite/goku.png"),
    escalaVisual(100),
    velY(0),
    enElAire(false),
    mirandoIzquierda(false),
    gravedadTimer(new QTimer(this)),
    movimientoTimer(new QTimer(this)),
    vida(10),
    nivel(nullptr),
    puedeRecibirDanio(true)
{
    if (original.isNull())
        qDebug() << "Sprite Goku no cargado";

    recortarSprite(44, 47, 48, 44);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    for (int i = 0; i < MAX_KI; ++i)
        slotsDisparo[i] = true;

    QTimer::singleShot(200, this, [this]() {
        this->setFocus(Qt::OtherFocusReason);
    });

    connect(gravedadTimer, &QTimer::timeout, this, &goku::aplicarGravedad);
    connect(movimientoTimer, &QTimer::timeout, this, &goku::moverEnAire);
    gravedadTimer->start(20);
    movimientoTimer->start(20);
}

goku::~goku()
{
    gravedadTimer->stop();
    movimientoTimer->stop();
}

void goku::setNivel(Nivel1* n)
{
    nivel = n;
}

void goku::setVida(int v)
{
    vida = v;
}

int goku::getVida() const
{
    return vida;
}

void goku::recibirDanio(int cantidad)
{
    if (!puedeRecibirDanio || vida <= 0)
        return;

    vida -= cantidad;
    puedeRecibirDanio = false;

    if (nivel && nivel->vidaGoku)
        nivel->vidaGoku->reducir();

    qDebug() << "Goku recibió daño. Vida restante:" << vida;

    if (vida <= 0) {
        qDebug() << "Goku ha sido derrotado";
        if (scene()) scene()->removeItem(this);
        deleteLater();
        return;
    }


    QTimer::singleShot(2000, this, [this]() {
        puedeRecibirDanio = true;
        qDebug() << " Goku puede recibir daño nuevamente";
    });
}

void goku::recortarSprite(int x, int y, int w, int h)
{
    if (!original.isNull()) {
        pixmap = original.copy(x, y, w, h);
        update();
    }
}

QRectF goku::boundingRect() const
{
    return QRectF(-escalaVisual / 2, -escalaVisual / 2, escalaVisual, escalaVisual);
}

void goku::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (pixmap.isNull()) return;

    QPixmap escalado = pixmap.scaled(escalaVisual, escalaVisual, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if (mirandoIzquierda)
        painter->drawPixmap(-escalaVisual / 2, -escalaVisual / 2, escalado.transformed(QTransform().scale(-1, 1)));
    else
        painter->drawPixmap(-escalaVisual / 2, -escalaVisual / 2, escalado);
}

int goku::obtenerSlotLibre()
{
    for (int i = 0; i < MAX_KI; ++i) {
        if (slotsDisparo[i])
            return i;
    }
    return -1;
}

void goku::keyPressEvent(QKeyEvent *event)
{
    teclasPresionadas.insert(event->key());

    if (event->key() == Qt::Key_W && !enElAire) {
        velY = -12.0;
        enElAire = true;
        moveBy(0, velY);
        recortarSprite(0, 200, 50, 44);
    }

    if (event->key() == Qt::Key_H && scene()) {
        int slot = obtenerSlotLibre();
        if (slot != -1) {
            slotsDisparo[slot] = false;

            Ataque* ki = new Ataque(!mirandoIzquierda, this, this);
            ki->setPos(x(), y());
            scene()->addItem(ki);

            QTimer::singleShot(5000, this, [this, slot]() {
                habilitarSlotDisparo(slot);
            });

            qDebug() << "Disparo lanzado en slot" << slot;
        } else {
            qDebug() << "Todos los disparos en enfriamiento";
        }
    }
}

void goku::habilitarSlotDisparo(int slot)
{
    if (slot >= 0 && slot < MAX_KI) {
        slotsDisparo[slot] = true;
        qDebug() << "Disparo en slot" << slot << "habilitado";
    }
}

void goku::keyReleaseEvent(QKeyEvent *event)
{
    teclasPresionadas.remove(event->key());
}

void goku::focusInEvent(QFocusEvent *)
{
    setFocus();
}

void goku::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setFocus();
}

void goku::aplicarGravedad()
{
    const float suelo = 850;
    float bordeInferior = y() + escalaVisual / 2;

    if (bordeInferior >= suelo) {
        setY(suelo - escalaVisual / 2);
        velY = 0;
        enElAire = false;
        recortarSprite(44, 47, 48, 44);
    } else {
        velY += 0.5;
        moveBy(0, velY);
        enElAire = true;
    }
}

void goku::moverEnAire()
{
    const float izq = 200, der = 1420;

    if (teclasPresionadas.contains(Qt::Key_A) && x() - escalaVisual / 2 > izq) {
        moveBy(-5, 0);
        mirandoIzquierda = true;
        recortarSprite(150, 45, 50, 44);
    } else if (teclasPresionadas.contains(Qt::Key_D) && x() + escalaVisual / 2 < der) {
        moveBy(5, 0);
        mirandoIzquierda = false;
        recortarSprite(95, 45, 50, 44);
    } else {
        recortarSprite(44, 47, 48, 44);
    }
}

