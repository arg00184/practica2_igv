#include <cstdlib>

#include "igvInterfaz.h"

igvInterfaz *igvInterfaz::_instancia = nullptr;

igvInterfaz::igvInterfaz() {
    camara.set(igvPunto3D(3.5, 4.0, 10.0),
               igvPunto3D(0.0, 0.0, 0.0),
               igvPunto3D(0.0, 1.0, 0.0));
}

igvInterfaz &igvInterfaz::getInstancia() {
    if (!_instancia) {
        _instancia = new igvInterfaz;
    }

    return *_instancia;
}

void igvInterfaz::configura_entorno(int argc, char **argv
                                    , int _ancho_ventana, int _alto_ventana
                                    , int _pos_X, int _pos_Y
                                    , std::string _titulo) {
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana, _alto_ventana);
    glutInitWindowPosition(_pos_X, _pos_Y);
    glutCreateWindow(_titulo.c_str());


    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    mostrarAyudaInicial();
}


void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop();
}

void igvInterfaz::cambiarModoInteraccion() {
    modoSeleccion = !modoSeleccion;

    if (modoSeleccion) {
        printf("Modo selección activado: Usa las teclas 1-4 o haz clic para elegir parte\n");
        printf("Luego controla el movimiento con las flechas (izq/der/arriba/abajo)\n");
        _instancia->escena.activarModoSeleccion(true);
        arrastrando = false;
    } else {
        printf("Modo teclado activado: Las teclas afectan directamente a todas las partes\n");
        _instancia->escena.activarModoSeleccion(false);
        arrastrando = false;
    }
}

void igvInterfaz::mostrarAyudaInicial() const {
    printf("====================== INSTRUCCIONES ======================\n");
    printf("Movimiento de cámara: flechas (vista libre), +/- zoom, P perspectiva/ortográfica\n");
    printf("Vista múltiple: tecla 4. Ejes: E. Encender movimiento continuo de cámara: C/F/B\n");
    printf("Iluminación y normales: H alterna sombreado plano/suave y uso de normales\n");
    printf("Animaciones: A anima la lámpara, G activa la órbita automática de la cámara\n");
    printf("Interacción con la lámpara: M cambia entre modo teclado y modo selección\n");
    printf("Seleccionar partes: teclas 1-4 o clic por color. Reset pose: R\n");
    printf("Mover partes (modo selección): flechas o arrastrar con botón izquierdo\n");
    printf("Brazo 2 y pantalla: Izq/Der giro lateral, Arr/Ab inclinación vertical\n");
    printf("Salir: ESC. \n");
    printf("============================================================\n");
}

void igvInterfaz::aplicarIncrementoSeleccionadoHorizontal(float incremento) {
    switch (escena.getParteSeleccionada()) {
        case 0:
            escena.rotarBaseLampara(incremento);
            break;
        case 1:
            escena.rotarBrazo1Lampara(incremento);
            break;
        case 2:
            escena.rotarBrazo2LateralLampara(incremento);
            break;
        case 3:
            escena.rotarPantallaLateralLampara(incremento);
            break;
        default:
            break;
    }
}

void igvInterfaz::aplicarIncrementoSeleccionadoVertical(float incremento) {
    switch (escena.getParteSeleccionada()) {
        case 0:
            escena.rotarBaseLampara(incremento);
            break;
        case 1:
            escena.rotarBrazo1Lampara(incremento);
            break;
        case 2:
            escena.rotarBrazo2Lampara(incremento);
            break;
        case 3:
            escena.rotarPantallaLampara(incremento);
            break;
        default:
            break;
    }
}

void igvInterfaz::aplicarMovimientoRaton(int dx, int dy) {
    if (escena.getParteSeleccionada() == -1) return;

    const float factor = 0.25f;
    switch (escena.getParteSeleccionada()) {
        case 0:
            escena.rotarBaseLampara(dx * factor);
            break;
        case 1:
            escena.rotarBrazo1Lampara(-dy * factor);
            break;
        case 2:
            escena.rotarBrazo2LateralLampara(dx * factor);
            escena.rotarBrazo2Lampara(-dy * factor);
            break;
        case 3:
            escena.rotarPantallaLateralLampara(dx * factor);
            escena.rotarPantallaLampara(-dy * factor);
            break;
        default:
            break;
    }
}

void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'e':
        case 'E':
            _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
            break;
        case 'c':
        case 'C':
            _instancia->camara.activarMovimiento();
            break;
        case 'f':
        case 'F':
            if (_instancia->camara.getMovimientoActivo())
                _instancia->camara.desplazarAdelante(0.2);
            break;
        case 'b':
        case 'B':
            if (_instancia->camara.getMovimientoActivo())
                _instancia->camara.desplazarAdelante(-0.2);
            break;
        case '+':
            _instancia->camara.zoom(10.0);
            break;
        case '-':
            _instancia->camara.zoom(-10.0);
            break;
        case 'p':
        case 'P':
            if (_instancia->camara.getTipo() == IGV_PARALELA)
                _instancia->camara.set(IGV_PERSPECTIVA);
            else _instancia->camara.set(IGV_PARALELA);
            break;
        case '4':
            _instancia->cambiaModoMultiViewPort();
            break;
        case 'h':
        case 'H':
            _instancia->escena.cambiarModoSombreado();
            _instancia->escena.cambiarUsoNormales();
            break;
        case 'r':
        case 'R':
            _instancia->escena.resetearPoseLampara();
            break;
        case 'm':
        case 'M':
            _instancia->cambiarModoInteraccion();
            break;
        case 'a':
        case 'A':
            _instancia->animacionModeloActiva = !_instancia->animacionModeloActiva;
            if (_instancia->animacionModeloActiva) {
                printf("Animacion automática del modelo ACTIVADA\n");
            } else {
                printf("Animacion automática del modelo DESACTIVADA\n");
            }
            break;
        case 'g':
        case 'G':
            _instancia->orbitaAutomaticaActiva = !_instancia->orbitaAutomaticaActiva;
            if (_instancia->orbitaAutomaticaActiva) {
                printf("Orbitado automático de la cámara ACTIVADO\n");
            } else {
                printf("Orbitado automático de la cámara DESACTIVADO\n");
            }
            break;
        case '1':
            _instancia->escena.setParteSeleccionada(0);
            printf("Base seleccionada - Usa las flechas para rotar\n");
            break;
        case '2':
            _instancia->escena.setParteSeleccionada(1);
            printf("Brazo 1 seleccionado - Usa las flechas para rotar\n");
            break;
        case '3':
            _instancia->escena.setParteSeleccionada(2);
            printf("Brazo 2 seleccionado - Izq/Der giran lateralmente, Arr/Ab inclinan\n");
            break;
        case '4':
            _instancia->escena.setParteSeleccionada(3);
            printf("Pantalla seleccionada - Izq/Der giran la pantalla, Arr/Ab inclinan\n");
            break;
        case 27:
            exit(1);
    }
    glutPostRedisplay();
}

void igvInterfaz::specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (_instancia->escena.getParteSeleccionada() == -1) {
                _instancia->camara.orbita(-5.0);
            } else {
                _instancia->aplicarIncrementoSeleccionadoHorizontal(-5.0f);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (_instancia->escena.getParteSeleccionada() == -1) {
                _instancia->camara.orbita(5.0);
            } else {
                _instancia->aplicarIncrementoSeleccionadoHorizontal(5.0f);
            }
            break;
        case GLUT_KEY_UP:
            if (_instancia->escena.getParteSeleccionada() == -1) {
                _instancia->camara.cabeceo(5.0);
            } else {
                _instancia->aplicarIncrementoSeleccionadoVertical(5.0f);
            }
            break;
        case GLUT_KEY_DOWN:
            if (_instancia->escena.getParteSeleccionada() == -1) {
                _instancia->camara.cabeceo(-5.0);
            } else {
                _instancia->aplicarIncrementoSeleccionadoVertical(-5.0f);
            }
            break;
    }

    glutPostRedisplay();
}

void igvInterfaz::reshapeFunc(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    _instancia->set_ancho_ventana(w);
    _instancia->set_alto_ventana(h);
    _instancia->camara.aplicar();
}

void igvInterfaz::mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!_instancia->modoSeleccion) {
            // Activa el modo de selección al primer clic para permitir arrastrar con el ratón
            _instancia->cambiarModoInteraccion();
        }

        if (!_instancia->modoSeleccion) {
            return; // No se pudo activar el modo selección
        }

        _instancia->escena.seleccionarParte(x, y, _instancia->alto_ventana);
        int parte = _instancia->escena.getParteSeleccionada();
        switch(parte) {
            case 0:
                printf("Base seleccionada - Arrastra o usa las flechas para rotar\n");
                _instancia->arrastrando = true;
                break;
            case 1:
                printf("Brazo 1 seleccionado - Arrastra o usa las flechas para rotar\n");
                _instancia->arrastrando = true;
                break;
            case 2:
                printf("Brazo 2 seleccionado - Arrastra para girar/inclinar o usa las flechas\n");
                _instancia->arrastrando = true;
                break;
            case 3:
                printf("Pantalla seleccionada - Arrastra para girar/inclinar o usa las flechas\n");
                _instancia->arrastrando = true;
                break;
            default:
                printf("No se selecciono ninguna parte - Haz clic en la lámpara\n");
                _instancia->arrastrando = false;
                break;
        }

        _instancia->ultimoX = x;
        _instancia->ultimoY = y;

        glutPostRedisplay();
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        _instancia->arrastrando = false;
    }
}

void igvInterfaz::motionFunc(int x, int y) {
    if (!_instancia->modoSeleccion || !_instancia->arrastrando) return;

    int dx = x - _instancia->ultimoX;
    int dy = y - _instancia->ultimoY;

    _instancia->aplicarMovimientoRaton(dx, dy);

    _instancia->ultimoX = x;
    _instancia->ultimoY = y;

    glutPostRedisplay();
}

void igvInterfaz::displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_instancia->modoMultiViewport) {
        for (int i = 0; i < 4; i++) {
            _instancia->camara.aplicarViewport(i,
                                               _instancia->ancho_ventana,
                                               _instancia->alto_ventana);

            _instancia->escena.visualizar();
        }
    } else {
        glViewport(0, 0, _instancia->ancho_ventana, _instancia->alto_ventana);
        _instancia->camara.aplicar();
        _instancia->escena.visualizar();
    }

    glutSwapBuffers();
}

void igvInterfaz::timerFunc(int value) {
    if (_instancia->animacionModeloActiva) {
        _instancia->escena.rotarBaseLampara(1.0f);
    }

    if (_instancia->orbitaAutomaticaActiva) {
        _instancia->camara.orbita(0.5);
    }

    if (_instancia->animacionModeloActiva || _instancia->orbitaAutomaticaActiva) {
        glutPostRedisplay();
    }

    glutTimerFunc(_instancia->timerAnimacion, timerFunc, 0);
}

void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutTimerFunc(16, timerFunc, 0);
}

int igvInterfaz::get_ancho_ventana() {
    return ancho_ventana;
}

int igvInterfaz::get_alto_ventana() {
    return alto_ventana;
}

void igvInterfaz::set_ancho_ventana(int _ancho_ventana) {
    ancho_ventana = _ancho_ventana;
}

void igvInterfaz::set_alto_ventana(int _alto_ventana) {
    alto_ventana = _alto_ventana;
}