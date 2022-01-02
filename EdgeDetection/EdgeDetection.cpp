#include <iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

using namespace cv;


Mat src,resized_src, src_gray;
Mat dst, detected_edges;

int low_threshold = 0;
const int max_threshold = 255;
const int ratio = 3;
const int kernel_size = 3;
const String window_name = "Edge Map";

int img_width = 480;
int img_height = 640;

String imgPath = <ImgPath>;


void CannyThreshold(int, void*) {
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, low_threshold, low_threshold * ratio, kernel_size);
    dst = Scalar::all(0);
    resized_src.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}

int main(int argc, char** argv)
{
    src = imread(imgPath, IMREAD_COLOR); // Load an image
    if (src.empty())
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }

    resize(src, resized_src, Size(img_height, img_width), INTER_LINEAR);//Resizing Image 

    dst.create(resized_src.size(), src.type());
    cvtColor(resized_src, src_gray, COLOR_BGR2GRAY); //Convert Image to Gray

    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold:", window_name,&low_threshold, max_threshold, CannyThreshold);

    CannyThreshold(0, 0);
    waitKey(0);
    return 0;
}

