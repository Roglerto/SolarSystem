#ifndef ESFERA_FONDO_HPP
#define ESFERA_FONDO_HPP

#include "materiales.hpp"
#include "objetos-4.hpp"
#include "file_ply_stl.hpp"
#include "objetos-3.h" 
#include "math.h"
#include "iostream"
#include <string>

#define PI 3.14159265358979323846

using namespace std;


//**********************************************************************
// clase para dibujar una esfera con un mapamundi

class EsferaFondo : public _sup_par_triangles_object3D
{
   private:
   
   float tamx;
   float tamy;
   float tamz;
   
   float orbitaplaneta;
   float orbitaplanetax;
   float orbitaplanetay;
   float orbitaplanetaz;
   
   float  rotacionprovar;
   float rotacionprovarx;
   float rotacionprovary;
   float rotacionprovarz;
   
   float displanesolx ;
   float displanesoly ;
   float displanesolz ;
   
   float radio;
   
   bool eventorotacion;
   
   
   public:
   EsferaFondo(string & nombreArchivoJPG,float var1,float var2,float var3) ;
   void  draw_solid_material_gouroud() ; // prac.4
   void  rotacion();
   void  orbita();
   void  dibujaorbita();
   void activarrotacion();
   void desactivarrotacion();

} ;


#endif
