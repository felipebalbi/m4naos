# Function to add sources to the list of sources
function(add_sources)
  foreach(arg ${ARGV})
    if(IS_DIRECTORY ${arg})
      message(FATAL_ERROR "`add_sources()` can't be used on a directory")
    endif()
  target_sources(${PROJECT_NAME} PRIVATE ${arg})
  endforeach()
endfunction()

# Function to conditionally enable compilation and linking of sources
function(add_sources_ifdef config)
  if(${${config}})
    add_sources(${ARGN})
  endif()
endfunction()
