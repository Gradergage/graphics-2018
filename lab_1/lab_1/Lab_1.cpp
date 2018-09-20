#include <cstdio>
#include <iostream>
#include <windows.h>

#pragma comment(lib,"I:\\Downloads\\opcv\\opencv\\build\\x64\\vc15\\lib\\opencv_world343.lib")
#pragma comment(lib,"I:\\Downloads\\opcv\\opencv\\build\\x64\\vc15\\lib\\opencv_world343d.lib")

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>           // cv::Mat
#include <opencv2/highgui/highgui.hpp>     // cv::imread()
#include <opencv2/imgproc/imgproc.hpp>     // cv::Canny()

#define BLOCK_SIZE 16

//using namespace std;
//using namespace cv;

int getShiftVectors(char* image);

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		std::cout << "Wrong number of parameters" << std::endl;
		return -1;
	}

	getShiftVectors(argv[1]);
	system("pause");
	return 0;
}

int getShiftVectors(char* image)
{
	int rows, cols;

	cv::Mat input;	//Loading image
	input = cv::imread(image, CV_LOAD_IMAGE_COLOR);

	rows = input.rows;
	cols = input.cols;
	std::cout << "Image size: " << cols << "x" << rows << std::endl;
	cv::Mat edges; //Detecting edges in input image
	Canny(input, edges, 10, 100);

	return 0;
}