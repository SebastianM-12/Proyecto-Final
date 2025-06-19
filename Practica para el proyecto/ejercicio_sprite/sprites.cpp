#include "sprites.h"

sprite::sprite(QObject *parent)
    : QObject{parent}{

    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/imagenes/donalPNG.png");
    //Dimensiones de las imagenes
    ancho = 100;
    alto = 100;

    timer -> start(250);

    connect(timer,&QTimer::timeout,this,&sprite::Actualizacion);



}


void sprite::Actualizacion(){

    columnas +=100;
    if(columnas >=600){
        columnas=0;
    }
    this -> update(-ancho/2,-alto/2,ancho,alto);


}
QRectF sprite::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);


}

void sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,0,ancho,alto);

}

