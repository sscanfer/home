project(home)
cmake_minimum_required(VERSION 3.16)
# include (include(CTest))
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)

# TODO 如果有更多的和 src 并列的子目录, 并且其中存在源代码, 请把他们也加入进来, 否则这些文件不会参与编译
# add_subdirectory(your_new_folder)