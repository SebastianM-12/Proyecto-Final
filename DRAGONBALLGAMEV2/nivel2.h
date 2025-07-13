#ifndef NIVEL2_H
#define NIVEL2_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class nivel2 : public QObject
{
    Q_OBJECT
public:
    explicit nivel2(QObject *parent = nullptr);

signals:
};

#endif // NIVEL2_H
