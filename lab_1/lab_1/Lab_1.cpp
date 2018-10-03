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
#define AREA_SIZE BLOCK_SIZE*4
//using namespace std;
//using namespace cv;
int getShiftVectors(char* srcName, char* resName);
void compareImages(cv::Mat &src, cv::Mat &res);
int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		std::cout << "Wrong number of parameters" << std::endl;
		return -1;
	}

	getShiftVectors("testimage.bmp", "testimage.bmp");
	//getShiftVectors("testimage2.jpg")
	return 0;
}


int getShiftVectors(char* srcName, char* resName)
{

	cv::Mat src, res;

	src = cv::imread(srcName, CV_LOAD_IMAGE_COLOR);
	res = cv::imread(resName, CV_LOAD_IMAGE_COLOR);
	compareImages(src, res);
	//cv::Point pt1(height / 3, width / 3);
	//cv::Point pt2(height / 4, width / 4);


	//image = cvCloneImage(input);
	/*Canny(input, edges, 10, 100);*/
	//image = cvLoadImage(imageName, 1);
	// пробегаемся по всем пикселям изображения
	//for (int y = 0; y < image->height; y++) {
	//	uchar* ptr = (uchar*)(image->imageData + y * image->widthStep);
	//	for (int x = 0; x < image->width; x++) {
	//		// 3 канала 
	//		ptr[3 * x] = 0;     // B - синий
	//		ptr[3 * x + 1] = 0;   // G - зелёный
	//		ptr[3 * x + 2] = 255; // R - красный
	//	}
	//}
//	cv::arrowedLine(image, pt2, pt1, 23, 1, 8, 0, 0.05);
	cv::namedWindow("original", CV_WINDOW_AUTOSIZE);
	cv::imshow("original", res);
	//printf("[i] channels:  %d\n", image->nChannels);
	//printf("[i] pixel depth: %d bits\n", image->depth);
	//printf("[i] width:       %d pixels\n", image->width);
	//printf("[i] height:      %d pixels\n", image->height);
	//printf("[i] image size:  %d bytes\n", image->imageSize);
	//printf("[i] width step:  %d bytes\n", image->widthStep);
	cv::waitKey(0);                   // Show our image inside it.

	/*cvWaitKey(0);*/
	/*CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i);

	cvLine(color_dst, line[0], line[1], CV_RGB(255, 0, 0), 3, CV_AA, 0);*/


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

	uchar *dataSrc = src.data;
	uchar *dataRes = res.data;

	
	for (int h = 0; h < (hSrc - AREA_SIZE); h += AREA_SIZE)			//Внешние циклы
	{																//
		for (int s = 0; s < (sSrc - AREA_SIZE); s += AREA_SIZE)		//Задают зоны поиска
		{
			//cv::Rect roi( s, h, BLOCK_SIZE, BLOCK_SIZE);
			//cv::Mat srcBlock(src,roi);
			bool eq = false;
			//inner Area cycle
			for (int c = 0; c < AREA_SIZE; c++)		//Внутренние циклы для зоны поиска
			{										//
				uchar SAD = 0;						//
				for (int d = 0; d < AREA_SIZE; d++) //Задают начальную точку для выбора блока, который будет сравниваться со всеми остальными блоками зоны 
				{
					//inner  Block cycle
					//uint8_t *srcBlock = dataSrc + (a + h) * BLOCK_SIZE + b + s;
					//cv::Rect roi2(s + d, h + c, BLOCK_SIZE, BLOCK_SIZE);
					//cv::Mat resBlock(res,roi2);
					
					//std::cout <<"Area :" << h << "x" << s << " Block: "<< h + c << "x" <<  s + d << std::endl;
					//eq = std::equal(srcBlock.begin<uchar>(), srcBlock.end<uchar>(), resBlock.begin<uchar>());
				//	cv::Mat diff = resBlock != srcBlock;
					// Equal if no elements disagree
				//	eq = (cv::sum(srcBlock != resBlock) == cv::Scalar(0, 0, 0, 0));
					//eq = cv::countNonZero(diff) == 0;
					/*resBlock.release();
					if (eq)
					{
						cv::Point pt1((h + BLOCK_SIZE), (s+ BLOCK_SIZE));
						cv::Point pt2((h + BLOCK_SIZE + c), (s + BLOCK_SIZE+d));
						cv::arrowedLine(res, pt1, pt2, 1, 1, 8, 0, 0.05);
						break;
					}*/
					
					SAD = 0;
					for (int i = 0; i < BLOCK_SIZE; i++)       //Внутренние циклы для сравнения блоков
					{										   //
						for (int j = 0; j < BLOCK_SIZE; j++)   //Сравнивают бллоки поэлементно
						{
							//uint8_t val = myData[i * width + j];
							if ((i + c + h < hSrc) && (j + c + s < sSrc))
							{
								 
							}
							//SAD += abs(dataSrc[(i + h) * sSrc + j + s] - dataRes[(i + c + h) * sSrc + j + d + s]);
							uchar valS = dataSrc[(i + h) * sSrc + j + s];
							uchar valR = dataRes[(i + c + h) * sSrc + j + d + s]; //блок, смещенный относительно зоны поиска

							SAD += abs(valS - valR);
							/*if (valS > valR)
								SAD += valS - valR;
							else
								SAD += valR - valS;*/
							//do whatever you want with your value
						}
					}
					if (SAD == 0)
					{
						cv::Point pt1((h ), (s));
						cv::Point pt2((h  + c), (s+d));
						cv::arrowedLine(res, pt1, pt2, 1, 1, 8, 0, 0.05);
						//break;
					}
					
				}
				/*if (eq)
					break;*/
				//if (SAD == 0)
				//	break;
			}
			//srcBlock.release();
		}
	}
}