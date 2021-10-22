# main.c 编译成一个可执行文件，因为里面包含 main 函数
#add_executable(home main.c swap.c)
#add_executable(home tlv.c)
#add_executable(home find_judge.c)
#add_executable(home sum_one_hundred.c)
#add_executable(home min_area_rectangle939.c)
#add_executable(home minSubArrayLen_209.c)
#add_executable(home GetLongestFlawedVowelSubstrLen.c)
#add_executable(home reverse_single_list.c)
#add_executable(home maxLength_1239.c)
add_executable(home longestRepeatingSubstring_1602.c)

target_include_directories(home PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 和华为安全函数的库进行链接，如果使用了华为安全函数，请将注释取消
#target_link_libraries(test ${CMAKE_SOURCE_DIR}/lib/libsecurec.a)

# TODO 如何在上面已有的 exe 中增加一个新的源文件，参与编译?
# 1: 新建一个文件，比如 newfile.cpp
# 2: 需要将其添加到上面的 add_executable() 参数列表的最后

# TODO 如何增加一个新的可执行文件
# 1：在 src 目录下新建一个 .cpp/.c 文件，编辑并且保存；比如叫 newfile.cpp
# 2: 增加一行 add_executable(newfile newfile.cpp)
# 3: 重新执行 cmake build 即可

# !! 注意!!
# 1: 头文件要加到 include 目录下，如果添加到了其它目录下，务必在这里调用 include_directories
# 2: 如果新增的文件不被添加到add_executable, 那么就不会被编译。