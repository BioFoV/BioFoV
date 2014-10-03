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

all: linux windows

################################################################################

linux: qt-linux opencv-linux
windows: qt-windows opencv-windows

################################################################################

qt: qt-linux qt-windows
qt-linux:
	$(MAKE) -C $(QT_FLD) linux
qt-windows:
	$(MAKE) -C $(QT_FLD) windows

opencv: opencv-linux opencv-windows
opencv-linux:
	$(MAKE) -C $(OPENCV_FLD) linux
opencv-windows:
	$(MAKE) -C $(OPENCV_FLD) windows

################################################################################

clean: clean-qt clean-opencv

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
