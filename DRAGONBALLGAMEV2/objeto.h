#ifndef OBJETO_H
#define OBJETO_H

#include <QObject>
#include <QGraphicsPixmapItem>

class objeto : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    objeto(QObject* parent = nullptr);
};

#endif // OBJETO_H
