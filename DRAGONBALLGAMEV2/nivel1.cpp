#include "nivel1.h"
#include "goku.h"

Nivel1::Nivel1(int width, int height, QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, width, height);

    QPixmap fondo("C:/Users/Sebastian/Pictures/dragon ball imagenes/ring.jpg");
    QPixmap fondoEscalado = fondo.scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QGraphicsPixmapItem* fondoItem = addPixmap(fondoEscalado);
    fondoItem->setZValue(-1);
    fondoItem->setPos(0, 0);

    // AGREGAR GOKU
    Goku* goku = new Goku();
    addItem(goku);
    goku->setFlag(QGraphicsItem::ItemIsFocusable);
    goku->setFocus();  // Para que reciba eventos de teclado
}
