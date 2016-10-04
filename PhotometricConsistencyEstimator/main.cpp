#include "Reader.h"

int main(int argc, char** argv)
{
	Reader r;
	if (r.LoadPhotos("Images/Images.txt"))
	{
		//r.CalculateMeanHistogram();
		r.CalculateMeanValueFromHsv();
		
		cout << "Photometric consistency for specified images saved to file 'Result/results.txt'" << endl;
	}
	else
	{
		cout << "Error occured while loading images. Specify your path in 'Images/Images.txt' properly..." << endl;
		return 1;
	}

	cout << endl << "Pres any key to continue..." << endl;
	waitKey(0);
	getchar();
	return 0;
}