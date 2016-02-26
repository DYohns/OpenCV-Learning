#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/*
 fn: sharpen image
 using filter2D
*/
void sharpen2D(const cv::Mat &image, cv::Mat &result) {

	// Construct kernel (all entries initialized to 0)
	cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
	// assigns kernel values
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;

	//filter the image
	cv::filter2D(image, result, image.depth(), kernel);
}

int main()
{
	cv::Mat image = cv::imread("Images/boldt.jpg", 0);
	if (!image.data)
		return 0;

	cv::Mat result;
	result.create(image.size(), image.type());

	double time;
	image = cv::imread("Images/boldt.jpg", 0);
	time = static_cast<double>(cv::getTickCount());
	sharpen2D(image, result);
	time = (static_cast<double>(cv::getTickCount()) - time) / cv::getTickFrequency();
	std::cout << "time 2D= " << time << std::endl;

	cv::namedWindow("Image 2D");
	cv::imshow("Image 2D", result);

	cv::waitKey();

	return 0;
}


