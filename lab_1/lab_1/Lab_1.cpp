#include <cstdio>
#include <iostream>
#include <windows.h>

//#pragma comment(lib,"I:\\Downloads\\opcv\\opencv\\build\\x64\\vc15\\lib\\opencv_world343.lib")
#pragma comment(lib,"I:\\Downloads\\opcv\\opencv\\build\\x64\\vc15\\lib\\opencv_world343d.lib")

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>           // cv::Mat
#include <opencv2/highgui/highgui.hpp>     // cv::imread()
#include <opencv2/imgproc/imgproc.hpp>     // cv::Canny()
#include <opencv2/imgcodecs.hpp>

#define BLOCK_SIZE 20
#define AREA_SIZE BLOCK_SIZE*2



int getShiftVectors(char* srcName, char* resName);
void compareImages(cv::Mat &src, cv::Mat &res);
int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		std::cout << "Wrong number of parameters" << std::endl;
		return -1;
	}
	getShiftVectors("testimage.bmp", "testimage2.bmp");
	return 0;
}


int getShiftVectors(char* srcName, char* resName)
{

	cv::Mat src, res;

	src = cv::imread(srcName, CV_LOAD_IMAGE_COLOR);
	res = cv::imread(resName, CV_LOAD_IMAGE_COLOR);
	compareImages(src, res);

	return 0;
}

void compareImages(cv::Mat &src, cv::Mat &res)
{

	int wSrc = src.rows;
	int hSrc = src.cols;
	size_t sSrc = src.step;

	int wRes = res.rows;
	int hRes = res.cols;
	size_t sRes = res.step;

	cv::Mat cpy;
	res.copyTo(cpy);

	int height = hSrc - hSrc % BLOCK_SIZE;
	int width = wSrc - wSrc % BLOCK_SIZE;
	int h = 0, w = 0;

	for (h = 0; h <= height; h += BLOCK_SIZE)			//Внешние циклы
	{													//
		for (w = 0; w <= width; w += BLOCK_SIZE)		//Задают новый блок
		{

			bool eq = false;
			int bh, bw;
			if ((bh = BLOCK_SIZE) > hSrc - h)
				bh = hSrc - h;
			if ((bw = BLOCK_SIZE) > wSrc - w)
				bw = wSrc - w;
				
			cv::Rect roi1(h, w,bh, bw);
			cv::Mat srcBlock(src, roi1);

			cv::rectangle(cpy, roi1, cv::Scalar(255, 0, 0), 1, 8, 0);

					
					//Horisontal borders
					int hal=0, har=0;
					
					if ((hal = h - AREA_SIZE) < 0)
						hal = 0;

					if ((har = h + AREA_SIZE+bh) >= hSrc)
						har = hSrc;

					//Vertical borders
					int wal=0, war=0;

					if ((wal = w - AREA_SIZE) < 0)
						wal = 0;

					if ((war = w + AREA_SIZE + bw) >= wSrc)
						war = wSrc;

					int i = 0, j = 0;
					cv::Rect roi3(hal, wal, har-hal, war-wal);
				//	cv::rectangle(cpy, roi3, cv::Scalar(0, 0, 255), 1, 8, 0);

					for (i = hal; i < har; i++)       //Внутренние циклы для сравнения блоков
					{										   //
						for (j = wal; j < war; j++)   //Сравнивают блоки поэлементно
						{

							if ((i+bh)<hSrc && (j+bw)<wSrc)
							{
								cv::Rect roi2(i, j, bh, bw);
								cv::Mat resBlock(res, roi2);

							//	printf("src(%d,%d,%d,%d) res(%d,%d,%d,%d)\n", h, w, bh, bw, i, j, bh, bw);
								//std::cout << "Start block:" << h << "" << w << " -  BlockToCompare: " << i<< "x" << j << std::endl;
								eq = (cv::sum(srcBlock != resBlock) == cv::Scalar(0, 0, 0, 0));
								//eq = cv::countNonZero(diff) == 0;
								if (eq)
								{
								//	std::cout << "Start block:" << h << "x" << w << " -  BlockToCompare: " << i << "x" << j << std::endl;
									cv::Point pt1(h, w);
									cv::Point pt2(i, j);
									cv::arrowedLine(cpy, pt1, pt2, 1, 1, 8, 0, 0.05);
									cv::rectangle(cpy, roi2, cv::Scalar(0, 255, 0), 1, 8, 0);
									break;
								}
							}
							
						}
						if (eq)
						{
							break;
						}
					}

		}
	}
	cv::namedWindow("original", CV_WINDOW_AUTOSIZE);
	cv::imshow("original", cpy);
	cv::waitKey(0);
}