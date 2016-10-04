#ifndef READER_H
#define READER_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>     

using namespace cv;
using namespace std;

class Reader
{
public:
	bool LoadPhotos(string filePath);
	void CalculateMeanHistogram();
	void CalculateMeanValueFromHsv();

private: 
	Mat CalculateHistogramMatrix(Mat frame, int histSize);
	float CalculateMeanOfHistogram(Mat histogram);
	const string ImageFolderName = "Images";
	const string OutputFile = "Result/result.txt";

	vector<string> ImagePaths;
	bool SaveMean(string outputFile, float mean);
};

#endif