#ifndef MATERIALES_HPP
#define MATERIALES_HPP

#include <string>
#include <vector>
#include <GL/gl.h>

#include "vertex.h"
#include "jpg_imagen.hpp"
#include "materiales.hpp"
#include "luz.hpp"
#include "textura.hpp"

typedef _vertex3<float> vectorRGB ;

class Material ;
class Textura  ;
   


//**********************************************************************
// Clase Material
// ---------------
// clase que encapsula los atributos de un material, incluyendo la
// textura del mismo. 

class Material
{
   public:
   
   // crea un material con un color plano blanco sin textura 
   // ni iluminación
   Material() ;     
   
   // crea un material con una textura asociada, y con la iluminación activada.
   // 'nombreArchivoJPG' nombre del archivo que contiene la imagen de text.
   Material( const std::string & nombreArchivoJPG ) ;
   
   // libera la memoria dinámica ocupada por el material
   ~Material() ;    
   
   // cambia el estado de OpenGL de forma que a partir de la llamada
   // se usaran los atributos de este material como valores de los parámetros
   // en la evaluación del MIL durante la visualización de primitivas
   void activar() ; 
   void activarsol();
   void activarfondo();
  
    //--------------------------------------------------------
   
   void coloresCero();// pone todos los colores y reflectividades a cero
   
   bool 
      iluminacion ;  // true si el material requiere activar iluminación, 
                     // false si requiere desactivarla
   Textura *
      tex ;          // si !=NULL, el material tiene esta textura
   GLuint 
      ident_textura ;// identificador de textura, si tiene_textura=true
   _vertex3f
      color ;        // color del material cuando iluminacion=false 
   ColoresMat
      del,           // reflectividades de caras delanteras, si iluminacion= true
      tra ;          // reflectividades de caras traseras, si iluminacion=true
} ;



#endif
