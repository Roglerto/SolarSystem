#ifndef LUZ_HPP
#define LUZ_HPP

#include <string>
#include <vector>
#include <GL/gl.h>

#include "vertex.h"
#include "jpg_imagen.hpp"
#include "materiales.hpp"
#include "textura.hpp"

typedef _vertex3<float> vectorRGB ;

//**********************************************************************
// Clase FuenteLuz
// ---------------
// clase que contiene los atributo de una fuente de luz OpenGL

class FuenteLuz
{
   public:
   
   // inicializa la fuente de luz, indicando el indice de la misma, que
   // debe ser el valor de GL_LIGHT0 o GL_LIGHT1 o GL_LIGHT2 etc...
   //
   // p_ind_fuente == GL_LIGHT0, GL_LIGHT1, etc...
   // p_longi_ini == valor inicial del ángulo horizontal en grados
   // p_lati_ini  == idem del ángulo vértical
   // p_color     == color de la fuente de luz (amb, dif y spec )
   FuenteLuz( GLenum p_ind_fuente, GLfloat p_longi_ini, GLfloat p_lati_ini, const vectorRGB & p_color ) ; 
   
   // cambia el estado de OpenGL de forma que a partir de la llamada
   // se usará esta fuente de luz en los calculos del MIL
   // (en cada momento puede haber varias fuentes activadas)
   void activar() ;
   
   // cambia los atributos de la instancia en respuesta a una pulsación
   // de una tecla 'especial' (según la terminología de 'glut')
   bool gestionarEventoTeclaEspecial( int key ) ; 

   protected:
   
   GLenum
      ind_fuente ;// indice de la fuente de luz 
                  // (entre GL_LIGHT0 y GL_LIGHT0+máx.núm.fuentes)
   GLfloat 
      longi,      // longitud actual de la fuente direccional (entre 0 y 360)
      lati,       // latitud actual de la fuente direccional (entre -90 y 90)
      longi_ini,  // valor inicial de 'longi'
      lati_ini ;  // valor inicial de 'lati'
   _vertex3f
      col_ambiente,  // color de la fuente para la componente ambiental
      col_difuso,    // color de la fuente para la componente difusa
      col_especular; // color de la fuente para la componente especular
   
} ;

#endif
