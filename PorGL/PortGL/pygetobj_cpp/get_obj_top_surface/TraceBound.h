#ifndef Trace_Region_Contour_H
#define Trace_Region_Contour_H
#include "mregion.h"
//#include "objstrok.h"

#define DEBUG_OUT_STROKEINFO 0
#define DUMP_CONTOURINFO_DEBUG 0


struct PointDxy       //标记点
{
	int x,y;           //点的坐标
	double dx,dy;      //点的方向
	double angle;      //点的角度
	int ifBoundPoint;  //是否边界点
	int chain       ;  //链码数值
	int pixIntensity;  //像素值
	int ptOffset    ;  //像素点到buffer的偏移
	int Label       ;  //联通域的组号
	int groupIdx    ;  //点在联通域内的序号
	int R,G,B;
	float strokeWidth;
};


/// \brief 根据边界点来跟踪一个区域的轮廓线
///    
/// \param ImgWidth      图像宽度
/// \param ImgHeight     图像高度
/// \param ImgLabel      图像的标记点
/// \param startpos      轮廓跟踪的开始点(+)                 
/// \param btpos         轮廓跟踪的开始点附近的边界外侧点(-)
/// \param contour       跟踪完以后的轮廓结果 
/// \param TraceLb       需要跟踪的轮廓标记     
/// \return   
void TraceOneContour(int ImgWidth,int ImgHeight,vector<int>&ImgLabel,
					 const std::pair<int,int>& startpos,
					 const std::pair<int,int>& btpos, vector<int>& contour,int TraceLb)
{
	int xSize = ImgWidth, ySize = ImgHeight;
	
	char BLACK = 1;
	enum { LKN = 8 };
	static int cwmat[LKN][2] = {		// clock-wise matrix
		{-1, +1},		// left-upper
		{0, +1},		// upper
		{+1,+1},
		{+1, 0},
		{+1, -1},
		{0, -1},
		{-1, -1},
		{-1, 0}		// left
	};
	contour.clear();
	int px = startpos.first, py = startpos.second;	// current center point
	int bx = btpos.first, by = btpos.second ;		// bt point
	contour.push_back(py*xSize + px);
	
	int cx = bx, cy = by;
	bool bstop = false;
	int nVisitStart = 1;
	static int nStopTimes = 1;
	
	do {
		// get next clockwise pixel for (cx, cy) around (px, py)
		int cur = -1;
		for (int i = 0; i < LKN; ++i)
		{
			if (cwmat[i][0] == (cx - px) &&
				cwmat[i][1] == (cy - py))
			{
				cur = i;
				break;
			}
		}
		if (cur < 0) break;
		
		int last = cur;
		cur = (cur+1) % LKN;
		while (cur != last)
		{	// loop 8-connected cells around p
			int prev = (cur - 1 + LKN)%LKN;
			cx = px + cwmat[cur][0], cy = py + cwmat[cur][1];
			bx = px + cwmat[prev][0], by = py + cwmat[prev][1];
			
			if ((cx == startpos.first && cy == startpos.second)
				&& (bx == btpos.first && by == btpos.second))
			{	// Jacob's stopping criterion
				bstop = true;
				break;
			}
			if (cx >= 0 && cx < xSize && cy >=0 && cy < ySize
			//	&& (ImgLabel[cy*ImgWidth + cx]>=0))//bp->pixRef(cx, cy) == BLACK)
			   &&	ImgLabel[cy*ImgWidth + cx]==TraceLb )
			{
				if (cx == startpos.first && cy == startpos.second)
				{  	// In some class, only Jacob's stopping cannot stop algorithm
					// so add visit time stopping criterion
					if (++nVisitStart >= nStopTimes)
					{
						bstop = true;
						break;
					}
				}
				contour.push_back(cy * xSize + cx);
				px = cx, py = cy;
				cx = bx, cy = by;
				break;
			}
			else
			{
				cur = (cur+1) % LKN;
			}
		}
		// handle isolated pixel point
		if (cur == last) break;
		if (bstop) break;
	}  while (1);
}

/// \brief 对一组轮廓跟踪完善其轮廓信息
///  跟踪完善区域的轮廓信息,且计算区域的笔触宽度信息(stroke width,mean,stdev)
/// \param Width       图像的宽度
/// \param Height      图像的高度
/// \param RgVec       待分析的一组区域向量      
/// \param LabelVec    图像的联通域标记信息 
/// \return   轮廓信息会更新在Region的CountorPt和Contour中
void TraceRegion(int Width,int Height,vector<Region>&RgVec,vector<int>&LabelVec)
{
   
	int i,j;
	vector<int> ContourMp;
	int TotalCnt =  Width * Height;

	LabelVec.resize(TotalCnt);
    ContourMp.resize(TotalCnt);
	
	int ObjNum = RgVec.size();
    
	Loopi(TotalCnt)  LabelVec[i]  = -1;
	Loopi(TotalCnt)  ContourMp[i] =  0;
	
	Loopi(RgVec.size())
	{   
		RgVec[i].ContourPtVec.clear();
		RgVec[i].InflectionPts.clear();

		RgVec[i].left = RgVec[i].right = RgVec[i].top = RgVec[i].bottom = -1;

		Loopj(RgVec[i].PtVec.size())
		{
			int xx,yy;
			xx = RgVec[i].PtVec[j].x ;
			yy = RgVec[i].PtVec[j].y ;
			int Pos;
			Pos = yy * Width + xx;
			LabelVec[Pos] = i;
		}
  }  
//--------------------------------------------------------------------
	Loopi( Width )
	{
		LabelVec[i                     ] = -1; 
		LabelVec[(Height-1) * Width + i] = -1;
	}
	
	Loopi(Height)
	{
		LabelVec[i*Width             ] = -1;
		LabelVec[i*Width +  (Width-1)] = -1;
}
//--------------------------------------------------------------------
  pair<int,int> btpos;
  pair<int,int> startpos; 
  vector<int> contour;
  C24BitMap CPic;
  CPic.FormatF(Width,Height);
  CPic.CleanPic(0);

  Loopj(Height)
     Loopi(Width) 
  {   
	  int MinX,MaxX,MinY,MaxY;
	  //if(i==0||j==0) continue;
      if(LabelVec[j* Width + i]<0)
	  {btpos.first  =  i;
       btpos.second =  j;
	  }  //(LabelVec[j* Width + i]>=0) && 
	  else
	     if((LabelVec[j* Width + i-1]<0)&&
		     ContourMp[j* Width + i] ==0 )
      {
		  startpos.first   = i;
		  startpos.second  = j;

		  MinX = MaxX = i;
		  MinY = MaxY = j;
		  int TraceLabel = LabelVec[j* Width + i];
		  
		  TraceOneContour(Width, Height, LabelVec, startpos, btpos,  contour , TraceLabel);
          
		  CPic.SetPenColor(255,0,0); 
		  /*int Label = LabelVec[j* Width + i]; 
		  for (int t=0; t<contour.size(); t++)
		  {
			  ContourMp[contour[t]] =1;
			  int xx,yy;
			  xx = contour[t] % Width; 
			  yy = contour[t] / Width;
			  
			  if(xx < MinX) MinX = xx; if( xx > MaxX ) MaxX = xx;
			  if(yy < MinY) MinY = yy; if( yy > MaxY ) MaxY = yy;	

			  CPic.SigDot(xx, yy);
              RPoint Pt;
			  Pt.x = xx; Pt.y = yy;
			  RgVec[Label].ContourPtVec.push_back(Pt);
		  }*/

		  int Label = LabelVec[j* Width + i]; 
		  vector<RPoint> contour_pts;
		  contour_pts.clear();
		  for (int t=0; t<contour.size(); t++)
		  {
			  ContourMp[contour[t]] = 1;
			  int xx,yy;
			  xx = contour[t] % Width; 
			  yy = contour[t] / Width;
			  
			  if(xx < MinX) MinX = xx; if( xx > MaxX ) MaxX = xx;
			  if(yy < MinY) MinY = yy; if( yy > MaxY ) MaxY = yy;	

              RPoint Pt;
			  Pt.x = xx; Pt.y = yy;
			  RgVec[Label].ContourPtVec.push_back(Pt);
			  contour_pts.push_back(Pt);
		  }
		  
		  if(contour.size()>0)
		  {
			  RgVec[Label].MContours.push_back(contour_pts);
		  }
		  
		  if(RgVec[Label].left==-1)
		  {
			   RgVec[Label].left = MinX; RgVec[Label].right  = MaxX;
			   RgVec[Label].top  = MinY; RgVec[Label].bottom = MaxY;
			   RgVec[Label].rwidth  = MaxX-MinX+1;
			   RgVec[Label].rheight = MaxY-MinY+1;
		  }
		  else
		  {
			  if(RgVec[Label].left > MinX)RgVec[Label].left = MinX; if(RgVec[Label].right  < MaxX) RgVec[Label].right  = MaxX;
			  if(RgVec[Label].top  > MinY)RgVec[Label].top  = MinY; if(RgVec[Label].bottom < MaxY) RgVec[Label].bottom = MaxY;
			  RgVec[Label].rwidth  = RgVec[Label].right  - RgVec[Label].left +1;
              RgVec[Label].rheight = RgVec[Label].bottom - RgVec[Label].top  +1;
		  }

		  int MaxSz = max((MaxY-MinY+1),(MaxX-MinX+1));
		  int Step  = MaxSz/16;
		  if(Step<2) Step = 2;

         
		  
		  CPic.SetPenColor(0,255,0);

		  if(contour.size()> (Step*2))
                 for(int t=Step;t<contour.size()-Step;t++)
		  {
          //-------------------------------------------------------
			  if((t+Step)> (contour.size()-1))
				  break;
			  double dx1,dy1,dx2,dy2;		
			  dx1 = contour[t]%Width - contour[t-Step]%Width ;
			  dy1 = contour[t]/Width - contour[t-Step]/Width ;
			  
			  dx2 = contour[t+Step]%Width - contour[t]%Width ;
			  dy2 = contour[t+Step]/Width - contour[t]/Width ;
			  
			  //int Vote =  (atan2(dy1, dx1) + M_PI) / (M_PI/2.0);
			  //Vote = BOUND(Vote, 0, 3);
			  //ValArr[Vote] += 1.0;
			  //Cnt++;
			  
			  double Val = (dx1*dx2 + dy1*dy2) / (sqrt(dx1*dx1+dy1*dy1)*sqrt(dx2*dx2+ dy2*dy2));
			  if(fabs(Val)<0.8)
			  {
				  //PtVec[Idx3].InflectionPt = 1;
				  //InflectPtCnt ++;
				  int xx,yy;
				  xx = contour[t]%Width;
				  yy = contour[t]/Width;
				 /* CPic.SigDot(xx -1, yy);
				  CPic.SigDot(xx +1, yy);
				  CPic.SigDot(xx , yy-1);
				  CPic.SigDot(xx , yy+1);*/

				  RPoint Pt;
				  Pt.x = xx; Pt.y = yy;
			      RgVec[Label].InflectionPts.push_back(Pt);
			}
		  //-------------------------------------------------------
		  }
	      contour.clear();
	  }		
       
	  
  }

//------------------------------------------------------------------------------------
}

/// \brief     计算一个区域内的特征
///            计算区域的上下左右、长宽、圆心度等 
/// \param     Obj  待计算的一组区域
/// \return 无
void AnalysisRegionObj(Region&Obj)
{
	int i;
	float x,y,xmin,xmax,ymin,ymax;
	float xWeight,yWeight,gWeight;
    xWeight = yWeight = gWeight = 0;
	int val;
	xmin = ymin = 9999;
	xmax = ymax = 0;
	/*-----  integrate results */
	for (i=0; i<Obj.PtVec.size();i++)
	{  
		x  = Obj.PtVec[i].x; y = Obj.PtVec[i].y;
		val= 1;//Obj.PtVec[i].pixIntensity;
		
		if (xmin > x) xmin = x; if (xmax < x) xmax = x;
		if (ymin > y) ymin = y; if (ymax < y) ymax = y;
		
		xWeight += x * val; yWeight += y *val; gWeight  +=val;
	}   
	
	/* copy some data to "obj" structure */
	//Mxx=Mxx/rv;Myy=Myy/rv;Mxy=Mxy/rv;
	
	Obj.left  = xmin; Obj.right  = xmax;
	Obj.top   = ymin; Obj.bottom = ymax;
    Obj.GeoX =  ( xmin + xmax ) / 2;
	Obj.GeoY =  ( ymin + ymax ) / 2;
	
    Obj.rwidth  = xmax - xmin +1; 
	Obj.rheight = ymax - ymin +1;
	
	Obj.x   =  (xWeight / gWeight+1.0);
	Obj.y   =  (yWeight / gWeight+1.0);
    
	double Mxx,Myy,Mxy;
    Mxx = Myy = Mxy = 0;
	
	for (i=0; i<Obj.PtVec.size();i++)
	{
		x  = float(Obj.PtVec[i].x)-Obj.x;
		y  = float(Obj.PtVec[i].y)-Obj.y;
		val= 1;//Obj.PtVec[i].Flux;
		Mxx +=  (x * x * val); // / sum (I)
		Myy +=  (y * y * val); // / sum (I)
		Mxy +=  (x * y * val); // / sum (I) 
	}
	
	Obj.roundratio = sqrt(pow((Mxx - Myy), 2) + pow((2 * Mxy) , 2)) / (Mxx + Myy); 
	
}


#endif
