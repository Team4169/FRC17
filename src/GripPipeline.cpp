#include "GripPipeline.h"
#include "Robot.h"
#include <math.h>
/**
* Initializes a GripPipeline.
*/

namespace grip {

GripPipeline::GripPipeline() {
	table = NetworkTable::GetTable("Vision_Info");
}
/**
* Runs an iteration of the Pipeline and updates outputs.
*
* Sources need to be set before calling this method.
*
*/
void GripPipeline::Process(cv::Mat& source0){
	SmartDashboard::PutNumber("Vision Processing", 1);
	//Step HSV_Threshold0:
	//input
	//Replace HSV with RGB. Red 45-54 (49 actual value), Green 255, Blue 0?
	cv::Mat hsvThresholdInput = source0;
	double hsvThresholdHue[] = {70.0, 90.0};
	double hsvThresholdSaturation[] = {10.0, 255.0};
	double hsvThresholdValue[] = {30.0, 255.0};
	hsvThreshold(hsvThresholdInput, hsvThresholdHue, hsvThresholdSaturation, hsvThresholdValue, this->hsvThresholdOutput);
	//Step CV_dilate0:
	//input
	SmartDashboard::PutNumber("Vision Processing", 2);
	cv::Mat cvDilateSrc = hsvThresholdOutput;
	cv::Mat cvDilateKernel;
	cv::Point cvDilateAnchor(-1, -1);
	double cvDilateIterations = 1.0;  // default Double
    int cvDilateBordertype = cv::BORDER_CONSTANT;
	cv::Scalar cvDilateBordervalue(-1);
	cvDilate(cvDilateSrc, cvDilateKernel, cvDilateAnchor, cvDilateIterations, cvDilateBordertype, cvDilateBordervalue, this->cvDilateOutput);
	//Step CV_erode0:
	//input
	SmartDashboard::PutNumber("Vision Processing", 3);
	cv::Mat cvErodeSrc = cvDilateOutput;
	cv::Mat cvErodeKernel;
	cv::Point cvErodeAnchor(-1, -1);
	double cvErodeIterations = 1.0;  // default Double
    int cvErodeBordertype = cv::BORDER_CONSTANT;
	cv::Scalar cvErodeBordervalue(-1);
	cvErode(cvErodeSrc, cvErodeKernel, cvErodeAnchor, cvErodeIterations, cvErodeBordertype, cvErodeBordervalue, this->cvErodeOutput);
	//Step Mask0:
	SmartDashboard::PutNumber("Vision Processing", 4);
	//input
	//cv::Mat maskInput = source0;
	//cv::Mat maskMask = cvErodeOutput;
	//mask(maskInput, maskMask, this->maskOutput);
	//Step Blur0:
	//input
	cv::Mat blurInput = cvErodeOutput;
	BlurType blurType = BlurType::BOX;
	double blurRadius = 1.8018018018018018;  // default Double
	blur(blurInput, blurType, blurRadius, this->blurOutput);
	SmartDashboard::PutNumber("Vision Processing", 5);
	//Step Desaturate0:
	//input
	cv::Mat desaturateInput = blurOutput;
	desaturate(desaturateInput, this->desaturateOutput);
	SmartDashboard::PutNumber("Vision Processing", 6);
	//Step Find_Contours0:
	//input
	cv::Mat findContoursInput = desaturateOutput;
	//bool findContoursExternalOnly = false;  // default Boolean
	std::vector<cv::Vec4i> hierarchy;
	int mode = cv::RETR_EXTERNAL;
	int method = cv::CHAIN_APPROX_SIMPLE;
	cv::findContours(desaturateOutput, this->findContoursOutput, hierarchy, mode, method);
	SmartDashboard::PutNumber("Vision Processing", 7);
	contoursMat = cv::Mat::zeros(desaturateOutput.size(), CV_8UC3 );
	rectanglesMat = cv::Mat::zeros(desaturateOutput.size(), CV_8UC3);
	cv::Rect largestRectangles[2] = {cv::Rect(), cv::Rect()};
	int largestRectsIndex[2] = {-1, -1};
	//finds and stores the bounding rects of the largest 2 contours
	SmartDashboard::PutNumber("Vision Processing", 8);

	int size = (signed int)findContoursOutput.size();

	if(size<2){
		table->PutNumber("DistanceX", -1);
		table->PutString("DirectionString", NULL);
		return;
	}

	for(int j=0;j<2;j++){
		int currentContourIndex = -2;
		double area = 0;
		for(int i = 0; i<size; i++){
		   if(area < cv::contourArea(findContoursOutput[i]) && largestRectsIndex[0] != i){
			   double lwratio = ((double)(boundingRect(findContoursOutput[i]).width))/((double)(boundingRect(findContoursOutput[i]).height));
			   	if(lwratio < RECT_W_TO_L_RATIO + RECT_W_TO_L_RATIO_THRESHOLD && lwratio > RECT_W_TO_L_RATIO - RECT_W_TO_L_RATIO_THRESHOLD){
			   		area = cv::contourArea(findContoursOutput[i]);
			   	    currentContourIndex = i;
			   	}
		   }

	     }
		largestRectsIndex[j] = currentContourIndex;
		if(currentContourIndex > -1)
			largestRectangles[j] = boundingRect(findContoursOutput[currentContourIndex]);
	}


	//draws the rectangles around the largest 2 contours if their sides match a certain ratio
	//plus or minus a given threshold for error


	for(int i=0;i<2;i++){
		cv::Scalar color = cv::Scalar(255, 255, 255);
		cv::rectangle(rectanglesMat, largestRectangles[i], color, 1, 8, 0);
	}
	SmartDashboard::PutNumber("Vision Processing", 9);

	//write something to check gyro angle and adjust the angle to the nearest of the three possible angles

	//top-left of Rect is (x, y)
	//center of image = 320/2
		try{
		int centerX = Robot::CAMERA_IMG_WIDTH/2;

		int Rect0DistanceFromCenter = abs(centerX-(largestRectangles[0].x+largestRectangles[0].width/2));
		int Rect1DistanceFromCenter = abs(centerX-(largestRectangles[1].x+largestRectangles[1].width/2));
		double distanceX = ((double)Rect0DistanceFromCenter + (double)Rect1DistanceFromCenter)/2;

		int angle = 0;
		if(Rect0DistanceFromCenter > Rect1DistanceFromCenter){
			if(largestRectangles[0].x > centerX){
				//move right
				angle = 0;
			}else{
				//move left
				angle = 180;
			}
		}else{
			if(largestRectangles[1].x > centerX){
				//move right
				angle = 0;
			}else{
				//move left
				angle = 180;
			}
		}

		table->PutNumber("DistanceX", distanceX);
		table->PutNumber("Direction", angle);
		if(angle == 0){
			table->PutString("DirectionString", "Right");
		}else if(angle == 180){
			table->PutString("DirectionString", "Left");
		}
		//calculate approximate y distance and then math it to magnitude and direction
		}catch(std::exception e){
			DriverStation::ReportError(e.what());
		}


}


/**
 * This method is a generated setter for source0.
 * @param source the Mat to set
 */
/*void GripPipeline::setsource0(cv::Mat &source0){
	source0.copyTo(this->source0);
}*/
/**
 * This method is a generated getter for the output of a HSV_Threshold.
 * @return Mat output from HSV_Threshold.
 */
cv::Mat* GripPipeline::gethsvThresholdOutput(){
	return &(this->hsvThresholdOutput);
}
/**
 * This method is a generated getter for the output of a CV_dilate.
 * @return Mat output from CV_dilate.
 */
cv::Mat* GripPipeline::getcvDilateOutput(){
	return &(this->cvDilateOutput);
}
/**
 * This method is a generated getter for the output of a CV_erode.
 * @return Mat output from CV_erode.
 */
cv::Mat* GripPipeline::getcvErodeOutput(){
	return &(this->cvErodeOutput);
}
/**
 * This method is a generated getter for the output of a Mask.
 * @return Mat output from Mask.
 */
cv::Mat* GripPipeline::getmaskOutput(){
	return &(this->maskOutput);
}
/**
 * This method is a generated getter for the output of a Blur.
 * @return Mat output from Blur.
 */
cv::Mat* GripPipeline::getblurOutput(){
	return &(this->blurOutput);
}
/**
 * This method is a generated getter for the output of a Desaturate.
 * @return Mat output from Desaturate.
 */
cv::Mat* GripPipeline::getdesaturateOutput(){
	return &(this->desaturateOutput);
}
/**
 * This method is a generated getter for the output of a Find_Contours.
 * @return ContoursReport output from Find_Contours.
 */
std::vector<std::vector<cv::Point> >* GripPipeline::getfindContoursOutput(){
	return &(this->findContoursOutput);
}
std::vector<cv::Point>* GripPipeline::getApproxPolyOutput(){
	return &(this->approxPolyOutput);
}

cv::Mat* GripPipeline::getApproxPolyOutputMat(){
	return &(this->approxPolyOutputMat);
}

cv::Mat* GripPipeline::getContoursMat(){
	return &(this->contoursMat);
}

cv::Mat* GripPipeline::getRectanglesMat(){
	return &(this->rectanglesMat);
}
	/**
	 * Segment an image based on hue, saturation, and value ranges.
	 *
	 * @param input The image on which to perform the HSL threshold.
	 * @param hue The min and max hue.
	 * @param sat The min and max saturation.
	 * @param val The min and max value.
	 * @param output The image in which to store the output.
	 */
	void GripPipeline::hsvThreshold(cv::Mat &input, double hue[], double sat[], double val[], cv::Mat &out) {
		cv::cvtColor(input, out, cv::COLOR_BGR2HSV);
		cv::inRange(out,cv::Scalar(hue[0], sat[0], val[0]), cv::Scalar(hue[1], sat[1], val[1]), out);
	}

	/**
	 * Expands area of higher value in an image.
	 * @param src the Image to dilate.
	 * @param kernel the kernel for dilation.
	 * @param anchor the center of the kernel.
	 * @param iterations the number of times to perform the dilation.
	 * @param borderType pixel extrapolation method.
	 * @param borderValue value to be used for a constant border.
	 * @param dst Output Image.
	 */
	void GripPipeline::cvDilate(cv::Mat &src, cv::Mat &kernel, cv::Point &anchor, double iterations, int borderType, cv::Scalar &borderValue, cv::Mat &dst) {
		cv::dilate(src, dst, kernel, anchor, (int)iterations, borderType, borderValue);
	}

	/**
	 * Expands area of lower value in an image.
	 * @param src the Image to erode.
	 * @param kernel the kernel for erosion.
	 * @param anchor the center of the kernel.
	 * @param iterations the number of times to perform the erosion.
	 * @param borderType pixel extrapolation method.
	 * @param borderValue value to be used for a constant border.
	 * @param dst Output Image.
	 */
	void GripPipeline::cvErode(cv::Mat &src, cv::Mat &kernel, cv::Point &anchor, double iterations, int borderType, cv::Scalar &borderValue, cv::Mat &dst) {
		cv::erode(src, dst, kernel, anchor, (int)iterations, borderType, borderValue);
	}

		/**
		 * Filter out an area of an image using a binary mask.
		 *
		 * @param input The image on which the mask filters.
		 * @param mask The binary image that is used to filter.
		 * @param output The image in which to store the output.
		 */
		void GripPipeline::mask(cv::Mat &input, cv::Mat &mask, cv::Mat &output) {
			mask.convertTo(mask, CV_8UC1);
			cv::bitwise_xor(output, output, output);
			input.copyTo(output, mask);
		}

	/**
	 * Softens an image using one of several filters.
	 *
	 * @param input The image on which to perform the blur.
	 * @param type The blurType to perform.
	 * @param doubleRadius The radius for the blur.
	 * @param output The image in which to store the output.
	 */
	void GripPipeline::blur(cv::Mat &input, BlurType &type, double doubleRadius, cv::Mat &output) {
		int radius = (int)(doubleRadius + 0.5);
		int kernelSize;
		switch(type) {
			case BOX:
				kernelSize = 2 * radius + 1;
				cv::blur(input,output,cv::Size(kernelSize, kernelSize));
				break;
			case GAUSSIAN:
				kernelSize = 6 * radius + 1;
				cv::GaussianBlur(input, output, cv::Size(kernelSize, kernelSize), radius);
				break;
			case MEDIAN:
				kernelSize = 2 * radius + 1;
				cv::medianBlur(input, output, kernelSize);
				break;
			case BILATERAL:
				cv::bilateralFilter(input, output, -1, radius, radius);
				break;
        }
	}
	/**
	 * Converts a color image into shades of grey.
	 *
	 * @param input The image on which to perform the desaturate.
	 * @param output The image in which to store the output.
	 */
	void GripPipeline::desaturate(cv::Mat &input, cv::Mat &output) {
		switch (input.channels()) {
			case 1:
				// If the input is already one channel, it's already desaturated
				input.copyTo(output);
				break;
			case 3:
				cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
				break;
			case 4:
				cv::cvtColor(input, output, cv::COLOR_BGRA2GRAY);
				break;
			default:
				throw "Input to desaturate must have 1, 3, or 4 channels";
		}
	}

	/**
	 * Finds contours in an image.
	 *
	 * @param input The image to find contours in.
	 * @param externalOnly if only external contours are to be found.
	 * @param contours vector of contours to put contours in.
	 */
	void GripPipeline::findContours(cv::Mat &input, bool externalOnly, std::vector<std::vector<cv::Point> > &contours) {
		std::vector<cv::Vec4i> hierarchy;
		contours.clear();
		int mode = externalOnly ? cv::RETR_EXTERNAL : cv::RETR_LIST;
		int method = cv::CHAIN_APPROX_SIMPLE;
		cv::findContours(input, contours, hierarchy, mode, method);
	}



} // end grip namespace

