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

    QRect screenSize = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenSize.width();
    int screenHeight = screenSize.height();

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, screenWidth, screenHeight);
    ui->graphicsView->setScene(scene);

    QPixmap fondo("C:/Users/Sebastian/Pictures/dragon ball imagenes/menu.jpg");  // usa ruta relativa si puedes
    QPixmap fondoEscalado = fondo.scaled(screenWidth, screenHeight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QGraphicsPixmapItem* fondoItem = scene->addPixmap(fondoEscalado);
    fondoItem->setZValue(-1);
    fondoItem->setPos(0, 0);

    QFont fuenteBoton("Arial", 48, QFont::Bold);
    QFontMetrics fm(fuenteBoton);

    text = scene->addText("Jugar");
    text->setFont(fuenteBoton);
    text->setDefaultTextColor(Qt::white);

    text2 = scene->addText("Salir");
    text2->setFont(fuenteBoton);
    text2->setDefaultTextColor(Qt::white);

    int textWidth1 = fm.horizontalAdvance("Jugar");
    int textWidth2 = fm.horizontalAdvance("Salir");
    int spacing = 100;
    int totalWidth = textWidth1 + spacing + textWidth2;
    int startX = (screenWidth - totalWidth) / 2;
    int y = screenHeight * 0.85;

    text->setPos(startX, y);
    text2->setPos(startX + textWidth1 + spacing, y);

    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}
