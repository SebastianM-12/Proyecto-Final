#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include <QMessageBox>
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
    void iniciarJuego();
    void manejarVictoria();
    void volverAlMenu();

private:
    void configurarMenu();
    void limpiarEscenaJuego();
    void configurarBotones();

    Ui::MainWindow *ui;
    QGraphicsScene* escenaMenu;
    Nivel1* escenaJuego;
    QPushButton* btnJugar;
    QPushButton* btnSalir;
};

#endif // MAINWINDOW_H

