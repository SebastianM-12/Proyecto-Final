#ifndef ATAQUE_H
#define ATAQUE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class ataque : public QObject
{
    Q_OBJECT
public:
    explicit ataque(QObject *parent = nullptr);

signals:
};

#endif // ATAQUE_H
