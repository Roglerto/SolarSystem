#ifndef TEXTURA_HPP
#define TEXTURA_HPP

#include <string>
#include <vector>
#include <GL/gl.h>

#include "vertex.h"
#include "jpg_imagen.hpp"
#include "materiales.hpp"
#include "luz.hpp"

typedef _vertex3<float> vectorRGB ;

//**********************************************************************
// posibles modos de generacion de coords. de textura

typedef enum 
{  mgct_desactivada,  
   mgct_coords_objeto, 
   mgct_coords_ojo 
} 
   ModoGenCT ;
   
//**********************************************************************
// extrae un puntero (GLfloat *) a un vectorRGB con tres valores reales

inline const GLfloat * dir( const vectorRGB & rgb )
{  return (const GLfloat *) &(rgb.r) ;
}

//**********************************************************************
// Estructura ColoresMat
// ---------------------
// estructura con las reflectividades o colores de un material (+exp.brillo)

struct ColoresMat
{
   _vertex3f
      emision,    // color de la emisividad del material
      ambiente,   // reflectividad para la componente ambiental (M_A)
      difusa,     // reflectividad para la componente difusa (M_D)
      especular ; // reflectividad para la componente especular (M_S)
   GLfloat
      exp_brillo ; // exponente de brillo especular
} ;

//**********************************************************************
// Clase Textura:
// ---------------
// clase que encapsula una imagen de textura de OpenGL, así como los
// parámetros relativos a como se aplica  a las primitivas que se dibujen
// mientras está activa

class Textura
{
   public:
   
   // carga una imagen de textura en la memoria de vídeo, e
   // inicializa los atributos de la textura a valores por defecto.
   Textura( const std::string & nombreArchivoJPG ) ;
   
   // libera la memoria dinámica usada por la textura, si hay alguna
   ~Textura() ; 
   
   // modifica el estado de OpenGL de forma que, a partir de la llamada,
   // se usará la textura en el cálculo del color de los pixels en los 
   // que se proyectan las primitivas que se dibujen
   void activar() ;
   
   protected: //----------------------------------------------------------
   
   GLuint 
      ident_textura ;// 'nombre' o identif. de textura para OpenGL
   jpg::Imagen *
      imagen ;       // objeto con los bytes de la imagen de textura
   ModoGenCT
      modo_gen_ct ;  // modo de generacion de coordenadas de textura
                     // (desactivadas si modo_gen_ct == mgct_desactivada)
   GLfloat
      coefs_s[4] ,   // si 'modo_gen_ct != desactivadas', coeficientes para la coord. S
      coefs_t[4] ;   // idem para coordenada T
} ;

#endif
