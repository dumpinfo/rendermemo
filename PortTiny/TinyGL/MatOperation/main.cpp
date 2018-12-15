#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "MatMath.h"
#include "Quaternion.h"


void Quaternion2RotMatrix(const Quaternion &q, Matrix<double>&m)
 {
    m.SetDimension(3,3);
	m[0][0] = 1.0f - 2.0f * (q.y*q.y + q.z*q.z);                                         
	m[0][1] = 2.0f * (q.x*q.y + q.w*q.z);                                                
	m[0][2] = 2.0f * (q.x*q.z - q.w*q.y);                                                
                                                                                       
	m[1][0] = 2.0f * (q.x*q.y - q.w*q.z);                                                
	m[1][1] = 1.0f - 2.0f * (q.x*q.x + q.z*q.z);                                         
	m[1][2] = 2.0f * (q.y*q.z + q.w*q.x);                                                
                                                                                       
	m[2][0] = 2.0f * (q.x*q.z + q.w*q.y);                                                
	m[2][1] = 2.0f * (q.y*q.z - q.w*q.x);                                                
	m[2][2] = 1.0f - 2.0f * (q.x*q.x + q.y*q.y);                                         
}

struct Point3d
{
	double x,y,z;
};
#define DBL_EPSILON 0.00001
double norm(Point3d pt)
{
	return sqrt(pt.x*pt.x+pt.y*pt.y+pt.z*pt.z);
}
Matrix<double> GetRotateMatrix(double x,double y,double z)
{       
      //Matrix<double> m;
	  Point3d r;
      r.x = x; r.y = y;  r.z = z;
      Matrix<double> m; 
	  m.SetDimension(3,3);
      double theta = norm(r);

	   Matrix<double> m_eye; 
	     
	   m_eye.SetDimension(3,3);
	   m_eye[0][0] = m_eye[1][1] = m_eye[2][2] =1.0;
     
 	  if( theta < DBL_EPSILON )
        {
           // cvSetIdentity( dst );
          return m_eye;
        }
        else
        {
            double c = cos(theta);
            double s = sin(theta);
            double c1 = 1. - c;
            double itheta = theta ? 1./theta : 0.;

           r.x *= itheta;
		   r.y *= itheta;
		   r.z *= itheta;
           double array1[9] = {r.x*r.x, r.x*r.y, r.x*r.z, r.x*r.y, r.y*r.y, r.y*r.z, r.x*r.z, r.y*r.z, r.z*r.z };
           Matrix<double> rrt;//( array1, 9);
		   double array2[9] = {0, -r.z,  r.y,  r.z,    0, -r.x,  -r.y,  r.x,    0 };
           Matrix<double> r_x;//( array2, 9 );

            // R = cos(theta)*I + (1 - cos(theta))*r*rT + sin(theta)*[r_x]
           //Matrix<double>  R = c*m_eye + c1*rrt + s*r_x;
		   Matrix<double>  R = m_eye * c + rrt * c1 + r_x * s;
           return R;
           // Mat(R).convertTo(cvarrToMat(dst), dst->type);
        }
}
		
int main(int argc,char* argv[])
{
	Matrix <double> Mat(8,8);
	printf("hello world\n");
	Mat[3][1] =2;
	printf("%.2lf\n", Mat(3,1));
	
	/*
	 x: 0.0131551834857
  y: 0.828438808599
  z: -0.558071316537
  w: 0.0455245781134
  */
	Quaternion  q;
    q.x = 0.0131551834857 ;
    q.y = 0.828438808599  ;
    q.z = -0.558071316537 ;
    q.w = 0.0455245781134 ; 
  
	Matrix<double> rotM;
  Quaternion2RotMatrix(q, rotM);
	EulerAngles euler;
	euler.fromObjectToInertialQuaternion(q);
	euler.fromRotationMatrix( rotM);
	
	return 1;
}
