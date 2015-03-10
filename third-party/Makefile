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

## Tarballs
WIN_TBZ=windows.tbz
LIN_TBZ=linux.tbz

WIN_INSTALL_FLD=windows-install
LIN_INSTALL_FLD=linux-install

WIN_TBZ_URL=https://www.dropbox.com/s/p2pc135j08569ef/windows.tbz
LIN_TBZ_URL=https://www.dropbox.com/s/u0owdgrsn9lxegl/linux.tbz
PLACEHOLDER=PLACEHOLDER

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
opencv-linux: ffmpeg-linux
	$(MAKE) -C $(OPENCV_FLD) linux
opencv-windows:
	$(MAKE) -C $(OPENCV_FLD) windows

ffmpeg: ffmpeg-linux
ffmpeg-linux:
	$(MAKE) -C $(FFMPEG_FLD) linux

############################ Lazy Deploy Rules #################################

create-tbzs: linux-create-tbz windows-create-tbz

linux-create-tbz: linux
	tar -cjf $(LIN_TBZ) $(LIN_INSTALL_FLD)

windows-create-tbz: windows
	tar -cjf $(WIN_TBZ) $(WIN_INSTALL_FLD)

travis-ci-linux:
	rm -rf $(LIN_INSTALL_FLD)
	wget --quiet $(LIN_TBZ_URL)
	tar -xjf $(LIN_TBZ)
	cp $(QT_FLD)/qt.conf $(LIN_INSTALL_FLD)/bin/
	sed -i "s|$(PLACEHOLDER)|$(LIN_INSTALL_FLD)|g" \
		$(LIN_INSTALL_FLD)/bin/qt.conf

travis-ci-windows:
	rm -rf $(WIN_INSTALL_FLD)
	wget --quiet $(QT_WIN_TBZ_URL)
	tar -xjf $(WIN_TBZ)
	cp $(QT_FLD)/qt.conf $(WIN_INSTALL_FLD)/bin/
	sed -i "s|$(PLACEHOLDER)|$(WIN_INSTALL_FLD)|g" \
		$(WIN_INSTALL_FLD)/bin/qt.conf

################################################################################

clean: clean-qt clean-opencv clean-ffmpeg clean-install clean-tbz

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

clean-ffmpeg: clean-ffmpeg-linux
clean-ffmpeg-linux:
	$(MAKE) -C $(FFMPEG_FLD) clean-linux

clean-src: clean-qt-src clean-opencv-src clean-ffmpeg-src
clean-qt-src:
	$(MAKE) -C $(QT_FLD) clean-src
clean-opencv-src:
	$(MAKE) -C $(OPENCV_FLD) clean-src
clean-ffmpeg-src:
	$(MAKE) -C $(FFMPEG_FLD) clean-src

clean-install: clean-linux-install clean-windows-install
clean-linux-install:
	rm -rf linux-install
clean-windows-install:
	rm -rf windows-install

clean-tbz: clean-windows-tbz clean-linux-tbz
clean-windows-tbz:
	rm -f $(WIN_TBZ)
clean-linux-tbz:
	rm -f $(LIN_TBZ)
