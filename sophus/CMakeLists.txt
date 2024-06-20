cmake_minimum_required(VERSION 3.5)

project(useSophus)

find_package(Sophus REQUIRED)
find_package(Pangolin REQUIRED)
find_package(fmt REQUIRED)

include_directories("usr/include/eigen3")

set(FMT_LIBRARIES fmt::fmt)

include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(test test.cpp)
target_link_libraries(test ${Pangolin_LIBRARIES} ${FMT_LIBRARIES})

add_executable(useSophus useSophus.cpp)
target_link_libraries(useSophus Sophus::Sophus ${FMT_LIBRARIES})

add_executable(motion motion.cpp)
target_link_libraries(motion Sophus::Sophus ${FMT_LIBRARIES})

add_executable(test2 test2.cpp)
target_link_libraries(test2 Sophus::Sophus ${FMT_LIBRARIES})
