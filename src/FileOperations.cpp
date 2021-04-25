//
// Created by hari0 on 20-04-2021.
//

//#include "FileOperations.h"
#include "FileOperations.h"


namespace FileOp{
    bool canPerformFOps;
    std::string pref_path;
    config_data saveOptionData;
    std::string fpath;

    void InitializePrefPath() {

        char *base_path = SDL_GetPrefPath("shapes2d", "shx2d");
        if (base_path) {
            canPerformFOps = true;
            pref_path = base_path;
            fpath = pref_path + "config.bin";
            SDL_Log("Set Local FIle Path: %s", pref_path.c_str());
        } else {
            canPerformFOps = false;
        }
    }


    void PrepareConfigFileDescriptor() {
        if(!canPerformFOps)
            return;

        SDL_RWops* file = SDL_RWFromFile(fpath.c_str(), "r+b" );
        if( file == NULL ) {
            SDL_Log("Error opening file, Recreating!");
            file = SDL_RWFromFile( fpath.c_str(), "w+b" );
            if( file == NULL ) canPerformFOps = false;
            else{
                SDL_RWwrite( file, (struct config_data*)&saveOptionData, sizeof(config_data), 1 );
            }
        }
        SDL_RWclose( file );
    }

    void loadConfigBin(){
        if(!canPerformFOps)
            return;

        SDL_RWops* file = SDL_RWFromFile( fpath.c_str(), "r+b" );
        SDL_RWread( file, (struct config_data*)&saveOptionData, sizeof(config_data), 1 );
        SDL_RWclose( file );
    }

    void saveConfigBin(){
        if(!canPerformFOps)
            return;
        SDL_RWops* file = SDL_RWFromFile( fpath.c_str(), "w+b" );
        SDL_RWwrite( file, (struct config_data*)&saveOptionData, sizeof(config_data), 1 );
        SDL_RWclose( file );
    }
};


