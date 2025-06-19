#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect Desktop = screen->geometry();

    x = Desktop.x();
    y = Desktop.y();
    ancho = Desktop.width()-100;
    alto = Desktop.height()-100;

    scene = new QGraphicsScene(x,y,ancho,alto);

    ui ->graphicsView->setScene(scene);

    Donald = new sprite();
    scene -> addItem(Donald);
    Donald ->setPos(200,700);

}


Widget::~Widget()
{
    delete ui;
}
