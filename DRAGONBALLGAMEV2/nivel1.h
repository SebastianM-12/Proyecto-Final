#ifndef NIVEL1_H
#define NIVEL1_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include "goku.h"
#include "enemigo.h"
#include "atributos.h"

class Nivel1 : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Nivel1(int width, int height, QObject* parent = nullptr);
    goku* getGoku() const;
    void reducirVidaGoku();

    Atributo* vidaGoku;
    Atributo* vidaEnemigo;

signals:
    void tiempoAgotado();
    void enemigoDerrotado();

public slots:
    void avanzarAFaseSiguiente();

private slots:
    void actualizarTemporizador();
    void lanzarAtaquesAmbientales();

private:
    void configurarFondo(int width, int height);
    void configurarTemporizador();
    void configurarFase();
    void limpiarFaseActual();
    void crearEnemigo(TipoEnemigo tipo);
    void eliminarEnemigo();

    goku* m_goku;
    Enemigo* m_enemigo;
    QGraphicsTextItem* textoTemporizador;
    QTimer* temporizador;
    int tiempoRestante;
    int faseActual;

    int altoEscena;
    int anchoEscena;
};

#endif // NIVEL1_H
