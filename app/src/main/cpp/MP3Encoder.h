//
// Created by mvcoder on 2018/9/13.
//

#ifndef LAMEDEMO_MP3ENCODER_H
#define LAMEDEMO_MP3ENCODER_H

#include <stdio.h>
#include <lame.h>

class MP3Encoder{
private:
    FILE* pcmFile;
    FILE* mp3File;
    lame_t lameClient;

public:
    MP3Encoder();
    ~MP3Encoder();
    int init(const char* pcmFilePath, const char* mp3FilePath, int sampleRate, int channels, int bitRate);
    void encode();
    void destroy();
};

#endif //LAMEDEMO_MP3ENCODER_H
