#include "goku.h"

Goku::Goku()
{
    // Cargar desde recursos
    spriteSheet.load(":/imagenes/gokuv3.png");

    // Sprite inicial (quieto)
    actualizarSprite(0);
    setPos(200, 300);

    // Activar recepción de teclas
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Goku::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        actualizarSprite(2);
        moveBy(-10, 0);
    }
    else if (event->key() == Qt::Key_Right) {
        actualizarSprite(1);
        moveBy(10, 0);
    }
    else if (event->key() == Qt::Key_Up) {
        actualizarSprite(3);
        moveBy(0, -10);
    }
    else if (event->key() == Qt::Key_Down) {
        actualizarSprite(4);
        moveBy(0, 10);
    }
}

void Goku::actualizarSprite(int tipo)
{
    int spriteWidth = 87;
    int spriteHeight = 684;

    int x = tipo * spriteWidth;
    int y = 0;

    QPixmap recorte = spriteSheet.copy(x, y, spriteWidth, spriteHeight);
    setPixmap(recorte.scaled(100, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
