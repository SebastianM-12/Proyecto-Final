#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include "nivel1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void iniciarJuego();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    Nivel1* escenaNivel1;

    QPushButton* btnJugar;
    QPushButton* btnSalir;
};

#endif // MAINWINDOW_H
