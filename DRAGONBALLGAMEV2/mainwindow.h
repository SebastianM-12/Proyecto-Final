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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void iniciarJuegoNivel1();
    void iniciarJuegoNivel2();
    void volverAlMenu();
    void asignarFocoAGoku();

private:
    void configurarMenu();
    void limpiarEscenaJuego();
    QString estiloBotones() const;

    Ui::MainWindow *ui;
    QGraphicsScene* escenaMenu;
    Nivel1* escenaJuego;
    QPushButton* btnJugar;
    QPushButton* btnNivel2;
    QPushButton* btnSalir;
};

#endif // MAINWINDOW_H

