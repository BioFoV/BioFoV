#ifndef EVENT_H
#define EVENT_H

#ifndef INC_VIDEO
#define INC_VIDEO
#include "../Video/Video.hpp"
#endif

#ifndef INC_FRAME
#define INC_FRAME
#include "../Frame/Frame.hpp"
#endif

#ifndef INC_INDIVIDUAL
#define INC_INDIVIDUAL
#include "../Individual/Individual.hpp"
#endif

#ifndef INC_PLAYER
#define INC_PLAYER
#include "../player.hpp"
#endif

#ifndef INC_STDEXCEPT
#define INC_STDEXCEPT
#include <stdexcept>
#endif

#ifndef INC_LIST
#define INC_LIST
#include <list>
#endif

#define PLAY_FRAMES 0
#define PLAY_MASK 1
#define PLAY_MASKED_FRAMES 2

#include <QObject>

class Frame;
class Snapshot;
class Individual;
class Video;

///
/// \brief Class that represents a contiguous set of frames with something
///interesting on them.
///
class Event : public QObject, public Player {
    Q_OBJECT

signals:
     void frameProcessChanged(unsigned int newFrame);

protected:
	// external references
    /// \brief Video from which the Frames in this Event were extracted.
	Video* vid;
    /// \brief Deque of Frames that define this Event.
    std::deque<Frame*> frames;
    /// \brief Deque of Individual that show up in this Event.
    std::deque<Individual*> individuals;
    /// \brief Deque of Snapshots.
    std::deque<Snapshot*> snapshots;

private:
    /// \brief Player position.
    double position;

    /// \brief Player playback mode.
    /// PLAY_FRAMES -> plays frames,
    /// PLAY_MASK -> plays BW mask,
    /// PLAY_MASKED_FRAMES -> plays frames with the applied mask.
    int playMode;

public:
    /// \brief Constructor providing the Video from which the Frames are to be
    ///extracted.
    Event(Video* iVid);

    /// \brief Simple destructor.
    virtual ~Event();

    // Modifiers
    /// \brief Appends another Event to this one.
    /// \param ev1 Event to be appended to this one.
    /// \return The reference to the resulting Event.
    Event& operator +=(const Event& ev1);

    // Functions
    /// \brief Adds another Frame to this Event.
    /// \param inFrame Frame to be added to this Event.
    void addFrame(Frame* inFrame);

    /// \brief Adds another Snapshot to this Event.
    /// \param inSnap Snapshot to be added to this Event.
    void addSnapshot(Snapshot* inSnap);

    /// \brief Pop last Frame.
    void remLastFrame();

    /// \brief Pop last Snapshot.
    void remLastSnapshot();

    /// \brief Splits this Event into several based on the background
    ///subtraction results.
    /// TODO: Extensive description since this is an important method.
    /// \param threshold
    /// \param maxcount
    /// \param mincount
    /// \return Deque of the singular Event FIXME.
    std::deque<Event*> splitEvent(double threshold, double maxcount, double mincount);

    bool getFrameObject(Frame** outFrame);

    // Capture functions
    bool check_cap();
    bool setFramePos(double frameNum);
    double getFramePos();
    bool getFrame(cv::Mat &frame);
    bool getPrevFrame(cv::Mat &frame);
    bool getNextFrame(cv::Mat &frame);
    void* getCurrentFrameRef();

    // Properties
    double getFrameInt();
    double getFPS();
    double getLengthTime();
    double getLengthFrames();

    void mousePressEvent(cv::Point){}
    void mouseReleaseEvent(cv::Point){}
    void mouseMoveEvent(cv::Point){}

    // Playback modifier
    void setPlaybackMode(int mode);
};
#endif 
