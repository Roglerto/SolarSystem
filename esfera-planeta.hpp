#ifndef ESFERA_PLANETA_HPP
#define ESFERA_PLANETA_HPP

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

class EsferaPlaneta : public _sup_par_triangles_object3D
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
   
   float velocidad;
   int indice;
   
   
   public:
   EsferaPlaneta(float vel,int ind,string & nombreArchivoJPG,float var1,float var2,float var3,float var4,float var5,float var6,float var7,float var8,float var9,float var10,float var11,float var12,float var13,float var14,float var15) ;
   void  draw_solid_material_gouroud() ; // prac.4
   void  rotacion();
   void  orbita();
   void  dibujaorbita();
   void activarrotacion();
   void desactivarrotacion();

} ;


#endif
