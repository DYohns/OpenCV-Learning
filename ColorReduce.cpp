#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<string>

// fn: color reduce
void ColorReduce(cv::Mat &img, cv::Mat &result_img, int div = 64) {
	result_img.create(img.rows, img.cols, img.type());

	int nl = img.rows; // number of lines				   
	int nc = img.cols * img.channels(); // total number of elements per line

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round pixel value
	uchar mask = 0xFF << n;

	for (int j = 0; j < nl; j++) {
		// get jth first address
		uchar* data_img = img.ptr<uchar>(j);
		uchar* data_ri = result_img.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {

			// process each pixel
			data_ri[i] = (data_img[i] & mask) + div / 2;
			//data[i] = data[i] / div * div + div / 2;
		}
	}
}

int main() {
	std::string str_winName = "Image";
	cv::Mat img = cv::imread("Images/boldt.jpg");
	cv::Mat result_img;
	ColorReduce(img, result_img);
	cv::namedWindow(str_winName);
	cv::imshow(str_winName, result_img);
	cv::waitKey(0);
	return 1;
}
