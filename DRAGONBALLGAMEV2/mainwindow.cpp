#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include "goku.h"
#include "customgraphicsview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , escenaMenu(nullptr)
    , escenaJuego(nullptr)
    , btnJugar(nullptr)
    , btnNivel2(nullptr)
    , btnSalir(nullptr)
{
    ui->setupUi(this);
    configurarMenu();
}

void MainWindow::configurarMenu()
{
    QRect screenSize = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenSize.width();
    int screenHeight = screenSize.height();

    escenaMenu = new QGraphicsScene(this);
    escenaMenu->setSceneRect(0, 0, screenWidth, screenHeight);
    ui->graphicsView->setScene(escenaMenu);

    QPixmap fondo("C:/Users/Sebastian/Pictures/dragon ball imagenes/menu.jpg");
    if (fondo.isNull()) {
        qDebug() << " Imagen de menú no cargada";
        fondo = QPixmap(screenWidth, screenHeight);
        fondo.fill(Qt::darkBlue);
    }

    escenaMenu->addPixmap(fondo.scaled(screenWidth, screenHeight, Qt::KeepAspectRatioByExpanding));

    if (!btnJugar) {
        btnJugar = new QPushButton("NIVEL 1", this);
        btnJugar->setStyleSheet(estiloBotones());
        btnJugar->resize(200, 50);
        connect(btnJugar, &QPushButton::clicked, this, &MainWindow::iniciarJuegoNivel1);
    }

    if (!btnNivel2) {
        btnNivel2 = new QPushButton("NIVEL 2", this);
        btnNivel2->setStyleSheet(estiloBotones());
        btnNivel2->resize(200, 50);
        connect(btnNivel2, &QPushButton::clicked, this, &MainWindow::iniciarJuegoNivel2);
    }

    if (!btnSalir) {
        btnSalir = new QPushButton("SALIR", this);
        btnSalir->setStyleSheet(estiloBotones());
        btnSalir->resize(200, 50);
        connect(btnSalir, &QPushButton::clicked, this, &MainWindow::close);
    }

    int spacing = 60;
    int totalWidth = 200 * 3 + spacing * 2;
    int startX = (screenWidth - totalWidth) / 2;
    int y = screenHeight * 0.85;

    btnJugar->move(startX, y);
    btnNivel2->move(startX + 200 + spacing, y);
    btnSalir->move(startX + 2 * (200 + spacing), y);

    btnJugar->show();
    btnNivel2->show();
    btnSalir->show();

    this->showFullScreen();
}

QString MainWindow::estiloBotones() const
{
    return "QPushButton { background-color: rgba(255,255,255,180); color: black; font: bold 20px 'Arial'; "
           "border: 2px solid black; border-radius: 10px; padding: 5px; }"
           "QPushButton:hover { background-color: rgba(0,0,0,150); color: white; }";
}

void MainWindow::iniciarJuegoNivel1()
{
    limpiarEscenaJuego();

    btnJugar->hide();
    btnNivel2->hide();
    btnSalir->hide();

    QRect screenSize = QGuiApplication::primaryScreen()->geometry();
    escenaJuego = new Nivel1(screenSize.width(), screenSize.height(), this);
    ui->graphicsView->setScene(escenaJuego);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);

    connect(escenaJuego, &Nivel1::tiempoAgotado, this, &MainWindow::volverAlMenu);

    // Conexión con enemigoDerrotado
    connect(escenaJuego, &Nivel1::enemigoDerrotado, this, [=]() {
        QMessageBox::information(this, "Victoria", "¡Derrotaste al enemigo!");
        volverAlMenu();
    });

    QTimer::singleShot(100, this, [=]() {
        asignarFocoAGoku();
        if (auto view = qobject_cast<CustomGraphicsView*>(ui->graphicsView)) {
            view->setTargetItemForFocus(escenaJuego->getGoku());
        }
    });
}

void MainWindow::iniciarJuegoNivel2()
{
    limpiarEscenaJuego();

    btnJugar->hide();
    btnNivel2->hide();
    btnSalir->hide();

    QRect screenSize = QGuiApplication::primaryScreen()->geometry();
    escenaJuego = new Nivel1(screenSize.width(), screenSize.height(), this);
    escenaJuego->avanzarAFaseSiguiente();  // Ir directamente a fase 2 (sin enemigo)
    ui->graphicsView->setScene(escenaJuego);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);

    connect(escenaJuego, &Nivel1::tiempoAgotado, this, &MainWindow::volverAlMenu);

    QTimer::singleShot(100, this, [=]() {
        asignarFocoAGoku();
        if (auto view = qobject_cast<CustomGraphicsView*>(ui->graphicsView)) {
            view->setTargetItemForFocus(escenaJuego->getGoku());
        }
    });
}

void MainWindow::asignarFocoAGoku()
{
    if (!escenaJuego) return;
    goku* personaje = escenaJuego->getGoku();
    if (!personaje) return;

    personaje->setFocus(Qt::OtherFocusReason);

    QTimer* focoTimer = new QTimer(this);
    connect(focoTimer, &QTimer::timeout, this, [=]() {
        if (!personaje->hasFocus()) {
            personaje->setFocus(Qt::OtherFocusReason);
            qDebug() << "Intentando reasignar foco a Goku...";
        } else {
            focoTimer->stop();
            focoTimer->deleteLater();
            qDebug() << "Goku  tiene el foco.";
        }
    });
    focoTimer->start(100);
}

void MainWindow::volverAlMenu()
{
    qDebug() << "[MainWindow] Volviendo al menú tras señal.";
    limpiarEscenaJuego();
    configurarMenu();
}

void MainWindow::limpiarEscenaJuego()
{
    if (escenaJuego) {
        if (auto view = qobject_cast<CustomGraphicsView*>(ui->graphicsView)) {
            view->setTargetItemForFocus(nullptr);
        }
        escenaJuego->clear();
        delete escenaJuego;
        escenaJuego = nullptr;
    }
}

MainWindow::~MainWindow()
{
    delete escenaMenu;
    limpiarEscenaJuego();
    delete ui;
}

