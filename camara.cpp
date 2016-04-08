#include "camara.hpp"


Camara::Camara(){

GLfloat angle =0.f,camaragiro=1,camaratrasnalte=2,camaragiro2=1;
 GLfloat
   longi_cam_ini =  45.0,  // valor inicial para 'longi_cam' (ver abajo)
   lati_cam_ini  =  30.0 , // valor inicial para 'lati_cam' (ver abajo)
   dis_cam_ini   =  1.0 ;  // valor inicial para la distancia de la camara al origen
   
  GLfloat  movlon=longi_cam_ini, movlati=-1;
   
GLfloat
   longi_cam =  longi_cam_ini, // angulo de longitud actual de la cámara, en grados
   lati_cam  =  lati_cam_ini , // angulo de latitud actual de la cámara, en grados
   dis_cam   =  dis_cam_ini ;  // distancia de la camara al origen
   
GLfloat   longi_cam_luna=100 ,
      lati_cam_luna  = 1 ,seguiluna=10,borrar=0.5;
      
GLfloat   longi_cam_nave=6 ,
      lati_cam_nave  = 0.2 ;
   
GLfloat
   ang_ry_obj = 0.0 , // ángulo actual de rotacion en Y+ del objeto, en grados
   ang_rx_obj = 0.0 , // ángulo actual de rotacion en X- del objeto, en grados
   ang_rz_obj = 0.0 , // ángulo actual de rotacion en Z+ del objeto, en grados
   f_esc_obj  = 1.0 ; // factor de escala del objeto (en tanto por uno)

// tamaño de la ventana

int
  altoActual  = 1024, 
  anchoActual = 1024 ;

}

void Camara::movcam(){
  camaragiro--;
  camaragiro2--;
  
  }

void Camara::ancho ( int n) {
anchoActual=n;

}

int Camara::getancho ( ) {
return anchoActual;

}

int Camara::getalto ( ) {
return altoActual;

}

void Camara::alto(int anchoActual){
altoActual=anchoActual;

}


void Camara::rota(){
	glRotated( ang_rz_obj,  0.0, 0.0, 1.0 );  // (3) rot Z+
      glRotated( ang_rx_obj, -1.0, 0.0, 0.0 ) ; // (2) rot X-
      glRotated( ang_ry_obj,  0.0, 1.0, 0.0 );  // (1) rot Y+
}
//**********************************************************************
// fijar la matriz de vista, deja activo el modo de matriz modelview

void Camara::MatrizVista()
{
   const GLfloat
      longi_cam_rad = longi_cam*2.0f*M_PI / 360.0f ,
      lati_cam_rad  = lati_cam *2.0f*M_PI / 360.0f ;
      
   const GLfloat
      eyex = dis_cam*( sin(longi_cam_rad)*cos(lati_cam_rad) ),
      eyey = dis_cam*( sin(lati_cam_rad) ),
      eyez = dis_cam*( cos(longi_cam_rad)*cos(lati_cam_rad) );
      
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity() ;
   gluLookAt
   (  eyex, eyey, eyez,  // posición de la cámara
      0.0f, 0.0f, 0.0f,  // punto de atencion (== origen)
      0.0f, 1.0f, 0.0f   // vector 'up' (== eje Y+)
   ) ;
}
void Camara::MatrizVistaLuna()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity() ;




	//
	gluPerspective(45, (float)anchoActual/(float)altoActual , 0.10, 100.0);
	
	
      
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;



//glTranslatef(0,-0,-3);
//glRotatef(camaragiro2,0,1,0);



//



	gluLookAt
	(
	2, 0.2, 0,  // posición de la cámara  10, 0.5, -2,
	0, 0, -1,  // punto de atencion (== origen)   2, 0, 0, 
	0, 1, 0   // vector 'up' (== eje Y+)
	);
	
		//glRotatef(camaragiro,0,1,0);
		
		glRotatef(camaragiro2,0,1,0);	
		
glTranslatef(-6,0,0);

		glRotatef(camaragiro,0,1,0);	


	//glTranslatef(0,0,0);
	



	
			//
	//

	

   
   
}
void Camara::MatrizVistaNave()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity() ;




	//
	gluPerspective(45, (float)anchoActual/(float)altoActual , 0.10, 100.0);
	
	
      
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;
	
	
	
	gluLookAt
	(
	-1, -7, 15,  // posición de la cámara  10, 0.5, -2,
	0, 0, 0,  // punto de atencion (== origen)   2, 0, 0, 
	0, 1, 0   // vector 'up' (== eje Y+)
	);
	
	
  // glRotatef(90,1,0,0);
glRotatef(camaragiro,0,1,0);
//glRotatef(90,0,0,1);



}

//**********************************************************************

void Camara::FuncRedimensionar( int nuevoAncho, int nuevoAlto )
{
  altoActual = nuevoAlto ;
  anchoActual = nuevoAncho ;
  
  glViewport(0,0,anchoActual,altoActual);
  
  using namespace std ;
  //cout << "ventana redimensionada, nuevo tamaño: " << anchoActual << " x " << altoActual << " pixels." << endl << flush ;
}


//**********************************************************************

void Camara::MatrizProyeccion()
{
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity() ;
   
   if ( anchoActual < altoActual  )
   {  const GLfloat ratioYX = GLfloat(altoActual)/GLfloat(anchoActual) ;
      glOrtho( -dis_cam,dis_cam, -dis_cam*ratioYX,dis_cam*ratioYX, -dis_cam*3.0,dis_cam*3.0 );
   }
   else
   {  const GLfloat ratioXY = GLfloat(anchoActual)/GLfloat(altoActual) ;
      glOrtho( -dis_cam*ratioXY,dis_cam*ratioXY, -dis_cam,dis_cam, -dis_cam*3.0,dis_cam*3.0 );
   }
   
}

bool Camara::GestionEventoTeclaEspecialObjeto( int key ) 
{
   bool actualizar = true ;
   const double incr = 3.0 ;
   
   	
   switch( key )
   {
   
      case GLUT_KEY_LEFT:   
         ang_ry_obj += incr ;
         break ;
      case GLUT_KEY_RIGHT:
         ang_ry_obj -= incr  ;
         break ;
      case GLUT_KEY_UP:
         ang_rx_obj += incr  ;
         break ;
      case GLUT_KEY_DOWN:
         ang_rx_obj -= incr  ;
         break ;
      case GLUT_KEY_PAGE_UP :
         ang_rz_obj += incr  ;
         break ;
      case GLUT_KEY_PAGE_DOWN :
         ang_rz_obj -= incr  ;
         break ;
      case GLUT_KEY_HOME:
         ang_rz_obj = 0.0f ;
         ang_ry_obj = 0.0f ;
         ang_rx_obj = 0.0f ;
         f_esc_obj  = 1.0f ;
         break ;
      default :
         actualizar = false ;
         cout << "tecla no usable en este modo." << endl << flush ;
   }
   return actualizar ;
}

//**********************************************************************

bool Camara::GestionEventoTeclaNormalObjeto( unsigned char key ) 
{
   using namespace std ;
   bool 
      actualizar = true ;
   const float
      f_delta = 0.05f ;  // incremento/decr. del tamaño un 5% al pulsar
   //cout << "GestionEventoTeclaNormalObjeto(key==" << key << ")" << endl << flush ;
   switch( key )
   {
      case '+' :
         if ( f_esc_obj < 10.0f )
            f_esc_obj *= (1.0f+f_delta) ;
         break ;
      case '-' :
         if ( f_esc_obj > 0.1f ) 
            f_esc_obj /= (1.0f+f_delta) ;
         break ;
      default :
         cout << "tecla no usable en este modo." << endl << flush ;
         actualizar = false ;
         break ;
   }
   return actualizar ;
}

//**********************************************************************

bool Camara::GestionEventoTeclaEspecialTipoObjeto( int key )
{  
   
}
void Camara:: escala(){
glScalef( f_esc_obj, f_esc_obj, f_esc_obj );
}
//**********************************************************************
// gestor del evento de pulsación de tecla especial en modo 'cámara'

bool Camara::GestionEventoTeclaEspecialCamara( int key )
{
   bool actualizar = true ;
   
   const GLfloat incr = 3.0 ;
   
   
   switch( key )
   {
   cout <<"sale" <<endl;
      case GLUT_KEY_UP :
         lati_cam = minim( lati_cam+incr, 89.7f );
         
         break ;
      case GLUT_KEY_DOWN :
         lati_cam = maxim( lati_cam-incr, -89.7f );
         break ;
      case GLUT_KEY_LEFT :
         longi_cam += incr ;
         break ;
      case GLUT_KEY_RIGHT :
         longi_cam -= incr ;
         break ;
      case GLUT_KEY_HOME :
         longi_cam = longi_cam_ini ;
         lati_cam  = lati_cam_ini ;
         dis_cam   = dis_cam_ini ;
         break;
      default:
         actualizar = false ;
         cout << "tecla no usada en modo 'cámara'" << endl << flush ;
         break ;
   }
   return actualizar ;
}

//**********************************************************************

bool Camara::GestionEventoTeclaNormalCamara( unsigned char key ) 
{
   using namespace std ;
   bool 
      actualizar = true ;
   const float
      f_delta = 0.05f ;  // incremento/decr. de distancia un 5% al pulsar +/-
   //cout << "GestionEventoTeclaNormalCamara(key==" << key << ")" << endl << flush ;
   
   switch( key )
   {
      case '-' :
         if ( dis_cam < 10.0f )
            dis_cam *= (1.0f+f_delta) ;
         break ;
      case '+' :
         if ( dis_cam > 0.1f ) 
            dis_cam /= (1.0f+f_delta) ;
         break ;
      default :
         cout << "tecla no usable en este modo." << endl << flush ;
         actualizar = false ;
         break ;
   }
   return actualizar ;
}




