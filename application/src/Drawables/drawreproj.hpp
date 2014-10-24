#ifndef DRAWREPROJ_HPP
#define DRAWREPROJ_HPP

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#ifndef INC_DRAWABLE
#define INC_DRAWABLE
#include <Drawables/drawable.hpp>
#endif

/// Defines the radius of the clicked point markers (independent of image
///resolution.
#define CIRCLE_RATIO .01
/// Defines the thickness of the lines (independent of image resolution.
#define LINE_RATIO .002

/**
 * @brief Calculate the height/width of a certain object/person.
 * Implementation of Drawable class.
 */
class DrawReproj : public Drawable
{
private:
	/**
	 * @brief Vector to store the points.
	 * Store the four reference points plus the height point.
	 */
	cv::Point2f points[4];

	/**
	 * @brief repoints
	 */
	cv::Point2f repoints[4];

	/**
	 * @brief Number of points inserted so far.
	 */
	int npoints;

	/**
	 * @brief calculated
	 */
	bool calculated;

	/**
	 * @brief persptransf
	 */
	cv::Mat persptransf;

	/**
	 * @brief referential_width
	 */
	double referential_width;

	/**
	 * @brief referential_height
	 */
	double referential_height;

	/**
	 * @brief height
	 */
	double height;

	/**
	 * @brief ratio
	 */
	double ratio;

public:
	DrawReproj();
	~DrawReproj();

	void press(cv::Point);
	void release(cv::Point pi2);
	void draw(cv::Mat& frame);
	void move(cv::Point);
	bool isDone();

	std::string getDescription();
	std::string getIcon();

	bool isCalculated();
	void calcUndistort();
	void undistort(cv::Mat& frame);
};

#endif // DRAWHEIGHT_HPP
