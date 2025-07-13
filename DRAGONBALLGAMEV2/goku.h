#ifndef GOKU_H
#define GOKU_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPixmap>

class Goku : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Goku();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QPixmap spriteSheet;
    void actualizarSprite(int tipo);
};

#endif // GOKU_H
