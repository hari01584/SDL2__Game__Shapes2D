cmake_minimum_required(VERSION 3.6)

project(GAME)

# armeabi-v7a requires cpufeatures library
# include(AndroidNdkModules)
# android_ndk_import_module_cpufeatures()


# SDL sources are in a subfolder named "SDL"
add_subdirectory(SDL2)

find_package(SDL2_imager REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Image)


# Compilation of companion libraries
#add_subdirectory(SDL2_imager)
#add_subdirectory(SDL2_mixer)
#add_subdirectory(SDL2_ttf)

# Your game and its CMakeLists.txt are in a subfolder named "src"
add_subdirectory(src)

