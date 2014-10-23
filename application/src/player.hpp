#ifndef PLAYER_HPP
#define PLAYER_HPP

#ifndef INC_DRAWABLE
#define INC_DRAWABLE
#include <Drawables/drawable.hpp>
#endif

// OpenCV
#ifndef OPENCV_INC
#define OPENCV_INC
#include <opencv2/opencv.hpp>
#endif

#include <QSharedPointer>

class Frame;
/**
 * @brief FramePtr
 */
typedef QSharedPointer<Frame> FramePtr;

class Player;
/**
 * @brief PlayerPtr
 */
typedef QSharedPointer<Player> PlayerPtr;

/**
 * @brief Interface for VideoPlayer.
 * The Player class functions as a purelly virtual class intended to
 * make a single interface for reading frames and getting data from both Video
 * and Event, and actually anything else that comes after.
 */
class Player
{
public:
	// Capture functions
	/**
	 * @brief Checks whether the capture interface is valid or not.
	 * @return Whether the capture interface is valid or not.
	 */
	virtual bool check_cap() = 0;

	/**
	 * @brief Jumps the Player to the given frameNum.
	 * @param frameNum Number of the frame to jump to.
	 * @return Whether the provided frameNum was valid (in bounds).
	 */
	virtual bool setFramePos(double frameNum) = 0;

	/**
	 * @brief Gets the current position of Player.
	 * @return Current frame number.
	 */
	virtual double getFramePos() = 0;

	/**
	 * @brief Gets the next frame available in the Player.
	 * @param frame of the cv::Mat object where to put the read
	 * frame.
	 * @return Wheather the Player was successful into fetching the new frame.
	 */
	virtual bool getFrame(cv::Mat &frame) = 0;

	/**
	 * @brief Gets the next frame available in the Player.
	 * @param frame Reference of the cv::Mat object where to put the read
	 * frame.
	 * @return Wheather the Player was successful into fetching the new frame.
	 */
	virtual bool getNextFrame(cv::Mat &frame) = 0;

	/**
	 * @brief Gets the previous frame available in the Player.
	 * @param frame Reference of the cv::Mat object where to put the read frame.
	 * @return Wheather the Player was successful into fetching the new frame.
	 */
	virtual bool getPrevFrame(cv::Mat &frame) = 0;

	/**
	 * @brief stepForward
	 * @return
	 */
	virtual bool stepForward() = 0;

	/**
	 * @brief stepBackwards
	 * @return
	 */
	virtual bool stepBackwards() = 0;

	// Properties
	/**
	 * @brief Gets the interval between frames in seconds.
	 * @return Interval between frames in seconds.
	 */
	virtual double getFrameInt() = 0;

	/**
	 * @brief Gets the frame per second count.
	 * @return FPS.
	 */
	virtual double getFPS() = 0;

	/**
	 * @brief Gets the length of the video in seconds.
	 * @return Length of the video in seconds.
	 */
	virtual double getLengthTime() = 0;

	/**
	 * @brief Gets the length of the video in frames.
	 * @return Length of the video in frames.
	 */
	virtual double getLengthFrames() = 0;

	/**
	 * @brief getCurrentFrameRef
	 * @return
	 */
	virtual FramePtr getCurrentFrameRef() = 0;

	/**
	 * @brief getCurrentFrameNumber
	 * @return
	 */
	virtual unsigned int getCurrentFrameNumber() = 0;

	/**
	 * @brief mousePressEvent
	 * @param point
	 */
	virtual void mousePressEvent(cv::Point point) = 0;

	/**
	 * @brief mouseReleaseEvent
	 * @param point
	 */
	virtual void mouseReleaseEvent(cv::Point point) = 0;

	/**
	 * @brief mouseMoveEvent
	 * @param point
	 */
	virtual void mouseMoveEvent(cv::Point point) = 0;

	/**
	 * @brief save
	 * @param fname
	 */
	virtual void save(std::string fname) = 0;

	void saveFrame(std::string fname);
	void addDrawable(Drawable* newDrawable);
	void applyDrawables(cv::Mat& frame);
	std::deque<Drawable *> getDrawables();

	/**
	 * @brief activeDrawable
	 */
	Drawable* activeDrawable;

	/**
	 * @brief drawers
	 */
	std::deque<Drawable *> drawers;
};

#endif // PLAYER_HPP
