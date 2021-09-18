﻿#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

#include "SGMfunction.h"
#include "PreProcessing.h"
#include "PostProcessing.h"


using namespace cv;
using namespace std;

int main() {

	//load image
	Mat lImg = imread("image/leftimage/L.bmp", 1);
	Mat rImg = imread("image/rightimage/R.bmp", 1);
	if (!lImg.data || !rImg.data) {
		printf("Error: can not open image\n");
		printf("\nPress any key to continue...\n");
		system("pause");
		return -1;
	}

	//image preprocessing 
	PreMedianFlitering(lImg, lImg);
	PreMedianFlitering(rImg, rImg);

	//initialize disparity image 
	int hei = lImg.rows;
	int wid = rImg.cols;
	Mat lDis = Mat::zeros(hei, wid, CV_32FC1);
	Mat postlDis = Mat::zeros(hei, wid, CV_32FC1);

	//sgm compute
	SGMStereo sgm;
	sgm.compute(lImg, rImg, lDis);

	//post processing
	PostMedianFlitering(lDis, postlDis);

	//export result
	imwrite("image/resimage/000045_11_64res_row-5.png", lDis);
	imwrite("image/resimage/000045_11_64res_post-5.png", postlDis);

	return 0;

}