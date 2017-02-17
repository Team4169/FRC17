#pragma once
#include <vision/VisionPipeline.h>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <C:/Users/Benjamin/wpilib/cpp/current/include/opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <math.h>
#include <NetworkTables/NetworkTable.h>

namespace grip {

/**
* A representation of the different types of blurs that can be used.
*
*/
enum BlurType {
	BOX, GAUSSIAN, MEDIAN, BILATERAL
};
/**
* GripPipeline class.
* 
* An OpenCV pipeline generated by GRIP.
*/
class GripPipeline : public frc::VisionPipeline {
	private:
		cv::Mat hsvThresholdOutput;
		cv::Mat cvDilateOutput;
		cv::Mat cvErodeOutput;
		cv::Mat maskOutput;
		cv::Mat blurOutput;
		cv::Mat desaturateOutput;
		cv::Mat approxPolyOutputMat;
		cv::Mat contoursMat;
		cv::Mat rectanglesMat;
		std::vector<std::vector<cv::Point> > findContoursOutput;
		std::vector<cv::Point> approxPolyOutput;
		std::shared_ptr<NetworkTable> table;
		void hsvThreshold(cv::Mat &, double [], double [], double [], cv::Mat &);
		void cvDilate(cv::Mat &, cv::Mat &, cv::Point &, double , int , cv::Scalar &, cv::Mat &);
		void cvErode(cv::Mat &, cv::Mat &, cv::Point &, double , int , cv::Scalar &, cv::Mat &);
		void mask(cv::Mat &, cv::Mat &, cv::Mat &);
		void blur(cv::Mat &, BlurType &, double , cv::Mat &);
		void desaturate(cv::Mat &, cv::Mat &);
		void findContours(cv::Mat &, bool , std::vector<std::vector<cv::Point> > &);

	public:
		static constexpr double APPROXIMATION_ACCURACY_THRESHOLD = 5.0;
		static constexpr double RECT_W_TO_L_RATIO = 0.4;
		static constexpr double RECT_W_TO_L_RATIO_THRESHOLD = 0.1;

		GripPipeline();
		void Process(cv::Mat& source0);
		cv::Mat* gethsvThresholdOutput();
		cv::Mat* getcvDilateOutput();
		cv::Mat* getcvErodeOutput();
		cv::Mat* getmaskOutput();
		cv::Mat* getblurOutput();
		cv::Mat* getdesaturateOutput();
		cv::Mat* getContoursMat();
		cv::Mat* getApproxPolyOutputMat();
		cv::Mat* getRectanglesMat();
		std::vector<std::vector<cv::Point> >* getfindContoursOutput();
		std::vector<cv::Point>* getApproxPolyOutput();
};


} // end namespace grip


