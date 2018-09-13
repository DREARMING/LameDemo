#include <jni.h>
#include <string>
#include "lame/include/lame.h"

extern "C" JNIEXPORT jstring

JNICALL
Java_com_mvcoder_lamedemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(get_lame_version());
}
