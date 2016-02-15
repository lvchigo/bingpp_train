// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#ifdef _WIN32
#include <crtdbg.h>

#include <SDKDDKVer.h>
#endif
#include <stdio.h>

#pragma once
#pragma warning(disable: 4996)
#pragma warning(disable: 4995)
#pragma warning(disable: 4805)
#pragma warning(disable: 4267)

#include <limits>
#include <assert.h>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <fstream>
//#include <random>

#ifdef _WIN32
#include <atlstr.h>
#include <atltypes.h>
#endif

#ifndef __APPLE__
#include <omp.h>
#endif
//#include <strstream>

#ifndef _WIN32
#include <sys/stat.h>
#include <dirent.h>
#endif
using namespace std;

// TODO: reference additional headers your program requires here
#include "../LibLinear/linear.h"
#include <opencv2/opencv.hpp> 
#include <opencv/cv.h>

extern "C" {
#include "vl/generic.h"
#include "vl/imopv.h"
}

#define CV_VERSION_ID CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)
#ifdef _DEBUG
#define cvLIB(name) "opencv_" name CV_VERSION_ID "d"
#else
#define cvLIB(name) "opencv_" name CV_VERSION_ID
#endif

#pragma comment( lib, cvLIB("ts"))
#pragma comment( lib, cvLIB("world"))
using namespace cv;


typedef const Mat CMat;
typedef const string CStr;
typedef vector<Mat> vecM;
typedef vector<string> vecS;
typedef vector<int> vecI;
typedef vector<bool> vecB;
typedef vector<float> vecF;
typedef vector<double> vecD;

#ifndef _WIN32
typedef uint64_t UINT64;
typedef uint32_t UINT;
typedef int64_t INT64;
typedef uint8_t byte;
typedef bool BOOL;

#define FALSE false;
#define __popcnt64 __builtin_popcountll
#endif
enum{CV_FLIP_BOTH = -1, CV_FLIP_VERTICAL = 0, CV_FLIP_HORIZONTAL = 1};
#define _S(str) ((str).c_str())
#define CHK_IND(p) ((p).x >= 0 && (p).x < _w && (p).y >= 0 && (p).y < _h)
#define CV_Assert_(expr, args) \
{\
	if (!(expr)) {\
	  string msg(args); \
	  printf("%s in %s:%d\n", msg.c_str(), __FILE__, __LINE__); \
	  cv::error(cv::Exception(CV_StsAssert, msg, __FUNCTION__, __FILE__, __LINE__) ); }\
}

// Return -1 if not in the list
template<typename T>
static inline int findFromList(const T &word, const vector<T> &strList) {size_t idx = find(strList.begin(), strList.end(), word) - strList.begin(); return idx < strList.size() ? idx : -1;}
template<typename T> inline T sqr(T x) { return x * x; } // out of range risk for T = byte, ...
template<class T, int D> inline T vecSqrDist(const Vec<T, D> &v1, const Vec<T, D> &v2) {T s = 0; for (int i=0; i<D; i++) s += sqr(v1[i] - v2[i]); return s;} // out of range risk for T = byte, ...
template<class T, int D> inline T vecDist(const Vec<T, D> &v1, const Vec<T, D> &v2) { return sqrt(vecSqrDist(v1, v2)); } // out of range risk for T = byte, ...

inline Rect Vec4i2Rect(Vec4i &v){return Rect(Point(v[0] - 1, v[1] - 1), Point(v[2], v[3])); }

Point const DIRECTION4[5] = {
	Point(1, 0),  //Direction 0: right
	Point(0, 1),  //Direction 1: bottom
	Point(-1, 0), //Direction 2: left
	Point(0, -1), //Direction 3: up
	Point(0, 0),
};  //format: {dx, dy}


#include "CmFile.h"
#include "CmTimer.h"
#include "ValStructVec.h"


void initGPU(int threadNum);
void	releaseGPU(int threadNum);
void FelzenSegmentIndex(vector<Vec4i> &boxes, Mat &matIm, float c, int min_size);
void FelzenSegmentIndex(vector<Vec4i> &boxes, Mat &matIm, float sigma, float c, int min_size);
void mtse(vector<Vec4i> &sp_boxes, ValStructVec<float, Vec4i> &init_boxes, ValStructVec<float, Vec4i> &out_boxes, vecF thetas, const float beta, const bool combine);
