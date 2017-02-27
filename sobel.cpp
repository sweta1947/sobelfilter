#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
int main()
{
	int A[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
	int B[3][3] = { { 1, 2, 1 }, { 0,0,0 }, { -1, -2, -1 } };
	int Gx1,Gx2,Gx3, Gy1,Gy2,Gy3;
	int e, f, g;
	int c = 0;
	int d = 0;
	Mat var1 = imread("images.jpg", 1);
	Mat var2(var1.rows, var1.cols, CV_8UC3, Scalar(0, 0, 0));
	for (int i = 0; i < var1.rows; i++)
	{
		var2.at<Vec3b>(i, 0) = var1.at<Vec3b>(i, 0);
		var2.at<Vec3b>(i, var1.cols - 1) = var1.at<Vec3b>(i, var1.cols - 1);

	}
	for (int i = 0; i < var1.cols; i++)
	{
		var2.at<Vec3b>(0, i) = var1.at<Vec3b>(0, i);
		var2.at<Vec3b>(var1.rows - 1, i) = var1.at<Vec3b>(var1.rows - 1, i);

	}
	for (int i = 0; i < var1.rows - 1; i++){
		for (int j = 0; j < var1.cols - 1; j++)
		{
			Gx1 = 0;
			Gx2 = 0;
			Gx3 = 0;
			Gy1= 0;
			Gy2 = 0; Gy3 = 0;
			c = 0;
			for (int m = i; m < var1.rows; m++, c++)
			{
				if (c < 3)
				{
					d = 0;
					for (int n = j; n < var1.cols; n++, d++)
					{
						if (d < 3)
						{
							if ((i + 1) < var1.rows && (j + 1) < var1.cols)
							{
								Gx1+= var1.at<Vec3b>(m, n)[0] * A[m - i][n - j];
								Gx2+= var1.at<Vec3b>(m, n)[1] * A[m - i][n - j];
								Gx3+= var1.at<Vec3b>(m, n)[2] * A[m - i][n - j];
								Gy1 += var1.at<Vec3b>(m, n)[0] * B[m - i][n - j];
								Gy2 += var1.at<Vec3b>(m, n)[1] * B[m - i][n - j];
								Gy3 += var1.at<Vec3b>(m, n)[2] * B[m - i][n - j];
							}
						}
					}
				}
			}
		e=(int)sqrt(Gx1*Gx1 + Gy1*Gy1);
	    f=(int)sqrt(Gx2*Gx2 + Gy2*Gy2);
	    g=(int)sqrt(Gx2*Gx2 + Gy2*Gy2);
		if (e > 255)
			var2.at<Vec3b>(i + 1, j + 1)[0] = 255;
		else
			var2.at<Vec3b>(i + 1, j + 1)[0] = e;
		if (f > 255)
			var2.at<Vec3b>(i + 1, j + 1)[1] = 255;
		else
			var2.at<Vec3b>(i + 1, j + 1)[1] = f;
		if (g> 255)
			var2.at<Vec3b>(i + 1, j + 1)[2] = 255;
		else
		var2.at<Vec3b>(i + 1, j + 1)[2] = g;
		}
	}
	imshow("window1", var1);
	imshow("window2", var2);
	waitKey(0);
	return(0);
}