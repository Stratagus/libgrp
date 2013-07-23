# - Try to find libgrp
# Once done, this will define
#
#  libgrp_FOUND - system has Magick
#  libgrp_INCLUDE_DIRS - the Magick include directories
#  libgrp_LIBRARIES - link these to use Magick

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(libgrp_PKGCONF libgrp)

# Include dir
find_path(libgrp_INCLUDE_DIR
  NAMES libgrp/libgrp.h
  PATHS ${libgrp_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(libgrp_LIBRARY
  NAMES libgrp
  PATHS ${libgrp_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(libgrp_PROCESS_INCLUDES libgrp_INCLUDE_DIR)
set(libgrp_PROCESS_LIBS libgrp_LIBRARY)
libfind_process(libgrp)

