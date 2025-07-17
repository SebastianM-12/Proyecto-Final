#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , escenaMenu(nullptr)
    , escenaJuego(nullptr)
    , btnJugar(nullptr)
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
    if(fondo.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen del menú";
        fondo = QPixmap(screenWidth, screenHeight);
        fondo.fill(Qt::darkBlue);
    }
    QGraphicsPixmapItem* fondoItem = escenaMenu->addPixmap(fondo.scaled(screenWidth, screenHeight, Qt::KeepAspectRatioByExpanding));
    fondoItem->setZValue(-1);
    fondoItem->setPos(0, 0);

    int btnAncho = 200;
    int btnAlto = 50;
    int spacing = 60;

    btnJugar = new QPushButton("JUGAR", this);
    btnSalir = new QPushButton("SALIR", this);

    QString estilo = "QPushButton {"
                     "background-color: rgba(255, 255, 255, 180);"
                     "color: black;"
                     "font: bold 20px 'Arial';"
                     "border: 2px solid black;"
                     "border-radius: 10px;"
                     "padding: 5px;"
                     "}"
                     "QPushButton:hover {"
                     "background-color: rgba(0, 0, 0, 150);"
                     "color: white;"
                     "}";

    btnJugar->setStyleSheet(estilo);
    btnSalir->setStyleSheet(estilo);

    btnJugar->resize(btnAncho, btnAlto);
    btnSalir->resize(btnAncho, btnAlto);

    int totalWidth = btnAncho * 2 + spacing;
    int startX = (screenWidth - totalWidth) / 2;
    int y = screenHeight * 0.85;

    btnJugar->move(startX, y);
    btnSalir->move(startX + btnAncho + spacing, y);

    connect(btnSalir, &QPushButton::clicked, this, &MainWindow::close);
    connect(btnJugar, &QPushButton::clicked, this, &MainWindow::iniciarJuego);

    this->showFullScreen();
}

void MainWindow::iniciarJuego()
{
    btnJugar->hide();
    btnSalir->hide();

    QRect screenSize = QGuiApplication::primaryScreen()->geometry();
    escenaJuego = new Nivel1(screenSize.width(), screenSize.height(), this);

    ui->graphicsView->setScene(escenaJuego);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);

    connect(escenaJuego, &Nivel1::enemigoEliminado, this, &MainWindow::manejarVictoria);
}

void MainWindow::manejarVictoria()
{

    volverAlMenu();
}

void MainWindow::volverAlMenu()
{
    limpiarEscenaJuego();
    configurarMenu();
    btnJugar->show();
    btnSalir->show();
}

void MainWindow::limpiarEscenaJuego()
{
    if(escenaJuego) {
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

