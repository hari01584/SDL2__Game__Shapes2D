//
// Created by hari0 on 21-04-2021.
//

#ifndef ANDROID_PROJECT_FILEOPERATIONS_H
#define ANDROID_PROJECT_FILEOPERATIONS_H
#include "import.h"

struct config_data{
    bool firstTimeEntry = 1;
    int color_r = 255;
    int color_g = 255;
    int color_b = 255;
    int color_a = 255;
};

namespace FileOp{
    extern  config_data saveOptionData;
    void InitializePrefPath();
    void PrepareConfigFileDescriptor();
    void loadConfigBin();
    void saveConfigBin();
};
#endif //ANDROID_PROJECT_FILEOPERATIONS_H
