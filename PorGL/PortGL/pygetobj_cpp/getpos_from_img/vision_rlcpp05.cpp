#include "Python.h"
#include "c24bitmap.h"
#include "c256bitmap.h"
#include <vector>
using namespace std;
#include "mregion.h"
#include "region.h"
#include "TraceBound.h"
#include "read_cfg.h"
#include <numpy/arrayobject.h>

#define ColorDist(R1,G1,B1,R2,G2,B2)  ((R1-R2)*(R1-R2) + (G1-G2)*(G1-G2) + (B1-B2)*(B1-B2))

double object_R,object_G, object_B, object_colordiff, scale_factor;
   
void TransGray(C24BitMap&Sr,C256BitMap&Ds)
{
	IJT;
	Ds.FormatF(Sr.Width,Sr.Height);
	LoopPic_ij(Ds)
	{
		C24PixVal Tmp=get_pix_color(Sr,i,j);
		int diff = ColorDist( (*Tmp.r), (*Tmp.g) ,(*Tmp.b) ,
		                      object_R,object_G, object_B  );
		if(diff > object_colordiff*object_colordiff)
			*get_pix_color(Ds,i,j) = 255;
		else
			*get_pix_color(Ds,i,j) = 0;
		//  *get_pix_color(Ds,i,j) = float(*Tmp.r);
		//	float(*Tmp.r)*.30+float(*Tmp.g)*.59+float(*Tmp.b)*.11;
	}
}

double GetObjDirection( Region&R )
{
	double DyDxA, DyDx , k,  b, meanx,  meany;
	CalculateLineKB(  R.ContourPtVec, k, b, meanx, meany);
	DyDx = k;
	int i;

	double Sum1(0),Sum2(0);
	double Cnt1(0),Cnt2(0);

	for( i = 0; i < R.ContourPtVec.size() - 5; i ++ )
		{
			RPoint Pt1 , Pt2;
			Pt1 = R.ContourPtVec[i];
			Pt2 = R.ContourPtVec[i+5];
			if(Pt1.x != Pt2.x)
				{
					DyDxA = (Pt1.y - Pt2.y)/(Pt1.x - Pt2.x);
					double CosSim = ( DyDxA * DyDx + 1*1 )/sqrt( 1+ DyDxA*DyDxA ) /sqrt(1+ DyDx*DyDx);
					if(CosSim>0.7)
						{
							Sum1 += DyDxA;
							Cnt1 ++;
						}
					if(CosSim <0.3)
						{
							Sum2 += DyDxA;
							Cnt2 ++;
						}
				}
			//double angle =
		}

	if(Cnt1 > (R.ContourPtVec.size() - 5)/3)
		{
			return Sum1/Cnt1;
		}
	else
		{
			if(DyDx<0.05)
				return 99;
			else
				return -1/DyDx;
		}


}


void GetBlackPicRegion(C256BitMap &Pic,C24BitMap&CPic,vector<Region>&RegionVec)
{
	int i,j;
	int ww,hh;
	ww = Pic.Width;
	hh = Pic.Height;
	ConnectedComponents Cp;

	Cp.scan_width  = Pic.LineWidth;
	Cp.scan_height = Pic.Height;

	Cp.left  = 0;
	Cp.right = ww-1;
	Cp.top   = 0;
	Cp.bottom= hh-1;
	Cp.pix_threshold = 1;
	Cp.alloc_space();

	//Cp.label_image(Pic.Buffer,1);
	Cp.label_image(Pic.Buffer,1);
	int obnum=Cp.relabel_image();

	Cp.GetResultGroup();
	CPic.FormatF(Pic.Width,Pic.Height);
	CPic.CleanPic(0);

	RegionVec.clear();
	RegionVec.resize(Cp.ResultVec.size());

	printf("obj number : %i\n",  Cp.ResultVec.size() );

	for( i=0; i< Cp.ResultVec.size(); i++)
		{
			printf("point number :%i\n", Cp.ResultVec[i].PtVec.size());
			//analysis(Cp.ResultVec[i]);
			/*printf("obj %03i: center %6.2lf ,%6.2lf;  long%4i, width:%4i, height:%5.1lf, round ratio %6.2lf\n",
				   i, Cp.ResultVec[i].x, Cp.ResultVec[i].y,
				   Cp.ResultVec[i].right  - Cp.ResultVec[i].left,
				   Cp.ResultVec[i].bottom - Cp.ResultVec[i].top,
				   Cp.ResultVec[i].Flux,
				   Cp.ResultVec[i].round_ratio);*/

			if(Cp.ResultVec[i].PtVec.size()< 5 )
				continue;

			CPic.RandPenColor();

			Loopj(Cp.ResultVec[i].PtVec.size())
			{
				CPic.SigDot(Cp.ResultVec[i].PtVec[j].x,
				            CPic.Height - 1 - Cp.ResultVec[i].PtVec[j].y);

				RPoint Pt;
				Pt.x = Cp.ResultVec[i].PtVec[j].x;
				Pt.y = CPic.Height - 1 - Cp.ResultVec[i].PtVec[j].y;
				RegionVec[i].PtVec.push_back(Pt);
			}

			CPic.SetPenColor(0 , 255, 0);
			CPic.DrawCircle(Cp.ResultVec[i].x, Cp.ResultVec[i].y, 2);

		}

	vector<int> LabelVec;

	CPic.SetPenColor(255 , 0, 0);

	TraceRegion(CPic.Width,  CPic.Height, RegionVec , LabelVec);
	Loopi( RegionVec.size() )
	{
		AnalysisRegionObj( RegionVec[i] );

		for(j=0; j<  RegionVec[i].ContourPtVec.size() ; j+=3)
			{
				CPic.SigDot( RegionVec[i].ContourPtVec[j].x,
				             RegionVec[i].ContourPtVec[j].y );
			}

		double DyDx = GetObjDirection( RegionVec[i] );
	    RegionVec[i].angle = atan(DyDx)*180.0/3.1415926;
		CPic.DrawLine(RegionVec[i].x,RegionVec[i].y,
		              RegionVec[i].x+20,RegionVec[i].y + 20* DyDx );
		
		printf("==point pos in img %8.3lf,%8.3lf, in coord  %7.3lf,%7.3lf\n",
		(RegionVec[i].x -  CPic.Width /2) ,
		(RegionVec[i].y -  CPic.Height/2),
		(RegionVec[i].x - CPic.Width/2)  * scale_factor,
		(RegionVec[i].y - CPic.Height/2) * scale_factor);
		
		//int x2,int y2);( RegionVec[i].ContourPtVec[j].x,
		// RegionVec[i].ContourPtVec[j].y );
	}



}



static PyObject *py_imgcpt(PyObject *self, PyObject *args)
{
	PyObject *bufobj;
	Py_buffer view;
	double result;
	/* Get the passed Python object */
	if (!PyArg_ParseTuple(args, "O", &bufobj))
		{
			return NULL;
		}

	/* Attempt to extract buffer information from it */
	if (PyObject_GetBuffer(bufobj, &view, PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1)
		{
			return NULL;
		}

	printf("========================\n",view.ndim);
	printf("the opencv obj's dimensions are %i\n",view.ndim);
	printf("========================\n",view.ndim);

	printf("============ok0=============\n");
	printf(" shape:== %d, %d, %d =\n",    view.shape[0], view.shape[1], view.shape[2]);
	printf("stride:== %d, %d, %d =\n",  view.strides[0], view.strides[1], view.strides[2]);
	printf("====data format:%s=====\n",view.format);
	printf("============ok1=============\n");

//==========================================================================================================
	int height = view.shape[0];
	int width  = view.shape[1];
	int i,j;
	float* ImgPtr = (float*)view.buf;

	C256BitMap Pic;
	Pic.FormatF(width, height);
	float *array_buff  = new float[width*height];
	float **array_img  = new float*[height];

	float min_val(999), max_val(-999);

	for(i=0; i<height; i++)
		{
			array_img[i] = & array_buff[i* width ];
		}

	memcpy(array_buff, ImgPtr , 4 * width * height);

	min_val  = *min_element(array_buff, array_buff + width*height);
	max_val  = *max_element(array_buff, array_buff + width*height);
	printf( "min: %.5lf, max:%.5lf\n", min_val , max_val );

	for(i=0; i<height; i++)
		for( j = 0; j < width; j++)
			{
				double pixval = ( max_val - array_img[i][j] ) * 30.0 * 256.0;
				pixval /= (max_val - min_val);
				if(pixval>255) pixval =255;
				* get_pix_color( Pic,j,i)	= pixval;
			}

	Pic.Save("gray.bmp");


	vector<Region> RegionVec;
	C24BitMap CPicObjs;
	GetBlackPicRegion(Pic, CPicObjs ,  RegionVec);
	CPicObjs.Save("target_objs.bmp");


	delete [] array_buff;
	delete [] array_img;
//======================================================================================
	/* Pass the raw buffer and size to the C function */


	PyBuffer_Release(&view);
	npy_intp dims[1] = {RegionVec.size()*3};
	int nd  = 1;
	double *lm_data = new double[RegionVec.size()*3];
	//lm[0] =20;
	//lm[1] =30;
    
	for(i=0 ; i < RegionVec.size(); i++)
	{
		lm_data[3*i  ] = (RegionVec[i].x - width/2)*scale_factor;
		lm_data[3*i+1] = (RegionVec[i].y -height/2)*scale_factor;
		lm_data[3*i+2] = RegionVec[i].angle;
		printf("%10.4lf,%10.4lf\n",lm_data[3*i  ],lm_data[3*i  +1]);
	}
	
	PyObject *arr = PyArray_SimpleNewFromData(nd, dims, NPY_DOUBLE, lm_data);
	Py_INCREF(arr);

	//delete []lm;
	return(arr);
//return Py_BuildValue("d", result);

// return Py_BuildValue("d", result);
}



/* Module method table */
static PyMethodDef SampleMethods[] =
{
	{"imgcpt",  py_imgcpt, METH_VARARGS, "cpp_ext_calculation"},
	{ NULL, NULL, 0, NULL}
};

/* Module structure */
static struct PyModuleDef samplemodule =
{
	PyModuleDef_HEAD_INIT,
	"sample1",           /* name of module */
	"A sample module",  /* Doc string (may be NULL) */
	-1,                 /* Size of per-interpreter state or -1 */
	SampleMethods       /* Method table */
};

/* Module initialization function */
PyMODINIT_FUNC
PyInit_sample1(void)
{
	import_array();
	vector<std::string> lines;
	readlistfile("config.txt", lines);
	printf("%s\n",lines[0].c_str());
	printf("%s\n",lines[1].c_str());
	
	vector<std::string> items;
	splitString(lines[0], items,",");
	
	object_R = atof(items[1].c_str());
	object_G = atof(items[2].c_str());
	object_B = atof(items[3].c_str());
	printf("target color is %.2lf, %.2lf, %.2lf\n", object_R, object_G, object_B);
	//=======================================================================
	items.clear();
	splitString(lines[1], items,",");
	object_colordiff = atof(items[1].c_str());
	//=======================================================================
	items.clear();
	splitString(lines[2], items,",");
	scale_factor = atof(items[1].c_str());
	
	
	return PyModule_Create(&samplemodule);
}
