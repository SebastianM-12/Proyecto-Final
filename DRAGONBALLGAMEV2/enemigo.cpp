#include "enemigo.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QTransform>

Enemigo::Enemigo(QObject *parent)
    : QObject(parent),
    original(":/sprite/chaoz.png"),
    anchoRecorte(0),
    altoRecorte(0),
    escalaVisual(120),
    vida(20),
    movimientoTimer(new QTimer(this)),
    velY(0),
    enElAire(false),
    moviendoDerecha(true),
    mirandoDerecha(true),  // Inicialmente mirando a la derecha
    barraVida(new Atributos(vida, this))
{
    if(original.isNull()) {
        qDebug() << "Error: No se pudo cargar sprite del enemigo";
        return;
    }

    recortarSprite(0, 0, 100, 100); // Sprite inicial

    connect(movimientoTimer, &QTimer::timeout, this, &Enemigo::moverAutomaticamente);
    movimientoTimer->start(20);
}

Enemigo::~Enemigo()
{
    movimientoTimer->stop();
}

void Enemigo::recibirDano(int cantidad)
{
    vida = qMax(0, vida - cantidad);
    barraVida->setVida(vida);
    qDebug() << "Enemigo recibió daño. Vida:" << vida;

    if(vida <= 0) {
        emit enemigoDerrotado();
        if(scene()) scene()->removeItem(this);
        deleteLater();
    }
}

int Enemigo::getVida() const
{
    return vida;
}

void Enemigo::recortarSprite(int x, int y, int w, int h)
{
    anchoRecorte = w;
    altoRecorte = h;
    pixmap = original.copy(x, y, w, h);
    update();
}

QRectF Enemigo::boundingRect() const
{
    return QRectF(-escalaVisual/2, -escalaVisual/2, escalaVisual, escalaVisual);
}

void Enemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPixmap escalado = pixmap.scaled(escalaVisual, escalaVisual, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if(mirandoDerecha) {  // Cambiado el condicional
        // Voltear horizontalmente cuando mira a la derecha
        painter->drawPixmap(-escalaVisual/2, -escalaVisual/2,
                            escalado.transformed(QTransform().scale(-1, 1)));
    } else {
        // Dibujar normal cuando mira a la izquierda
        painter->drawPixmap(-escalaVisual/2, -escalaVisual/2, escalado);
    }
}

void Enemigo::moverAutomaticamente()
{
    if(vida <= 0) return;

    const float limiteIzquierdo = 200;
    const float limiteDerecho = 1420;
    const float suelo = 800;
    const int velocidadX = 8;

    // Cambiar dirección al llegar a los límites
    if((x() + escalaVisual/2) >= limiteDerecho) {
        moviendoDerecha = false;
    } else if((x() - escalaVisual/2) <= limiteIzquierdo) {
        moviendoDerecha = true;
    }

    // CORRECCIÓN: Sincronizar la dirección visual con el movimiento
    mirandoDerecha = moviendoDerecha;

    // Movimiento horizontal
    moveBy(moviendoDerecha ? velocidadX : -velocidadX, 0);

    // Gravedad
    velY += 0.5;
    moveBy(0, velY);

    // Colisión con el suelo
    if(y() + escalaVisual/2 >= suelo) {
        setY(suelo - escalaVisual/2);
        velY = 0;
        enElAire = false;
        recortarSprite(0, 0, 100, 100); // Sprite normal
    } else {
        enElAire = true;
        recortarSprite(100, 200, 100, 100); // Sprite en aire
    }

    // Salto aleatorio
    if(!enElAire && QRandomGenerator::global()->bounded(100) < 3) {
        velY = -10.0;
        enElAire = true;
        recortarSprite(0, 200, 100, 100); // Sprite de salto
    }
}
