#include "ataques.h"
#include "enemigo.h"
#include "nivel1.h"
#include "goku.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>

QMap<Enemigo*, int> Ataque::velocidadOriginal;

Ataque::Ataque(bool direccionDerecha, goku* jugador, QObject* parent)
    : QObject(parent), jugador(jugador), velocidadX(direccionDerecha ? 10 : -10),
    velocidadY(-5), gravedad(0.5), eliminado(false), reboteActivado(false),
    yaReboto(false), rotacionAngulo(5)
{
    pixmap = QPixmap(":/sprite/ki.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setParentItem(nullptr);
    setZValue(1);
    setFlag(QGraphicsItem::ItemIsMovable);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ataque::mover);
    timer->start(20);
}

Ataque::~Ataque() {}

QRectF Ataque::boundingRect() const {
    return QRectF(-pixmap.width() / 2, -pixmap.height() / 2, pixmap.width(), pixmap.height());
}

void Ataque::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (!pixmap.isNull()) {
        painter->drawPixmap(-pixmap.width() / 2, -pixmap.height() / 2, pixmap);
    }
}

void Ataque::setReboteYRotacion(bool activar) {
    reboteActivado = activar;
}

void Ataque::mover() {
    if (eliminado || !scene()) return;

    setPos(x() + velocidadX, y() + velocidadY);

    if (reboteActivado && !yaReboto && y() >= 850) {
        velocidadY = -velocidadY * 0.5;
        yaReboto = true;
    } else {
        velocidadY += gravedad;
    }

    if (reboteActivado && yaReboto) {
        setRotation(rotation() + rotacionAngulo);
    }

    for (QGraphicsItem* item : collidingItems()) {
        if (Enemigo* enemigo = dynamic_cast<Enemigo*>(item)) {
            enemigo->recibirDanio(1);
            destruir();
            return;
        }

        if (goku* g = dynamic_cast<goku*>(item)) {
            // No dañar al Goku que lanzó el ataque
            if (jugador != nullptr && g == jugador)
                continue;

            // Si viene del cielo (ataque ambiental), sí daña
            g->recibirDanio(1);
            destruir();
            return;
        }
    }

    if (x() < 0 || x() > 1600 || y() > 1000) {
        destruir();
    }
}

void Ataque::lanzarDash(Enemigo* enemigo) {
    if (!enemigo) return;
    int velocidadOriginalEnemigo = enemigo->getVelocidadX();
    velocidadOriginal[enemigo] = velocidadOriginalEnemigo;
    enemigo->setVelocidadX(velocidadOriginalEnemigo * 2);

    QTimer::singleShot(1000, [enemigo]() {
        if (enemigo && velocidadOriginal.contains(enemigo)) {
            enemigo->setVelocidadX(velocidadOriginal[enemigo]);
            velocidadOriginal.remove(enemigo);
        }
    });
}

void Ataque::destruir() {
    eliminado = true;
    if (scene()) scene()->removeItem(this);
    deleteLater();
}

