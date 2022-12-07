cmake_minimum_required(VERSION 2.8)
project(webrtc_ns_cpp)
file(GLOB NS_SRC ns/*.cc ns/*.h ns/*.c)
add_executable(webrtc_ns_cpp main.cc ${NS_SRC})

SET(CMAKE_C_FLAGS_DEBUG "-O3")
SET(CMAKE_C_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG "-O3")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ftree-vectorize")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftree-vectorize")
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG} -Wall -g -O0 -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELDEBINFO} -g -O3")

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}  -fPIC -O0 -Wall -g2 -ggdb")

target_link_libraries(webrtc_ns_cpp -lm)



cmake_minimum_required(VERSION 3.10)
project(unittest_ns_no_resample_2019)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g") # 调试信息 set(CMAKE_CXX_FLAGS "-Wall") # 开启所有警告
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}  -fPIC -O0 -Wall -g2 -ggdb")

AUX_SOURCE_DIRECTORY(ns/. ns)

include_directories(.)

add_executable(unittest_ns_no_resample_2019
        unittest_ns_no_resample_2019.cc
        ${ns}
)

target_link_libraries(unittest_ns_no_resample_2019 -lm)
#target_link_libraries(unittest_ns_no_resample_2019 -lm)


# cmake_minimum_required(VERSION 2.8)
# project(unittest_ns_no_resample_2019)
# file(GLOB NS_SRC ns/*.cc ns/*.h ns/*.c)
# add_executable(unittest_ns_no_resample_2019 unittest_ns_no_resample_2019.cc ${NS_SRC})

# SET(CMAKE_C_FLAGS_DEBUG "-O3")
# SET(CMAKE_C_FLAGS_RELEASE "-O3")
# SET(CMAKE_CXX_FLAGS_DEBUG "-O3")
# SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ftree-vectorize")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftree-vectorize")
# SET(CMAKE_BUILD_TYPE "Release")
# SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG} -Wall -g -O0 -Wextra")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELDEBINFO} -g -O3")

# set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}  -fPIC -O0 -Wall -g2 -ggdb")

# target_link_libraries(unittest_ns_no_resample_2019 -lm)
