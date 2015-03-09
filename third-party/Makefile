################################################################################
#
# Cross compiler for Qt programs that use OpenCV.
# creator: Miguel Almeida
# date: 2014/09
#
################################################################################

## Third party libs
# OpenCV
OPENCV_FLD=opencv
# Qt
QT_FLD=qt
# ffmpeg
FFMPEG_FLD=ffmpeg

all: linux windows

################################################################################

linux: qt-linux opencv-linux
windows: qt-windows opencv-windows

travis-ci-windows:
	$(MAKE) -C $(OPENCV_FLD) windows-deploy-tbz
	$(MAKE) -C $(QT_FLD) windows-deploy-tbz

travis-ci-linux:
	$(MAKE) -C $(OPENCV_FLD) linux-deploy-tbz
	$(MAKE) -C $(QT_FLD) linux-deploy-tbz

################################################################################

qt: qt-linux qt-windows
qt-linux:
	$(MAKE) -C $(QT_FLD) linux
qt-windows:
	$(MAKE) -C $(QT_FLD) windows

opencv: opencv-linux opencv-windows
opencv-linux: ffmpeg-linux
	$(MAKE) -C $(OPENCV_FLD) linux
opencv-windows:
	$(MAKE) -C $(OPENCV_FLD) windows

ffmpeg: ffmpeg-linux
ffmpeg-linux:
	$(MAKE) -C $(FFMPEG_FLD) linux

################################################################################

clean: clean-qt clean-opencv clean-install

clean-windows: clean-qt-windows clean-opencv-windows
clean-linux: clean-qt-linux clean-opencv-linux

clean-qt: clean-qt-windows clean-qt-linux
clean-qt-linux:
	$(MAKE) -C $(QT_FLD) clean-linux
clean-qt-windows:
	$(MAKE) -C $(QT_FLD) clean-windows

clean-opencv: clean-opencv-windows clean-opencv-linux
clean-opencv-linux:
	$(MAKE) -C $(OPENCV_FLD) clean-linux
clean-opencv-windows:
	$(MAKE) -C $(OPENCV_FLD) clean-windows

clean-src: clean-qt-src clean-opencv-src
clean-qt-src:
	$(MAKE) -C $(QT_FLD) clean-src
clean-opencv-src:
	$(MAKE) -C $(OPENCV_FLD) clean-src

clean-install: clean-linux-install clean-windows-install
clean-linux-install:
	rm -rf linux-install
clean-windows-install:
	rm -rf windows-install
