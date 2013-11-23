/*
 * This framework should comprehend all the libs needed for the program
 * to function.
 */

// Window definitions
#define WIN_FLAGS CV_WINDOW_KEEPRATIO | CV_WINDOW_NORMAL | CV_GUI_EXPANDED

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

// IOStream
#ifndef IOSTREAM_INC
#define IOSTREAM_INC
#include <iostream>
#endif

// Framework headers
#include "Video/Video.hpp"
#include "Frame/Frame.hpp"
#include "Snapshot/Snapshot.hpp"
#include "Event/Event.hpp"
#include "Individual/Individual.hpp"
#include "Feature/Feature.hpp"

std::string parseArguments(int argc, char ** argv);