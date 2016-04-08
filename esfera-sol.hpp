#ifndef ESFERA_SOL_HPP
#define ESFERA_SOL_HPP

#include "materiales.hpp"
#include "objetos-4.hpp"
#include "file_ply_stl.hpp"
#include "objetos-3.h" 
#include "math.h"
#include "iostream"

//**********************************************************************
// clase para dibujar satelite luna

class EsferaSol : public _sup_par_triangles_object3D
{
   private:
   float rotacionvar;
   float orbitavar;
   float orbitatierra;
   bool eventorotacion;

   
   public:
   EsferaSol() ;
   void  draw_solid_material_gouroud() ; // prac.4
   void  rotacion();
   void  orbita();
   void activarrotacion();
   void desactivarrotacion();
} ;




#endif
