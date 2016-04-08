#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <ctype.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>

#include "aux-p4.hpp"
#include "objetos-3.h"

#include "esfera-planeta.hpp"
#include "esfera-fondo.hpp"
#include "esfera-sol.hpp"
#include "esfera-satelite.hpp"
#include "luz.hpp"
#include "objeto-ply.hpp"
#include "textura.hpp"


class Camara
{

private:

GLfloat angle ,camaragiro,camaratrasnalte,camaragiro2;
 GLfloat
   longi_cam_ini ,  // valor inicial para 'longi_cam' (ver abajo)
   lati_cam_ini   , // valor inicial para 'lati_cam' (ver abajo)
   dis_cam_ini   ;  // valor inicial para la distancia de la camara al origen
   
  
   
GLfloat
   longi_cam , // angulo de longitud actual de la cámara, en grados
   lati_cam   , // angulo de latitud actual de la cámara, en grados
   dis_cam   ;  // distancia de la camara al origen
   
GLfloat   longi_cam_luna,
      lati_cam_luna   ,seguiluna,borrar;
      
GLfloat   longi_cam_nave ,
      lati_cam_nave   ;
   
GLfloat
   ang_ry_obj  , // ángulo actual de rotacion en Y+ del objeto, en grados
   ang_rx_obj  , // ángulo actual de rotacion en X- del objeto, en grados
   ang_rz_obj  , // ángulo actual de rotacion en Z+ del objeto, en grados
   f_esc_obj   ; // factor de escala del objeto (en tanto por uno)


int
  altoActual  , 
  anchoActual  ;
  
public:
 Camara();
void MatrizVista();


void MatrizVistaLuna();

void MatrizVistaNave();
void MatrizProyeccion();


bool GestionEventoTeclaNormalCamara( unsigned char key ) ;
bool GestionEventoTeclaEspecialCamara( int key );
bool GestionEventoTeclaEspecialTipoObjeto( int key );
bool GestionEventoTeclaNormalObjeto( unsigned char key ) ;
bool GestionEventoTeclaEspecialObjeto( int key ) ;

void movcam();
void rota();
void  escala();
void FuncRedimensionar( int nuevoAncho, int nuevoAlto );

void ancho ( int) ;
void alto(int );
int getancho ( ) ;
int getalto ( ) ;
};

#endif

