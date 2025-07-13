#ifndef GOKU_H
#define GOKU_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class goku : public QObject
{
    Q_OBJECT
public:
    explicit goku(QObject *parent = nullptr);

signals:
};

#endif // GOKU_H
