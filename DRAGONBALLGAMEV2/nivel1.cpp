#include "nivel1.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>

Nivel1::Nivel1(int width, int height, QObject* parent)
    : QGraphicsScene(parent),
    m_goku(nullptr),
    m_enemigo(nullptr),
    m_colisionTimer(new QTimer(this))
{
    configurarEscena(width, height);
}

void Nivel1::configurarEscena(int width, int height) {
    setSceneRect(0, 0, width, height);

    QPixmap fondo("C:/Users/Sebastian/Pictures/dragon ball imagenes/ring.jpg");
    if(!fondo.isNull()) {
        addPixmap(fondo.scaled(width, height, Qt::KeepAspectRatioByExpanding));
    }

    m_goku = new goku();
    addItem(m_goku);
    m_goku->setPos(200, 800 - m_goku->boundingRect().height()/2);
    m_goku->setFlag(QGraphicsItem::ItemIsFocusable);
    m_goku->setFocus();

    m_enemigo = new Enemigo();
    addItem(m_enemigo);
    m_enemigo->setPos(m_goku->x() + 900, 800 - m_enemigo->boundingRect().height()/2);

    connect(m_enemigo, &Enemigo::enemigoDerrotado, this, &Nivel1::enemigoEliminado);

    connect(m_colisionTimer, &QTimer::timeout, [this]() {
        if(!m_goku || !m_enemigo) return;

        QPointF centroGoku = m_goku->pos() + m_goku->boundingRect().center();
        QPointF centroEnemigo = m_enemigo->pos() + m_enemigo->boundingRect().center();
        qreal distancia = QLineF(centroGoku, centroEnemigo).length();

        if(distancia < m_distanciaDano) {
            m_goku->recibirDano(1);
            qDebug() << "Daño aplicado. Distancia:" << distancia;
        }
    });
    m_colisionTimer->start(100);
}
