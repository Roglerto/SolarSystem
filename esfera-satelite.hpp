#ifndef ESFERA_SATELITE_HPP
#define ESFERA_SATELITE_HPP

#include "materiales.hpp"
#include "objetos-4.hpp"
#include "file_ply_stl.hpp"
#include "objetos-3.h" 
#include "math.h"
#include "iostream"

//**********************************************************************
// clase para dibujar satelite 

class EsferaSatelite : public _sup_par_triangles_object3D
{
   private:
   
   float orbitavar;  //0.5
   float orbitavarx;
   float orbitavary;
   float orbitavarz;
   
   float orbitaplaneta;
   float orbitaplanetax;
   float orbitaplanetay;
   float orbitaplanetaz;
   
   bool eventorotacion;
   
   float tamx;
   float tamy;
   float tamz;
   
   float disx;
   float disy;
   float disz;
   
   float displanesolx ;
   float displanesoly ;
   float displanesolz ;
   
   float  rotacionprovar;
   float rotacionprovarx;
   float rotacionprovary;
   float rotacionprovarz;

   
   public:
   EsferaSatelite(string & nombreArchivoJPG,float var1,float var2,float var3,float var4,float var5,float var6,float var7,float var8,float var9,float var10,float var11,float var12,float var13,float var14,float var15,float var16,float var17,float var18,float var19,float var20,float var21) ;
   void  draw_solid_material_gouroud() ; // prac.4
   void  rotacion();
   void  orbita();
   void activarrotacion();
   void desactivarrotacion();
} ;




#endif
