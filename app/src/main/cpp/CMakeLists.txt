# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

project("fmod")

# 1.导入头文件
include_directories("inc")

#批量导入所有源文件,就不用一个个文件导入了
file(GLOB laputa-all-file *.c *.h *.cpp *.hpp)
add_library(
        native-lib
        SHARED
        ${laputa-all-file}
)

#add_library( # Sets the name of the library.
#        native-lib
#        #Sets the library as a shared library.
#        SHARED
#        #Provides a relative path to your source file(s).
#        native-lib.cpp)

find_library( # Sets the name of the path variable. 自定义名称，目的防止多次查找
        laputa-log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate. 自动查找NDK log库
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

# 2.导入库文件
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

# 3.链接
target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK. 使用自定义名称，也可以直接用log
        ${laputa-log-lib}
        fmod
        fmodL #直接的写法 具体的库链接到native-lib.so
        )