#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QApplication>
#include <QScreen>
#include <QFontMetrics>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Obtener resolución de la pantalla
    QRect screenSize = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenSize.width();
    int screenHeight = screenSize.height();

    // Crear escena adaptada al tamaño de pantalla
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, screenWidth, screenHeight);
    ui->graphicsView->setScene(scene);

    // Fondo
    QPixmap fondo("C:/Users/Sebastian/Desktop/Sebastian/UdeA/semestre 2025-1/Informatica 2/Proyecto final/escenario/menu.jpg");
    QPixmap fondoEscalado = fondo.scaled(screenWidth, screenHeight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QGraphicsPixmapItem* fondoItem = scene->addPixmap(fondoEscalado);
    fondoItem->setZValue(-1);
    fondoItem->setPos(0, 0);

    // Título
    titulo = scene->addText("DRAGON BALL Z");
    QFont fontTitulo("Arial", 64, QFont::Bold);
    titulo->setFont(fontTitulo);
    titulo->setDefaultTextColor(Qt::yellow);

    QFontMetrics fmTitulo(fontTitulo);
    int tituloWidth = fmTitulo.horizontalAdvance("DRAGON BALL Z");
    titulo->setPos((screenWidth - tituloWidth) / 2, screenHeight * 0.2);

    // Botones
    QFont fontBoton("Arial", 48, QFont::Bold);
    QFontMetrics fmBoton(fontBoton);

    text = scene->addText("Jugar");
    text->setFont(fontBoton);
    text->setDefaultTextColor(Qt::white);

    text2 = scene->addText("Salir");
    text2->setFont(fontBoton);
    text2->setDefaultTextColor(Qt::white);

    int textWidth1 = fmBoton.horizontalAdvance("Jugar");
    int textWidth2 = fmBoton.horizontalAdvance("Salir");
    int espacio = 100;
    int totalAncho = textWidth1 + espacio + textWidth2;
    int startX = (screenWidth - totalAncho) / 2;
    int yBotones = screenHeight * 0.6;

    text->setPos(startX, yBotones);
    text2->setPos(startX + textWidth1 + espacio, yBotones);

    // Mostrar pantalla completa
    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}
