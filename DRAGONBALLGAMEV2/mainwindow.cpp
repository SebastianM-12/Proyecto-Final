#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Obtener tamaño de pantalla
    QRect screenSize = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenSize.width();
    int screenHeight = screenSize.height();

    // Crear escena y asignarla
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, screenWidth, screenHeight);
    ui->graphicsView->setScene(scene);

    // Fondo de menú
    QPixmap fondo("C:/Users/Sebastian/Pictures/dragon ball imagenes/menu.jpg");
    QPixmap fondoEscalado = fondo.scaled(screenWidth, screenHeight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QGraphicsPixmapItem* fondoItem = scene->addPixmap(fondoEscalado);
    fondoItem->setZValue(-1);
    fondoItem->setPos(0, 0);

    // --- BOTONES CON ESTILO ---
    int btnAncho = 200;
    int btnAlto = 50;
    int spacing = 60;

    btnJugar = new QPushButton("JUGAR", this);
    btnSalir = new QPushButton("SALIR", this);

    // Estilo
    QString estilo = "QPushButton {"
                     "background-color: rgba(255, 255, 255, 180);"
                     "color: black;"
                     "font: bold 20px 'Arial';"
                     "border: 2px solid black;"
                     "}"
                     "QPushButton:hover {"
                     "background-color: rgba(0, 0, 0, 150);"
                     "color: white;"
                     "}";

    btnJugar->setStyleSheet(estilo);
    btnSalir->setStyleSheet(estilo);

    btnJugar->resize(btnAncho, btnAlto);
    btnSalir->resize(btnAncho, btnAlto);

    // Posicionarlos horizontalmente y centrarlos
    int totalWidth = btnAncho * 2 + spacing;
    int startX = (screenWidth - totalWidth) / 2;
    int y = screenHeight * 0.85;

    btnJugar->move(startX, y);
    btnSalir->move(startX + btnAncho + spacing, y);

    // Conectar botones
    connect(btnSalir, &QPushButton::clicked, this, &MainWindow::close);
    connect(btnJugar, &QPushButton::clicked, this, &MainWindow::iniciarJuego);

    // Pantalla completa
    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniciarJuego()
{
    // Ocultar los botones del menú
    btnJugar->hide();
    btnSalir->hide();

    // Eliminar la escena del menú
    delete scene;

    // Obtener tamaño de pantalla
    QRect screenSize = QGuiApplication::primaryScreen()->geometry();
    int width = screenSize.width();
    int height = screenSize.height();

    // Crear nivel1 y mostrarlo
    escenaNivel1 = new Nivel1(width, height);
    ui->graphicsView->setScene(escenaNivel1);
}

