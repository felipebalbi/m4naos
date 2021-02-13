# SPDX-License-Identifier: GPL-3.0-or-later

find_package(Git QUIET)

if (GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short=12 HEAD
    WORKING_DIRECTORY                ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE                  PROJECT_VERSION_GIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    ERROR_VARIABLE                   stderr
    RESULT_VARIABLE                  ret
  )

  if (ret)
    message(STATUS "unable to run `git describe`: ${stderr}")
  elseif (CMAKE_VERBOSE_MAKEFILE)
    message(STATUS "unable to run `git describe`: ${stderr}")
  endif()
endif(GIT_FOUND)
