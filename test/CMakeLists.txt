set (TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
configure_file (
	"config.h.in"
	"${CMAKE_CURRENT_BINARY_DIR}/config.h"
)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

add_executable(threadxx-test
        main.cpp

	realisation.cpp
	testing.cpp
	../main/threadxx/threadxx.cpp
	../main/logxx/logxx.cpp
)
