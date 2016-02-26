#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<string>
#include<iostream>

// fn: add salt noise
void salt(cv::Mat &img, cv::Mat &result_img, int n) {
	int i, j;
	//result_img.create(img.rows, img.cols, img.type());
	result_img = img.clone();
	for (int k = 0; k < n; k++) {
		i = rand() % result_img.cols;
		j = rand() % result_img.rows;
		if (result_img.channels() == 1) { // gray-level image
			result_img.at<uchar>(j, i) = 255;
		}
		else if (result_img.channels() == 3) { // color image
			result_img.at<cv::Vec3b>(j, i)[0] = 255;
			result_img.at<cv::Vec3b>(j, i)[1] = 255;
			result_img.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}

int main() {
	std::string
		str_winName = "Image";
	cv::Mat img = cv::imread("Images/boldt.jpg");
	cv::Mat result_img;
	salt(img, result_img, 3000);

	cv::namedWindow(str_winName);
	cv::imshow(str_winName, result_img);
	cv::waitKey(0);
	return 1;
}
