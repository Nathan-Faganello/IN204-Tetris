cmake_minimum_required (VERSION 3.0)
project (Whatever)


##############
## EXTERNAL ##
##############
add_subdirectory(External)


##############
## PROJECT ##
##############

file(GLOB_RECURSE WHATEVER_FILES
  include/whatever/*
  src/*
  )

include_directories(include)

add_executable(whatever ${WHATEVER_FILES})

target_link_libraries(whatever sfml-window)

target_include_directories(whatever
  SYSTEM PUBLIC
  external/SFML/include/
)