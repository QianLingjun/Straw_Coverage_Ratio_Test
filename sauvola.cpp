#include <cxcore.h>
#include <cv.h>
#include <highgui.h>

void slide_window_mean(IplImage * pGrayImage, int * meanMat, const int radius)
{
	const int height=pGrayImage->height;
	const int width=pGrayImage->width;
	const int widthStep=pGrayImage->widthStep;
	uchar * pImageData=(uchar *)pGrayImage->imageData;

	int i=0, j=0;
	int a=0, t=0;
	int a0=0, t0=0;
	int b=0;
	int m=0, n=0;
	int m1=0, m2=0;
	int n1=0, n2=0;

	for(i=0; i<height; ++i)
	{ 
		a=0;
		t=0;
		m1 = i<radius ? -i : -radius; 
		m2 = i<height-radius ? radius : height-i-1;

		for(j=0; j<width; ++j)
		{
			n1 = j<radius ? -j : -radius; 
			n2 = j<width-radius ? radius : width-j-1;

			if(j == 0)
			{
				if(i == 0)
				{
					a = 0; t = 0;

					for(m=m1; m<=m2; ++m)
					{
						for(n=n1; n<=n2; ++n)
						{
							a += pImageData[(i+m)*widthStep+j+n];
						}
					}

					t = (n2-n1+1)*(m2-m1+1);

					a0 = a;
					t0 = t;

				}
				else if(i <= radius)
				{
					b = 0;
					for(n=n1; n<=n2; n++)
					{
						b += pImageData[(i+radius)*widthStep + j+n];
					}

					t0 += (radius+1);
					a0 += b;
					a = a0;
					t = t0;
				}
				else if(i > height-radius-1)
				{
					b = 0;
					for(n=n1; n<=n2; n++)
					{
						b += pImageData[(i-radius-1)*widthStep + j+n];
					}

					t0 -= (radius+1);
					a0 -= b;
					a = a0;
					t = t0;

				}
				else
				{
					b = 0;
					for(n=n1; n<=n2; n++)
					{
						b += pImageData[(i-radius-1)*widthStep + j+n];
					}
					a0 -= b;

					b = 0;
					for(n=n1; n<=n2; n++)
					{
						b += pImageData[(i+radius)*widthStep + j+n];
					}
					a0 += b;

					a = a0;
					t = t0;
				}
			}
			else if(j <= radius)
			{
				b = 0;
				for(m=m1; m<=m2; m++)
				{
					b += pImageData[(i+m)*widthStep + j+radius];
				}

				a += b;
				t += (m2-m1+1);

			}
			else if(j > width-radius-1)
			{
				b = 0;
				for(m=m1; m<=m2; m++)
				{
					b += pImageData[(i+m)*widthStep + j-radius-1];
				}

				a -= b;
				t -= (m2-m1+1);

			}
			else
			{
				b = 0;
				for(m=m1; m<=m2; ++m)
				{
					b += pImageData[(i+m)*widthStep + j-radius-1];
				}
				a -= b;

				b = 0;
				for(m=m1; m<=m2; m++)
				{
					b += pImageData[(i+m)*widthStep + j+radius];
				}
				a += b;
			}

			meanMat[i*width+j]=(int)round((double)a/t);
		}
	}
}

void slide_window_variance(IplImage * pGrayImage, int * meanMat, float * varMat, 
						   const int radius)
{
	const int height=pGrayImage->height;
	const int width=pGrayImage->width;
	const int widthStep=pGrayImage->widthStep;
	uchar * pGrayData=(uchar *)pGrayImage->imageData;

	int t=0;
	float var=0;

	for (int i=0; i<height; ++i)
	{
		for(int j=0; j<width; ++j)
		{
			var=0;
			t=0;

			for(int m=-radius; m<=radius; ++m)
			{
				for(int n=-radius;n<=radius; ++n)
				{
					if(!(i+m>=0 && i+m<height && j+n>=0 && j+n<width)) continue;

					var+=powf(pGrayData[(i+m)*widthStep+j+n]-meanMat[i*width+j], 2);
					++t;
				}
			}

			varMat[i*width+j] = sqrtf(var/(t-1));
		}
	}
}

void sauvola_binarize(IplImage * pGrayImg, IplImage * pBinImg, const int W, 
					  const float K, const float R)
{
	const int height=pGrayImg->height;
	const int width=pGrayImg->width;
	const int widthStep=pGrayImg->widthStep;

	uchar * pGrayData = (uchar *)pGrayImg->imageData;
	uchar * pBinData = (uchar *)pBinImg->imageData;

	const int size=height*width;
	int * meanMat=new int[size];
	memset(meanMat, 0, sizeof(int)*size);
	float * varMat=new float[size];
	memset(varMat, 0, sizeof(float)*size);

	slide_window_mean(pGrayImg, meanMat, W);
	slide_window_variance(pGrayImg, meanMat, varMat, W);

	int i=0, j=0;
	int T=0;
	int * pMeanMat=NULL;
	float * pVarMat=NULL;
	uchar * pTempData=NULL;
	uchar * pTempData2=NULL;

	for(i=0; i<height; ++i)
	{
		pMeanMat=meanMat+i*width;
		pVarMat=varMat+i*width;
		pTempData=pGrayData+i*widthStep;
		pTempData2=pBinData+i*widthStep;

		for(j=0; j<width; ++j)
		{
			T=(int)(pMeanMat[j]*(1+K*(pVarMat[j]/R-1)));
			pTempData2[j] = pTempData[j]<T?0:255;
		}
	}

	delete [] meanMat;
	delete [] varMat;
}
