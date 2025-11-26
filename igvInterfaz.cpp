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
}


void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop();
}

void igvInterfaz::cambiarModoInteraccion() {
    modoSeleccion = !modoSeleccion;

    if (modoSeleccion) {
        printf("Modo selección activado: Haz clic en una parte de la lámpara para seleccionarla\n");
        printf("Luego usa las teclas Q/A (brazo1), W/S (brazo2), Z/X (pantalla), 1/2 (base)\n");
    } else {
        printf("Modo teclado activado: Las teclas afectan directamente a todas las partes\n");
        _instancia->escena.activarModoSeleccion(false);
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
        case 'g':
        case 'G':
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
        case 't':
        case 'T':
            _instancia->animacionActiva = !_instancia->animacionActiva;
            if (_instancia->animacionActiva) {
                printf("Animacion automática ACTIVADA\n");
                glutTimerFunc(_instancia->timerAnimacion, timerFunc, 0);
            } else {
                printf("Animacion automática DESACTIVADA\n");
            }
            break;
        case '1':
            if (_instancia->modoSeleccion) {
                if (_instancia->escena.getParteSeleccionada() == 0) {
                    _instancia->escena.rotarBaseLampara(-5.0f);
                }
            } else {
                _instancia->escena.rotarBaseLampara(-5.0f);
            }
            break;
        case '2':
            if (_instancia->modoSeleccion) {
                if (_instancia->escena.getParteSeleccionada() == 0) {
                    _instancia->escena.rotarBaseLampara(5.0f);
                }
            } else {
                _instancia->escena.rotarBaseLampara(5.0f);
            }
            break;
        case 'q':
        case 'Q':
            if (_instancia->modoSeleccion) {
                if (_instancia->escena.getParteSeleccionada() == 1) {
                    _instancia->escena.rotarBrazo1Lampara(5.0f);
                }
            } else {
                _instancia->escena.rotarBrazo1Lampara(5.0f);
            }
            break;
        case 'a':
        case 'A':
            if (_instancia->modoSeleccion) {
                if (_instancia->escena.getParteSeleccionada() == 1) {
                    _instancia->escena.rotarBrazo1Lampara(-5.0f);
                }
            } else {
                _instancia->escena.rotarBrazo1Lampara(-5.0f);
            }
            break;
        case 'w':
        case 'W':
            if (_instancia->modoSeleccion) {
                if (_instancia->escena.getParteSeleccionada() == 2) {
                    _instancia->escena.rotarBrazo2Lampara(5.0f);
                }
            } else {
                _instancia->escena.rotarBrazo2Lampara(5.0f);
            }
            break;
        case 's':
        case 'S':
            if (_instancia->modoSeleccion) {
                if (_instancia->escena.getParteSeleccionada() == 2) {
                    _instancia->escena.rotarBrazo2Lampara(-5.0f);
                }
            } else {
                _instancia->escena.rotarBrazo2Lampara(-5.0f);
            }
            break;
        case 'z':
        case 'Z':
            if (_instancia->modoSeleccion) {
                if (_instancia->escena.getParteSeleccionada() == 3) {
                    _instancia->escena.rotarPantallaLampara(5.0f);
                }
            } else {
                _instancia->escena.rotarPantallaLampara(5.0f);
            }
            break;
        case 'x':
        case 'X':
            if (_instancia->modoSeleccion) {
                if (_instancia->escena.getParteSeleccionada() == 3) {
                    _instancia->escena.rotarPantallaLampara(-5.0f);
                }
            } else {
                _instancia->escena.rotarPantallaLampara(-5.0f);
            }
            break;
        case 27:
            exit(1);
    }
    glutPostRedisplay();
}

void igvInterfaz::specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            _instancia->camara.orbita(-5.0);
            break;
        case GLUT_KEY_RIGHT:
            _instancia->camara.orbita(5.0);
            break;
        case GLUT_KEY_UP:
            _instancia->camara.cabeceo(5.0);
            break;
        case GLUT_KEY_DOWN:
            _instancia->camara.cabeceo(-5.0);
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
    if (_instancia->modoSeleccion && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _instancia->escena.seleccionarParte(x, y, _instancia->alto_ventana);
        int parte = _instancia->escena.getParteSeleccionada();
        switch(parte) {
            case 0:
                printf("Base seleccionada - Usa teclas 1/2 para rotar\n");
                break;
            case 1:
                printf("Brazo 1 seleccionado - Usa teclas Q/A para rotar\n");
                break;
            case 2:
                printf("Brazo 2 seleccionado - Usa teclas W/S para rotar\n");
                break;
            case 3:
                printf("Pantalla seleccionada - Usa teclas Z/X para rotar\n");
                break;
            default:
                printf("No se selecciono ninguna parte - Haz clic en la lámpara\n");
                break;
        }

        glutPostRedisplay();
    }
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
    if (_instancia->animacionActiva) {
        _instancia->escena.rotarBaseLampara(1.0f);

        _instancia->camara.orbita(0.5);

        glutPostRedisplay();
        glutTimerFunc(_instancia->timerAnimacion, timerFunc, 0);
    }
}

void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutMouseFunc(mouseFunc);
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