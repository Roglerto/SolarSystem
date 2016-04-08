
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>

#include "jpg_imagen.hpp"

#include "materiales.hpp"
#include "objetos-4.hpp"
#include "objeto-ply.hpp"

using namespace std;

//**********************************************************************
//
// Clase TexObjetoPly
// ------------------
// clase para la textura del objeto ply
//
//**********************************************************************

class TexObjetoPly : public Textura 
{  public: 
   TexObjetoPly(  const std::string & p_nom_fich_jpg, 
                   const float p_coefs_s[4], const float p_coefs_t[4] ) ; 
} ;

//----------------------------------------------------------------------

TexObjetoPly::TexObjetoPly(  const std::string & p_nom_fich_jpg, 
                   const float p_coefs_s[4], const float p_coefs_t[4] )

:  Textura(p_nom_fich_jpg)

   // 'marmol.jpg' : http://www.shareaec.com/images/large/13621.jpg
{
   // establecer modo de generación de coordenadas de textura
   // (coordenadas de objeto)
   
   assert( p_coefs_s != NULL && p_coefs_t != NULL ) ;
   
   modo_gen_ct = mgct_coords_objeto ;
   
   for( unsigned i = 0 ; i < 4 ; i++ )
   {  coefs_s[i] = p_coefs_s[i] ;
      coefs_t[i] = p_coefs_t[i] ;
   }
}

//**********************************************************************
//
// Clase MatObjetoPly
// ------------------
// clase para el material del objeto ply
//
//**********************************************************************

const float
   refl_amb_ini = 0.1 ,
   refl_dif_ini = 0.7 ,
   refl_esp_ini = 1.0 ,
   exp_brillo_ini   = 80.0 ;
   
//----------------------------------------------------------------------   

class MatObjetoPly: public Material 
{  
   public: 
   MatObjetoPly( const std::string & p_nom_fich_jpg, 
                   const float coefs_s[4], const float coefs_t[4] ) ; 
} ;



//----------------------------------------------------------------------

MatObjetoPly::MatObjetoPly( const std::string & p_nom_fich_jpg,  
                   const float coefs_s[4], const float coefs_t[4] )
{
   coloresCero() ; // 
   
   color = vectorRGB(1.0,1.0,1.0);
   iluminacion    = true ; 
   tex            = new TexObjetoPly(p_nom_fich_jpg,coefs_s,coefs_t) ; 
   
   tra.ambiente  = vectorRGB( 0.05,0.05,0.05 ) ;
   tra.difusa    = vectorRGB( 0.10,0.10,0.10 ) ;
   tra.especular = vectorRGB( 0.0,0.0,0.0 ) ;
   tra.exp_brillo = 50 ;
}

//**********************************************************************
// clase ObjetoPLY
//----------------------------------------------------------------------

ObjetoPLY::ObjetoPLY(  const std::string & p_nom_fich_ply , const std::string & p_nom_fich_jpg )

:  _ply_triangles_object3D( p_nom_fich_ply )

{
  if(!Vertices_normals_computed)
    compute_vertices_normals();
   
   for(int i=0;i<Vertices.size();i++){
    Nuevos_Vertices.push_back(Vertices[i].x);
    Nuevos_Vertices.push_back(Vertices[i].y);
    Nuevos_Vertices.push_back(Vertices[i].z);
}

for( int w=0;w<Faces_vertices.size();w++){
    Nuevos_Faces_vertices.push_back(Faces_vertices[w].x);
    Nuevos_Faces_vertices.push_back(Faces_vertices[w].y);
    Nuevos_Faces_vertices.push_back(Faces_vertices[w].z);
}

for(int ko=0;ko<Vertices_normals.size();ko++){
    Nuevos_Vertices_normals.push_back(Vertices_normals[ko].x);
    Nuevos_Vertices_normals.push_back(Vertices_normals[ko].y);
    Nuevos_Vertices_normals.push_back(Vertices_normals[ko].z);
}

for( int lol=0;lol<Vertices_tex_coords.size();lol++){
    Nuevos_Vertices_tex_coords.push_back(Vertices_tex_coords[lol].x);
    Nuevos_Vertices_tex_coords.push_back(Vertices_tex_coords[lol].y);
}
	rotacionvar=0;
   orbitavar=90;
   eventorotacion=false;
   camara=false;

   // calcular parámetros de la caja englobante
   _vertex3f centro, pmin, pmax ;
   float max_dim = 10.0f ;
   compute_bounding_box( centro, pmin, pmax, max_dim ) ;
   cout<< "máxima dimensión del objeto ply == " << max_dim << endl ;
   
   // situar el objeto en el centro y con ancho unidad
   const float fesc = 1.0/max_dim ;
   for( unsigned long i = 0 ; i < Vertices.size() ; i++ )
   {
      Vertices[i] -= centro ;
      Vertices[i] *= fesc ;
   }
   
   // ajustar los parámetros de la caja englobante
   pmin -= centro ;
   pmax -= centro ;
   pmin *= fesc ;
   pmax *= fesc ;
   
   // calcular coeficientes de generacion automática de texturas
   const float
      fsx = 1.0f/(pmax.x-pmin.x) ,
      fty = 1.0f/(pmax.y-pmin.y) ;
   const float 
      coefs_s[4] = {fsx,0.0,0.0,-fsx*pmin.x}  ,
      coefs_t[4] = {0.0,fty,0.0,-fty*pmin.y}  ;
   
   // crear material
   material = new MatObjetoPly(p_nom_fich_jpg,coefs_s,coefs_t) ;
   
   // incializar reflectividades del material
   refl_amb   = refl_amb_ini ;
   refl_dif   = refl_dif_ini ;
   refl_esp   = refl_esp_ini ;
   exp_brillo = exp_brillo_ini ;
   actualizar_refls() ;
   
   
}

//----------------------------------------------------------------------

void ObjetoPLY::compute_bounding_box( _vertex3f & centro, 
                    _vertex3f & pmin, _vertex3f & pmax, float max_dim  )
{
   assert( Vertices.size() >  0.0 ) ;
   
   // calcular centro y máxima dimension de la caja englobante
   
   pmin = Vertices[0] ;
   pmax = Vertices[0] ;
      
   for( unsigned long i = 1 ; i < Vertices.size() ; i++ )
   {
      const _vertex3f & v = Vertices[i] ;
      
      if ( v.x < pmin.x ) pmin.x = v.x ;
      if ( v.y < pmin.y ) pmin.y = v.y ;
      if ( v.z < pmin.z ) pmin.z = v.z ;
      
      if ( pmax.x < v.x ) pmax.x = v.x ;
      if ( pmax.y < v.y ) pmax.y = v.y ;
      if ( pmax.z < v.z ) pmax.z = v.z ;
   }
   
   assert( 0.0 < pmax.x - pmin.x ||  0.0 < pmax.y - pmin.y || 0.0 < pmax.z - pmin.z );
   
   centro = _vertex3f( 0.5*(pmin.x+pmax.x), 0.5*(pmin.y+pmax.y), 0.5*(pmin.z+pmax.z) );
   
   max_dim = pmax.x - pmin.x ;
   if ( max_dim < pmax.y-pmin.y ) max_dim = pmax.y - pmin.y ; 
   if ( max_dim < pmax.z-pmin.z ) max_dim = pmax.z - pmin.z ;
}

//----------------------------------------------------------------------

void ObjetoPLY::actualizar_refls()
{
   assert( material != NULL );
   
   material->del.ambiente  = vectorRGB( refl_amb,refl_amb,refl_amb );
   material->del.difusa    = vectorRGB( refl_dif,refl_dif,refl_dif ) ;
   material->del.especular = vectorRGB( refl_esp,refl_esp,refl_esp ) ;
   material->del.exp_brillo = exp_brillo ;
}

//----------------------------------------------------------------------

const float incr = 0.01f ;

//----------------------------------------------------------------------

inline void incre( float & v )
{
   v += incr ;
   if ( v > 1.0 ) v = 1.0 ;
}

//----------------------------------------------------------------------

inline void decre( float & v )
{
   v -= incr ;
   if ( v < 0.0 ) v = 0.0 ;
}

//----------------------------------------------------------------------

bool ObjetoPLY::gestionarEventoTeclaEspecial( int key )
{
   using namespace std ;
   bool actualizar = true ;
   
   assert( material != NULL ) ;
   
   switch( key )
   {
      case GLUT_KEY_UP        : incre( refl_amb ) ; break ;
      case GLUT_KEY_DOWN      : decre( refl_amb ) ; break ;
      case GLUT_KEY_RIGHT     : incre( refl_dif ) ; break ;
      case GLUT_KEY_LEFT      : decre( refl_dif ) ; break ;
      case GLUT_KEY_PAGE_UP   : incre( refl_esp ) ; break ;
      case GLUT_KEY_PAGE_DOWN : decre( refl_esp ) ; break ;
      case GLUT_KEY_INSERT    :
         exp_brillo *= 1.01 ;
         if ( exp_brillo > 128.0 )
            exp_brillo = 128.0 ;
         break ;
      case GLUT_KEY_END       :
         exp_brillo /= 1.01;
         break ;
      case GLUT_KEY_HOME      :
         refl_amb   = refl_amb_ini ;
         refl_dif   = refl_dif_ini ;
         refl_esp   = refl_esp_ini ;
         exp_brillo = exp_brillo_ini ;
         break ;
      default:
         actualizar = false ;
         cout << "tecla especial no usada en este modo" << endl << flush ;
         break ;
   }
   if ( actualizar )
   {
      actualizar_refls() ;
      cout << "material del objeto ply: amb == " << refl_amb 
         << ", dif == " << refl_dif 
         << ", esp == " << refl_esp 
         << ", exp == " << exp_brillo
         << endl << flush ;
   }
   return actualizar ;
}

void ObjetoPLY::draw_solid_material_gouroud()
{
int Vertex_1,Vertex_2,Vertex_3,j=0;



  



glShadeModel(GL_SMOOTH);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
material->activar();




glEnableClientState( GL_VERTEX_ARRAY );
glVertexPointer(3, GL_FLOAT, 0, &Vertices[0] );

glEnableClientState( GL_INDEX_ARRAY );
glIndexPointer( GL_UNSIGNED_INT, 0,&Faces_vertices[0] );

glEnableClientState( GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT,0,&Vertices_normals[0]);

glEnableClientState(GL_TEXTURE_COORD_ARRAY);
glTexCoordPointer(2, GL_FLOAT,  0, &Vertices_tex_coords[0]);

glInitNames();


glPushMatrix();

if(camara)
	glScaled(0.1,0.1,0.1);
else{
	glScaled(0.01,0.01,0.01);
	glTranslatef(	-500, -30, 0);
	
}
//glRotatef(90,1,0,0);
glRotatef(orbitavar,0,1,0);

glTranslatef(	-40, -30, 0);
glRotatef(-45,0,1,0);
if(eventorotacion){
  glRotatef(rotacionvar,0,1,0);
}

glPushName(69);

glDrawElements( GL_TRIANGLES, Faces_vertices.size()*3, GL_UNSIGNED_INT, &Faces_vertices[0] );


glPopName();
glPopMatrix();


}

void  ObjetoPLY::rotacion(){
  
  rotacionvar=rotacionvar+1;
 }
 
void  ObjetoPLY::orbita(){
  
  orbitavar=orbitavar+1;
 }

void ObjetoPLY::activarrotacion(){

    eventorotacion=true;
}

void ObjetoPLY::desactivarrotacion(){

    eventorotacion=false;

}

void ObjetoPLY::ampliar_cam(){

camara=true;

}

void ObjetoPLY::disminuir_cam(){

camara=false;

}
    
