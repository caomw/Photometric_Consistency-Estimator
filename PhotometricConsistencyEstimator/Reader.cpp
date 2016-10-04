#include "Reader.h"

///<summary>
///Load photos from specified txt file.
///</summary>
bool Reader::LoadPhotos(string filePath)
{
	ifstream File(filePath);
	string str;
	try
	{
		//read lines from txt file
		while (getline(File, str))
		{
			if (str != "")
			{
				ImagePaths.push_back(ImageFolderName + "/" + str + ".png");
			}
		}
	}
	catch (exception& e)
	{
		return false;
	}

	//check if vector has values
	if (!ImagePaths.empty())
	{
		return true;
	}	
	else
	{
		return false;
	}
}

///<summary>
///Calculates photometric consistency for images
///</summary>
void Reader::CalculateMeanHistogram()
{
	Mat frame, hist;
	float meanHist;
	//calculate average histogram for all images
	for (int i = 0; i < ImagePaths.size(); i++)
	{
		//load image
		frame = imread(ImagePaths[i], IMREAD_GRAYSCALE);
		if (!frame.data)
		{
			cout << "Error while loading frame!" << endl;
			return;
		}

		//process image
		try
		{
			cout << "Processing: " << ImagePaths[i];
			//calculate historgam
			hist = CalculateHistogramMatrix(frame, 256);

			//calculate mean from Mat object
			meanHist = CalculateMeanOfHistogram(hist);

			//save it to the file
			SaveMean(OutputFile, meanHist);
			
			cout << "... done"<< endl;
		}
		catch(exception& e)
		{
			cout << "Exception occured while processing data. Exception message: " << e.what() << endl;
			return;
		}
	}
}

///<summary>
///Calculates normalized histogram for specified frame
///</summary>
void Reader::CalculateMeanValueFromHsv()
{
	Mat frame, v, hsv, vHist;
	Mat channels[3];
	float meanValue;
	Scalar sumV;
	Rect myRoi(160, 70, 310, 350);
	int size = 310 * 350;
	//calculate average V from HSV for all images
	for (int i = 0; i < ImagePaths.size(); i++)
	{
		//load image
		frame = imread(ImagePaths[i], IMREAD_COLOR);

		if (!frame.data)
		{
			cout << "Error while loading frame!" << endl;
			return;
		}

		//crop
		frame = frame(myRoi);

		//process image
		try
		{
			cout << "Processing: " << ImagePaths[i];

			cvtColor(frame, hsv, CV_BGR2HSV);
			split(hsv, channels);
			v = channels[2];
			sumV = sum(v);
			meanValue = sumV[0] / size;

			//save it to the file
			SaveMean(OutputFile, meanValue);
			cout << "... done" << endl;
		}
		catch (exception& e)
		{
			cout << "Exception occured while processing data. Exception message: " << e.what() << endl;
			return;
		}
	}
}

///<summary>
///Calculates normalized histogram for specified frame
///</summary>
Mat Reader::CalculateHistogramMatrix(Mat frame, int histSize)
{
	Mat histogram;
	
	//set the range for grayscale
	float range[] = { 0, 256 };
	const float* histRange = { range };

	//calculate histogram
	calcHist(&frame, 1, 0, Mat(), histogram, 1, &histSize, &histRange, true, false);
	normalize(histogram, histogram, 0, frame.rows, NORM_MINMAX, -1, Mat());

	return histogram;
}

///<summary>
///Calculates the mean value of histogram
///</summary>
float Reader::CalculateMeanOfHistogram(Mat histogram)
{
	Scalar tempVal = mean(histogram);
	float myMatMean = tempVal.val[0];
	return myMatMean;
}

///<summary>
///Append calculated photometric consistency to the file
///</summary>
bool Reader::SaveMean(string outputFile, float mean)
{
	ofstream result;
	result.open(outputFile, ios_base::app);
	result.setf(ios::fixed);

	if (result.good())
	{
		result << std::setprecision(2) << mean << endl;
		result.close();
		return true;
	}
	else
	{
		return false;
	}
}