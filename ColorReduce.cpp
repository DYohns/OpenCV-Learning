#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<string>
#include<iostream>
/*
 fn: color reduce
 using .ptr and * ++ and bitwise (continuous+channels)
*/
void ColorReduce(cv::Mat &image, int div = 64) {

	int nl = image.rows; // number of lines
	int nc = image.cols; // number of columns

	if (image.isContinuous()) {
		// then no padded pixels
		nc = nc*nl;
		nl = 1;  // it is now a 1D array
	}

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// process each pixel ---------------------

			*data++ = *data&mask + div / 2;
			*data++ = *data&mask + div / 2;
			*data++ = *data&mask + div / 2;

			// end of pixel processing ----------------

		} // end of line                   
	}
}

int main() {
	std::string str_winName = "Image";
	cv::Mat image = cv::imread("Images/boldt.jpg");

	double duration;
	duration = static_cast<double>(cv::getTickCount());

	ColorReduce(image);

	duration = static_cast<double>(cv::getTickCount()) - duration;
	duration /= cv::getTickFrequency();
	std::cout << duration << std::endl;

	cv::namedWindow(str_winName);
	cv::imshow(str_winName, image);
	cv::waitKey(0);
	return 1;
}
