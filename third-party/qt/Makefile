################################################################################
#
# Cross compiler for Qt programs that use OpenCV.
# creator: Miguel Almeida
# date: 2014/09
#
################################################################################

## System info
QT_DIR=$(shell pwd)
ifeq (${TRAVIS}, 1)
	CPUS=1
else
	CPUS=$(shell nproc)
endif

## Third party libs
# Qt
SRC_FLD=src
SRC_GIT=http://gitorious.org/qt/qt5.git
SRC_VERSION=v5.4.1

## Windows stuff
WIN_BUILD_FLD=windows-build
WIN_INSTALL_FLD=windows-install

## Linux stuff
LIN_BUILD_FLD=linux-build
LIN_INSTALL_FLD=linux-install

################################################################################

all: windows linux

################################################################################

src:
	test -d $(SRC_FLD) || git clone $(SRC_GIT) $(SRC_FLD)
	cd $(SRC_FLD); \
	git pull; \
	git checkout $(SRC_VERSION); \
	./init-repository --module-subset=qtbase,qttranslations
linux-src: src
windows-src: src

################################################################################

linux: linux-src
	mkdir -p $(LIN_BUILD_FLD); \
	cd $(LIN_BUILD_FLD); \
	../$(SRC_FLD)/configure \
		-prefix ../../../$(LIN_INSTALL_FLD)/ \
    	-opensource \
    	-skip qtwebkit \
		-release \
		-nomake tests \
		-nomake examples \
		-static \
		-confirm-license \
		-no-accessibility \
		-silent
	$(MAKE) -C $(LIN_BUILD_FLD) -j$(CPUS) install

windows: windows-src
	mkdir -p $(WIN_BUILD_FLD); \
	cd $(WIN_BUILD_FLD); \
	../$(SRC_FLD)/configure \
		-xplatform win32-g++ \
		-prefix ../../../$(WIN_INSTALL_FLD)/ \
		-opensource \
		-skip qtwebkit \
		-skip activeqt \
		-release \
		-nomake tests \
		-nomake examples \
		-static \
		-confirm-license \
		-qt-zlib \
		-qt-libpng \
		-qt-libjpeg \
		-qt-freetype \
		-no-xcb \
		-qt-pcre \
		-qt-xkbcommon \
		-no-accessibility \
		-no-opengl \
		-device-option CROSS_COMPILE=i686-w64-mingw32- \
		-no-pkg-config \
		-silent
	$(MAKE) -C $(WIN_BUILD_FLD) -j$(CPUS) install

################################################################################

clean-linux-build:
	rm -rf $(LIN_BUILD_FLD)
clean-linux-install:
	rm -rf $(LIN_INSTALL_FLD)
clean-linux: clean-linux-build clean-linux-install

clean-windows-build:
	rm -rf $(WIN_BUILD_FLD)
clean-windows-install:
	rm -rf $(WIN_INSTALL_FLD)
clean-windows: clean-windows-build clean-windows-install

clean-src:
	rm -rf $(SRC_FLD)

clean: clean-windows clean-linux clean-src
