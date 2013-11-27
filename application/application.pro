TEMPLATE = subdirs
SUBDIRS = framework \
          gui

# build must be last:
CONFIG += ordered
SUBDIRS += build
