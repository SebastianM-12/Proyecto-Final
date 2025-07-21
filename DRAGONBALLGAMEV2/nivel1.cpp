#include "nivel1.h"
#include "ataques.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFont>
#include <QTimer>
#include <QRandomGenerator>

Nivel1::Nivel1(int width, int height, QObject* parent)
    : QGraphicsScene(parent),
    m_goku(new goku()),
    m_enemigo(nullptr),
    textoTemporizador(nullptr),
    temporizador(new QTimer(this)),
    tiempoRestante(50),
    faseActual(1),
    altoEscena(height),
    anchoEscena(width),
    vidaGoku(nullptr),
    vidaEnemigo(nullptr)
{
    setSceneRect(0, 0, width, height);
    configurarFondo(width, height);
    configurarTemporizador();
    configurarFase();
}

goku* Nivel1::getGoku() const {
    return m_goku;
}

void Nivel1::configurarFondo(int width, int height)
{
    QString fondoRuta = "C:/Users/Sebastian/Pictures/dragon ball imagenes/ring.jpg";
    QPixmap fondo(fondoRuta);
    if (!fondo.isNull()) {
        addPixmap(fondo.scaled(width, height, Qt::KeepAspectRatioByExpanding));
    } else {
        qDebug() << "Imagen del fondo no cargada: " << fondoRuta;
    }
}

void Nivel1::configurarTemporizador()
{
    textoTemporizador = new QGraphicsTextItem();
    textoTemporizador->setDefaultTextColor(Qt::white);
    textoTemporizador->setFont(QFont("Arial", 20, QFont::Bold));
    textoTemporizador->setPos(30, 60);
    addItem(textoTemporizador);

    actualizarTemporizador();

    connect(temporizador, &QTimer::timeout, this, &Nivel1::actualizarTemporizador);
    temporizador->start(1000);
}

void Nivel1::configurarFase()
{
    if (m_goku) {
        addItem(m_goku);
        m_goku->setPos(200, 750 - m_goku->boundingRect().height() / 2);
        m_goku->setFlag(QGraphicsItem::ItemIsFocusable);
        m_goku->setFocus(Qt::OtherFocusReason);
        m_goku->setNivel(this);
    }

    if (!vidaGoku) {
        vidaGoku = new Atributo(10, 30, 30, Qt::green, this);
    } else {
        vidaGoku->reiniciar();
    }

    if (faseActual == 1) {
        crearEnemigo(Chaoz);
    } else if (faseActual == 2) {
        crearEnemigo(Ten);

        QTimer* timerAmbiente = new QTimer(this);
        connect(timerAmbiente, &QTimer::timeout, this, &Nivel1::lanzarAtaquesAmbientales);
        timerAmbiente->start(8000);
    }
}

void Nivel1::crearEnemigo(TipoEnemigo tipo)
{
    if (!m_enemigo) {
        m_enemigo = new Enemigo(tipo);
        addItem(m_enemigo);
        m_enemigo->setPos(1000, 750 - m_enemigo->boundingRect().height() / 2);
        m_enemigo->setNivel(this);

        connect(m_enemigo, &Enemigo::enemigoDerrotado, this, [=]() {
            qDebug() << "Enemigo derrotado";
            emit enemigoDerrotado();
        });
    }

    if (!vidaEnemigo) {
        int vidaMaxima = (tipo == Chaoz) ? 30 : 50;
        vidaEnemigo = new Atributo(vidaMaxima, 900, 30, Qt::red, this);
    } else {
        vidaEnemigo->reiniciar();
    }
}

void Nivel1::eliminarEnemigo()
{
    if (m_enemigo) {
        removeItem(m_enemigo);
        m_enemigo->deleteLater();
        m_enemigo = nullptr;
        qDebug() << "Enemigo eliminado correctamente";
    }
}

void Nivel1::actualizarTemporizador()
{
    int minutos = tiempoRestante / 60;
    int segundos = tiempoRestante % 60;
    textoTemporizador->setPlainText(
        QString("Tiempo restante: %1:%2")
            .arg(minutos, 2, 10, QLatin1Char('0'))
            .arg(segundos, 2, 10, QLatin1Char('0')));

    tiempoRestante--;
    if (tiempoRestante < 0) {
        temporizador->stop();
        textoTemporizador->setPlainText("¡Tiempo agotado!");
        eliminarEnemigo();
        emit tiempoAgotado();
    }
}

void Nivel1::limpiarFaseActual()
{
    if (temporizador)
        temporizador->stop();

    QList<QGraphicsItem*> copiaItems = items();
    for (QGraphicsItem* item : copiaItems) {
        if (auto ataque = dynamic_cast<Ataque*>(item)) {
            ataque->destruir();
        }
    }

    eliminarEnemigo();

    if (vidaGoku) {
        vidaGoku->liberar();
        delete vidaGoku;
        vidaGoku = nullptr;
    }

    if (vidaEnemigo) {
        vidaEnemigo->liberar();
        delete vidaEnemigo;
        vidaEnemigo = nullptr;
    }

    if (m_goku) {
        removeItem(m_goku);
        delete m_goku;
        m_goku = nullptr;
    }

    if (textoTemporizador) {
        removeItem(textoTemporizador);
        delete textoTemporizador;
        textoTemporizador = nullptr;
    }

    clear();
}

void Nivel1::avanzarAFaseSiguiente()
{
    faseActual++;
    qDebug() << "Avanzando a fase " << faseActual;

    limpiarFaseActual();

    m_goku = new goku();
    tiempoRestante = 70;
    configurarFondo(anchoEscena, altoEscena);
    configurarTemporizador();
    configurarFase();
}

void Nivel1::reducirVidaGoku()
{
    if (vidaGoku)
        vidaGoku->reducir();
}

void Nivel1::lanzarAtaquesAmbientales()
{
    for (int i = 0; i < 3; ++i) {
        int xAleatorio = QRandomGenerator::global()->bounded(500, 1400);
        Ataque* ki = new Ataque(false, nullptr);
        ki->setPos(xAleatorio, -50);
        ki->setReboteYRotacion(true);
        addItem(ki);
    }

    qDebug() << "Ataques ambientales lanzados";
}
