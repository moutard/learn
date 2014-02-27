/**
 * file Smoothing.cpp
 * brief Sample code for simple filters
 * author OpenCV team
 */
#include <iostream>
#include <vector>
#include <math.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"

#include "transfert.h"
using namespace std;
using namespace cv;

/**
 * RGB -> LMS
 */
inline float rgbToL(const uchar red, const uchar green, const uchar blue)
{
  float a11 = 0.3811f;
  float a12 = 0.5783f;
  float a13 = 0.0402f;
  return ((a11 * red) + (a12 * green) + (a13 * blue));
};
inline float rgbToM(const uchar red, const uchar green, const uchar blue)
{
  float a21 = 0.1967f;
  float a22 = 0.7244f;
  float a23 = 0.0782f;
  return ((a21 * red) + (a22 * green) + (a23 * blue));
};
inline float rgbToS(const uchar red, const uchar green, const uchar blue)
{
  float a31 = 0.0241f;
  float a32 = 0.1288f;
  float a33 = 0.8444f;
  return ((a31 * red) + (a32 * green) + (a33 * blue));
};

/**
 * LMS -> lambdaAlphaBetha
 */
inline float lmsToLambda(const float l, const float m, const float s)
{
  float coeff = 0.5773f; // 1/sqrt(3)
  return coeff * (l + m + s);
};
inline float lmsToAlpha(const float l, const float m, const float s)
{
  float coeff = 0.4082; // 1/sqrt(6)
  return coeff * (l + m - 2*s);
};
inline float lmsToBetha(const float l, const float m, const float s)
{
  float coeff = 0.7071; // 1/sqrt(2)
  return coeff * (l - m);
};

/**
 * Reverse
 *
 * lambdaAlphaBetha -> LMS
 */
inline float labToL(const float l, const float a, const float b)
{
  float coeff1 = 0.5773f; // sqrt(3)/3
  float coeff2 = 0.4082f; // sqrt(6)/6
  float coeff3 = 0.7071f; // sqrt(2)/2
  return (coeff1*l + coeff2*a + coeff3*b);
};
inline float labToM(const float l, const float a, const float b)
{
  float coeff1 = 0.5773f; // sqrt(3)/3
  float coeff2 = 0.4082f; // sqrt(6)/6
  float coeff3 = 0.7071f; // sqrt(2)/2
  return (coeff1*l + coeff2*a - coeff3*b);
};
inline float labToS(const float l, const float a, const float b)
{
  float coeff1 = 0.5773f; // sqrt(3)/3
  float coeff2 = 0.4082f; // sqrt(6)/6
  float coeff3 = 0.7071f; // sqrt(2)/2
  return (coeff1*l -  2*coeff2*a);
};

/**
 * LMS -> RGB
 */
inline float lmsToR(const float l, const float m, const float s)
{
  float a11 = 4.4679f;
  float a12 = 3.5873f;
  float a13 = 0.1193f;
  return ((a11 * l) - (a12 * m) + (a13 * s));
};
inline float lmsToG(const float l, const float m, const float s)
{
  float a21 = -1.2186f;
  float a22 = 2.3809f;
  float a23 = 0.1624f;
  return ((a21 * l) + (a22 * m) - (a23 * s));
};
inline float lmsToB(const float l, const float m, const float s)
{
  float a31 = 0.0497f;
  float a32 = 0.2439f;
  float a33 = 1.2045f;
  return ((a31 * l) - (a32 * m) + (a33 * s));
};

/**
 * oSrc : image you want to change.
 * oClr: image used to extract color.
 * oDst: an image that will contains the result.
 */
void SwitchColor(Mat& oSrc, Mat& oClr, Mat& oDst)
{
    // accept only char type matrices
    CV_Assert(oSrc.depth() != sizeof(uchar));
    Mat oSrcLabels, oClrLabels;
    const int K = 3;
    mykmean(oSrc, oSrcLabels, K);
    mykmean(oClr, oClrLabels, K);

     const int channels = oSrc.channels();
    if (channels == 3)
    {
      // Create a LAB matrix.
      Mat oSrcLAB = Mat::zeros(oSrc.rows, oSrc.cols, CV_64FC3);
      Mat oClrLAB = Mat::zeros(oSrc.rows, oSrc.cols, CV_64FC3);

      // Vec3b -> 3 channels of uchar.
      MatIterator_<Vec3b> itSrc, endSrc, itClr, endClr;
      MatIterator_<Vec3b> itDst, endDst;
      // Vec3d -> 3 channels of float.
      MatIterator_<Vec3d> itlab, endlab;
      MatIterator_<Vec3d> itClrlab, endClrlab;

      // oSrc -> LMS -> LAB
      itlab = oSrcLAB.begin<Vec3d>();
      for (itSrc = oSrc.begin<Vec3b>(), endSrc = oSrc.end<Vec3b>(); itSrc != endSrc; ++itSrc)
      {
          // Stored in BGR not RGB !
          uchar b = (*itSrc)[0];
          uchar g = (*itSrc)[1];
          uchar r = (*itSrc)[2];
          float L = log( 1 + rgbToL(r, g, b) );
          float M = log( 1 + rgbToM(r, g, b) );
          float S = log( 1 + rgbToS(r, g, b) );
          (*itlab)[0] = lmsToLambda(L, M, S);
          (*itlab)[1] = lmsToAlpha( L, M, S);
          (*itlab)[2] = lmsToBetha( L, M, S);
          ++itlab;
      }
      // oClr -> LMS -> LAB
      itClrlab = oClrLAB.begin<Vec3d>();
      for ( itClr = oClr.begin<Vec3b>(), endClr = oClr.end<Vec3b>(); itClr != endClr; ++itClr)
      {
          uchar b = (*itClr)[0];
          uchar g = (*itClr)[1];
          uchar r = (*itClr)[2];

          float L = log( 1 + rgbToL(r, g, b) );
          float M = log( 1 + rgbToM(r, g, b) );
          float S = log( 1 + rgbToS(r, g, b) );
          (*itClrlab)[0] = lmsToLambda(L, M, S);
          (*itClrlab)[1] = lmsToAlpha( L, M, S);
          (*itClrlab)[2] = lmsToBetha( L, M, S);
          ++itClrlab;
      }

      // For the source: Compute the mean and standard deviation for each cluster.
      vector<Scalar> clustersMeanSrc, clustersStdDevSrc;
      clustersMeanSrc.reserve(K), clustersStdDevSrc.reserve(K);
      for (unsigned int i = 0; i < K; i++) {
        Mat maskClusterSrc = oSrcLabels.clone(); // clone constructor.
        MatIterator_<Vec3b> it, end;
        for (it = maskClusterSrc.begin<Vec3b>(); it != maskClusterSrc.end<Vec3b>(); ++it) {
            (*it)[0] = ((*it)[0] == i) ? 1 : 0;
        }
        meanStdDev(oSrcLAB, clustersMeanSrc[i], clustersStdDevSrc[i], maskClusterSrc);
      }

      // For the color: Compute the mean and standard deviation for eah cluster.
      vector<Scalar> clustersMeanClr, clustersStdDevClr;
      clustersMeanClr.reserve(K), clustersStdDevClr.reserve(K);
      for (unsigned int i = 0; i < K; i++) {
        Mat maskClusterClr = oClrLabels.clone(); // clone constructor.
        MatIterator_<Vec3b> it, end;
        for (it = maskClusterClr.begin<Vec3b>(); it != maskClusterClr.end<Vec3b>(); ++it) {
            (*it)[0] = ((*it)[0] == i) ? 1 : 0;
        }
        meanStdDev(oClrLAB, clustersMeanClr[i], clustersStdDevClr[i], maskClusterClr);
      }

      // Compute average and standard derivation for oSrc and oClr
      Scalar meanSrc, stdDevSrc, meanClr, stdDevClr;
      meanStdDev(oSrcLAB, meanSrc, stdDevSrc);
      cout << "Source mean LAB: " << meanSrc[0] << " " << meanSrc[1] << " " << meanSrc[2] << endl;
      cout << "Source stdDev LAB: " << stdDevSrc[0] << " " << stdDevSrc[1] << " " << stdDevSrc[2] << endl;

      meanStdDev(oClrLAB, meanClr, stdDevClr);
      cout << "Color mean LAB: " << meanClr[0] << " " << meanClr[1] << " " << meanClr[2] << endl;
      cout << "Color stdDev LAB: " << stdDevClr[0] << " " << stdDevClr[1] << " " << stdDevClr[2] << endl;

      float x = (stdDevClr[0] / stdDevSrc[0]);
      float y = (stdDevClr[1] / stdDevSrc[1]);
      float z = (stdDevClr[2] / stdDevSrc[2]);

      for (itlab = oSrcLAB.begin<Vec3d>(), endlab = oSrcLAB.end<Vec3d>(); itlab != endlab; ++itlab)
      {
        (*itlab)[0] = x*((*itlab)[0] - meanSrc[0]) + meanClr[0];
        (*itlab)[1] = y*((*itlab)[1] - meanSrc[1]) + meanClr[1];
        (*itlab)[2] = z*((*itlab)[2] - meanSrc[2]) + meanClr[2];
      }
      // Reverse
      // LAB -> LMS -> oDst
      itDst = oDst.begin<Vec3b>();
      for (itlab = oSrcLAB.begin<Vec3d>(), endlab = oSrcLAB.end<Vec3d>(); itlab != endlab; ++itlab)
      {
          float l = (*itlab)[0];
          float a = (*itlab)[1];
          float b = (*itlab)[2];
          float L = exp( labToL(l, a, b) ) - 1;
          float M = exp( labToM(l, a, b) ) - 1;
          float S = exp( labToS(l, a, b) ) - 1;
          (*itDst)[2] = (uchar)lmsToR(L, M, S);
          (*itDst)[1] = (uchar)lmsToG(L, M, S);
          (*itDst)[0] = (uchar)lmsToB(L, M, S);
          ++itDst;
      }
    }
};

int mykmean(Mat& img, Mat& _labels, const int k)
{
    std::vector<cv::Mat> imgRGB;
    cv::split(img, imgRGB);
    int n = img.rows * img.cols;
    cv::Mat img3xN(n, 3, CV_8U);
    for (int i = 0; i != 3; ++i)
    {
      imgRGB[i].reshape(1, n).copyTo(img3xN.col(i));
    }
    img3xN.convertTo(img3xN, CV_32F);
    cv::kmeans(img3xN, k, _labels, cv::TermCriteria(), 10, cv::KMEANS_RANDOM_CENTERS);
    _labels = _labels.reshape(0, img.rows);

    return k;
};

int displayLabels(const Mat & _labels, int k)
{
  Mat imgLabels;
  cv::convertScaleAbs(_labels, imgLabels, int(255/k));
  cv::imshow("result", imgLabels);
  waitKey(0);
};
