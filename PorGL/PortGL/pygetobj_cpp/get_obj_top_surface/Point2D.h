#ifndef _POINT2D_H_
#define _POINT2D_H_

//#define LINEBOX_REGION_DEBUG 0
#define GET_MIN_MAX(val, min_v, max_v ) {if(min_v>(val)) min_v = val; if(max_v <(val))max_v = val;}
#define SWAP_VAL(x,y)  { x = (x)+(y); y =(x)-(y); x = (x)-(y); } 
//#include <iostream.h>

/**
 * Primitive 2D point class used as input for the LineParamEstimator.
 *
 * Author: Ziv Yaniv (zivy@cs.huji.ac.il)
 */
class Point2D {
public:
	Point2D(double px, double py) : x(px), y(py) {}
	double x;
	double y;
	Point2D(){x=0;y=0;};
	int Selected;
	double R,G,B;

	double NewX,NewY;
	double Weight;
};

/*inline ostream &operator<<(ostream &output,const Point2D &pnt)
{
//	output<<pnt.x<<' '<<pnt.y;
	return(output);
}*/


//│AXo+BYo+C│/√（A2+B2）
// Y = KX + B ---> KX - Y + B = 0 
float PointToLineDistance(float X,float Y,float K,float B)
{
	double Denominator = sqrt( K * K + 1.0);
	double Numerator   = fabs( K* X - Y +B);
	return Numerator/Denominator;
}


//最小二乘法直线拟合
int CalculateLineKB(vector<Point2D> &PointVec, double &k, double &b, double &meanx, double&meany)
{
	//最小二乘法直线拟合
	//m_FoldList为关键点(x,y)的列表
	//拟合直线方程(Y=kX+b)
	int i;
	if(PointVec.size()==0) return 0;
	long lCount = PointVec.size();
	if(lCount<2)return FALSE;
	
	double mX,mY,mXX,mXY,n;
	mX=mY=mXX=mXY=0;
	n=lCount;
	
	Loopi(PointVec.size())
	{
		//pFold=m_FoldList->GetNext(pos);
		mX  += PointVec[i].x;
		mY  += PointVec[i].y;
		mXX += PointVec[i].x * PointVec[i].x;
		mXY += PointVec[i].x * PointVec[i].y;
	}
	
	if(mX*mX-mXX*n==0)
		return FALSE;
	
	k = (mY * mX - mXY * n) / (mX * mX - mXX * n);
	b = (mY - mX*k ) / n;
	
	meanx = mX / double( PointVec.size() );
    meany = mY / double( PointVec.size() );
	
	return 1;
}





#endif //_POINT2D_H_