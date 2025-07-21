#include "enemigo.h"
#include "ataques.h"
#include "nivel1.h"
#include "goku.h"
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>
#include <QTransform>
#include <QPainterPath>

Enemigo::Enemigo(TipoEnemigo tipo, QObject *parent)
    : QObject(parent),
    tipoEnemigo(tipo),
    movimientoTimer(new QTimer(this)),
    velY(0),
    enElAire(false),
    moviendoDerecha(true),
    mirandoDerecha(true),
    velocidadX(8),
    nivel(nullptr)
{
    if (tipo == Chaoz) {
        original = QPixmap(":/sprite/chaoz.png");
        vida = 30;
        escalaVisual = 120;
    } else if (tipo == Ten) {
        QPixmap tenRaw(":/sprite/ten.png");
        original = tenRaw.copy(10, 0, tenRaw.width() - 10, tenRaw.height());
        vida = 50;
        escalaVisual = 90;
    }

    if (original.isNull()) {
        qDebug() << "Error: No se pudo cargar sprite del enemigo";
        return;
    }

    recortarSprite(0, 0, 100, 100);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    connect(movimientoTimer, &QTimer::timeout, this, &Enemigo::moverAutomaticamente);
    movimientoTimer->start(20);
}

Enemigo::~Enemigo()
{
    movimientoTimer->stop();
}

void Enemigo::setNivel(Nivel1* n) { nivel = n; }

void Enemigo::recortarSprite(int x, int y, int w, int h)
{
    anchoRecorte = w;
    altoRecorte = h;
    pixmap = original.copy(x, y, w, h);
    update();
}

QRectF Enemigo::boundingRect() const
{
    return QRectF(-escalaVisual / 2, -escalaVisual / 2, escalaVisual, escalaVisual);
}

QPainterPath Enemigo::shape() const
{
    QPainterPath path;
    QRectF areaReducida = boundingRect().adjusted(15, 15, -15, -15);
    path.addRect(areaReducida);
    return path;
}

void Enemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (pixmap.isNull()) return;
    QPixmap escalado = pixmap.scaled(escalaVisual, escalaVisual, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if (mirandoDerecha)
        painter->drawPixmap(-escalaVisual / 2, -escalaVisual / 2, escalado.transformed(QTransform().scale(-1, 1)));
    else
        painter->drawPixmap(-escalaVisual / 2, -escalaVisual / 2, escalado);
}

void Enemigo::moverAutomaticamente()
{
    const float limiteIzquierdo = 200;
    const float limiteDerecho = 1420;
    const float suelo = 850;

    if ((x() + escalaVisual / 2) >= limiteDerecho) moviendoDerecha = false;
    else if ((x() - escalaVisual / 2) <= limiteIzquierdo) moviendoDerecha = true;

    mirandoDerecha = moviendoDerecha;
    moveBy(moviendoDerecha ? velocidadX : -velocidadX, 0);

    velY += 0.5;
    moveBy(0, velY);

    if (y() + escalaVisual / 2 >= suelo) {
        setY(suelo - escalaVisual / 2);
        velY = 0;
        enElAire = false;
        recortarSprite(0, 0, 100, 100);
    } else {
        enElAire = true;
        recortarSprite(100, 200, 100, 100);
    }

    if (!enElAire && QRandomGenerator::global()->bounded(100) < 3) {
        velY = -10.0;
        enElAire = true;
        recortarSprite(0, 200, 100, 100);
    }

    if (QRandomGenerator::global()->bounded(1000) < 2) {
        Ataque::lanzarDash(this);
    }

    if (nivel && nivel->getGoku() && collidesWithItem(nivel->getGoku())) {
        nivel->getGoku()->recibirDanio(1);
    }
}

void Enemigo::advance(int step)
{
    if (!step) return;
    moverAutomaticamente();
}

void Enemigo::setVelocidadX(int v) { velocidadX = v; }
int Enemigo::getVelocidadX() const { return velocidadX; }

void Enemigo::recibirDanio(int cantidad)
{
    vida -= cantidad;
    qDebug() << "Enemigo recibió daño. Vida restante:" << vida;

    if (nivel && nivel->vidaEnemigo)
        nivel->vidaEnemigo->reducir();

    if (vida <= 0) {
        qDebug() << "Enemigo derrotado";
        if (scene()) scene()->removeItem(this);
        emit enemigoDerrotado();
        deleteLater();
    }
}

bool Enemigo::estaVivo() const { return vida > 0; }
int Enemigo::getVida() const { return vida; }
