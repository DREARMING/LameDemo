//
// Created by mvcoder on 2018/9/13.
//
#include "MP3Encoder.h"

int MP3Encoder::init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channels,
                     int bitRate) {
    int ret = -1;
    pcmFile = fopen(pcmFilePath, "rb");
    if(pcmFile){
        mp3File = fopen(mp3FilePath, "wb");
        if(mp3File){
            lameClient = lame_init();
            lame_set_in_samplerate(lameClient, sampleRate);
            lame_set_out_samplerate(lameClient, sampleRate);
            lame_set_num_channels(lameClient, channels);
            lame_set_brate(lameClient, bitRate);
            lame_init_params(lameClient);
            ret = 0;
        }
    }
    return ret;
}

void MP3Encoder::encode() {
    int bufferSize = 1024 * 256;
    short* buffer = new short[bufferSize / 2];
    short* leftBuffer = new short[bufferSize / 4];
    short* rightBuffer = new short[bufferSize / 4];
    unsigned char* mp3Buffer = new unsigned char[bufferSize];
    size_t readBufferSize = 0;
    while ((readBufferSize = fread(buffer, 2, bufferSize / 2, pcmFile)) > 0){
        for(int i=0; i<readBufferSize; i++){
            if(i % 2 == 0){
                leftBuffer[i/2] = buffer[i];
            }else{
                rightBuffer[i/2] = buffer[i];
            }
        }
        size_t worte_size = lame_encode_buffer(lameClient,leftBuffer,rightBuffer,(int)readBufferSize /2, mp3Buffer, bufferSize);
        fwrite(mp3Buffer,1,worte_size,mp3File);
    }
    delete[] buffer;
    delete[] leftBuffer;
    delete[] rightBuffer;
}

void MP3Encoder::destroy() {
    if(pcmFile){
        fclose(pcmFile);
    }
    if(mp3File){
        fclose(mp3File);
        lame_close(lameClient);
    }
}