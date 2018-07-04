# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(SRC_DIR src/main/cpp/src)
set(INCLUDE_DIR src/main/cpp/include)

add_library( # Sets the name of the library.
             native-flappybird

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${SRC_DIR}/game_jni.cpp
             ${SRC_DIR}/game.cpp
             ${SRC_DIR}/shader.cpp
             ${SRC_DIR}/texture2D.cpp
             ${SRC_DIR}/create_stb_image_imp.cpp
             ${SRC_DIR}/resource_manager.cpp
             ${SRC_DIR}/sprite.cpp
             ${SRC_DIR}/sprite_renderer.cpp
             ${SRC_DIR}/animation.cpp
             ${SRC_DIR}/game_object.cpp
             ${SRC_DIR}/bird_game_object.cpp
             ${SRC_DIR}/gl_renderer_jni.cpp
             ${SRC_DIR}/gui_score.cpp
             ${SRC_DIR}/utils.cpp
             ${SRC_DIR}/column_game_object.cpp
             ${SRC_DIR}/game_level.cpp
             ${SRC_DIR}/string_literals.cpp
             ${SRC_DIR}/sound_manager.cpp
             ${SRC_DIR}/sound.cpp
             ${SRC_DIR}/sound_queue.cpp)

include_directories(${INCLUDE_DIR})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-flappybird

                       # Links the target library to the log library
                       # included in the NDK.
                       EGL
                       GLESv2
                       android
                       log
                       OpenSLES)