set(LOG_LEVEL_VERBOSE "VERBOSE")
set(LOG_LEVEL_INFO "INFO")
set(LOG_LEVEL_DEBUG "DEBUG")

function (log log_level message)
  if (NOT TRY_CMAKE_LOGGER_DISABLE)
    if(log_level STREQUAL LOG_LEVEL_VERBOSE AND TRY_CMAKE_VERBOSE)
      message(STATUS "(${LOG_LEVEL_VERBOSE}): ${message}")
    elseif(log_level STREQUAL LOG_LEVEL_INFO)
      message(STATUS "(${LOG_LEVEL_INFO}): ${message}")
    elseif(log_level STREQUAL LOG_LEVEL_DEBUG)
      message(STATUS "(${LOG_LEVEL_DEBUG}): ${message}")
    endif()
  endif()
endfunction()

# Default directory that includes this module or directory provided by user
if (NOT TRY_CMAKE_PROJECT_PATH)
  set(TRY_CMAKE_PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# Retrieve the current version of the project
execute_process(
  COMMAND git describe --tags
  WORKING_DIRECTORY ${TRY_CMAKE_PROJECT_PATH}
  OUTPUT_VARIABLE GIT_TAG
  ERROR_QUIET
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Check if a tag was found
if(GIT_TAG)
  log(${LOG_LEVEL_INFO} "Git tag found: ${GIT_TAG}")
  log(${LOG_LEVEL_VERBOSE} "TRY_CMAKE_PROJECT_VERSION: ${TRY_CMAKE_PROJECT_VERSION}")

  set(TRY_CMAKE_PROJECT_VERSION ${GIT_TAG} CACHE STRING "Project version based on the latest Git tag")
  set(TRY_CMAKE_VERSION_FOUND ON CACHE BOOL "Flag to indicate if the project version was found")
else()
  log(${LOG_LEVEL_INFO} "No Git tag found")
  set(TRY_CMAKE_VERSION_FOUND ON CACHE BOOL "Flag to indicate if the project version was found")
endif()
