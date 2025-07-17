#include "goku.h"
#include "ataques.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>

int goku::contadorAtaques = 0;
bool goku::enEnfriamiento = false;

goku::goku(QObject *parent)
    : QObject(parent),
    original(":/sprite/goku.png"),
    vida(10),
    escalaVisual(100),
    velY(0),
    enElAire(false),
    mirandoIzquierda(false),
    gravedadTimer(new QTimer(this)),
    movimientoTimer(new QTimer(this)),
    barraVida(new Atributos(vida, this))
{
    if (original.isNull()) {
        qDebug() << "Error: No se pudo cargar sprite de Goku";
    }

    recortarSprite(44, 47, 48, 44);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    connect(gravedadTimer, &QTimer::timeout, this, &goku::aplicarGravedad);
    gravedadTimer->start(20);

    connect(movimientoTimer, &QTimer::timeout, this, &goku::moverEnAire);
    movimientoTimer->start(20);
}

goku::~goku()
{
    gravedadTimer->stop();
    movimientoTimer->stop();
}

void goku::recibirDano(int cantidad)
{
    vida = qMax(0, vida - cantidad);
    barraVida->setVida(vida);
    qDebug() << "Goku recibió daño. Vida:" << vida;

    if (vida <= 0) {
        qDebug() << "Goku ha sido derrotado";
        if (scene()) {
            scene()->removeItem(this);
        }
        deleteLater();
    }
}

int goku::getVida() const
{
    return vida;
}

void goku::recortarSprite(int x, int y, int w, int h)
{
    if (!original.isNull()) {
        anchoRecorte = w;
        altoRecorte = h;
        pixmap = original.copy(x, y, w, h);
        update();
    }
}

QRectF goku::boundingRect() const
{
    return QRectF(-escalaVisual / 2, -escalaVisual / 2, escalaVisual, escalaVisual);
}

void goku::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (pixmap.isNull()) return;

    QPixmap escalado = pixmap.scaled(escalaVisual, escalaVisual, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if (mirandoIzquierda) {
        painter->drawPixmap(-escalaVisual / 2, -escalaVisual / 2,
                            escalado.transformed(QTransform().scale(-1, 1)));
    } else {
        painter->drawPixmap(-escalaVisual / 2, -escalaVisual / 2, escalado);
    }
}

void goku::keyPressEvent(QKeyEvent *event)
{
    teclasPresionadas.insert(event->key());

    if (event->key() == Qt::Key_W && !enElAire) {
        velY = -12.0;
        enElAire = true;
        moveBy(0, velY);
        recortarSprite(0, 200, 50, 44);
    } else if (event->key() == Qt::Key_H && !enEnfriamiento) {
        lanzarAtaque();
    }
}

void goku::keyReleaseEvent(QKeyEvent *event)
{
    teclasPresionadas.remove(event->key());
}

void goku::aplicarGravedad()
{
    const float suelo = 800;
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
    const float limiteIzquierdo = 200;
    const float limiteDerecho = 1420;

    if (teclasPresionadas.contains(Qt::Key_A)) {
        if (x() - escalaVisual / 2 > limiteIzquierdo) {
            moveBy(-5, 0);
            mirandoIzquierda = true;
            recortarSprite(150, 45, 50, 44);
        }
    } else if (teclasPresionadas.contains(Qt::Key_D)) {
        if (x() + escalaVisual / 2 < limiteDerecho) {
            moveBy(5, 0);
            mirandoIzquierda = false;
            recortarSprite(95, 45, 50, 44);
        }
    } else {
        recortarSprite(44, 47, 48, 44);
    }
}

void goku::lanzarAtaque()
{
    if (!scene() || enEnfriamiento) return;

    Ataque *ataque = new Ataque(!mirandoIzquierda, this);
    ataque->setPos(x(), y());
    scene()->addItem(ataque);

    contadorAtaques++;
    if (contadorAtaques >= 5) {
        enEnfriamiento = true;
        QTimer::singleShot(5000, []() {
            contadorAtaques = 0;
            enEnfriamiento = false;
        });
    }
}

