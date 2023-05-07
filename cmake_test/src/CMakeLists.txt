# include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(mysum SHARED header.cpp )
target_include_directories(mysum PUBLIC ${CMAKE_SOURCE_DIR}/include)
#----------------------------------------------------------------#
#  这是
# target_link_directories(mysum PUBLIC ${CMAKE_SOURCE_DIR}/include)
