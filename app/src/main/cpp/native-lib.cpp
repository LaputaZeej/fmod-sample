#include <jni.h>
#include <string>
#include <unistd.h>
#include "fmod.hpp"
#include "fmod_dsp_effects.h"
#include "com_laputa_fmod_FmodHelper.h"

using namespace FMOD;

extern "C" JNIEXPORT jstring JNICALL
Java_com_laputa_fmod_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_laputa_fmod_MainActivity_nativeChangeVoice(JNIEnv *env, jobject thiz, jint mode,
                                                    jstring path) {
    const char *ptr_path = (env->GetStringUTFChars(path, 0));
    System *ptr_system = nullptr;
    Sound *ptr_sound = nullptr;
    Channel *ptr_channel = nullptr;
    // 数字信号处理
    DSP *ptr_dsp = 0;
    System_Create(&ptr_system);
    ptr_system->init(32, FMOD_INIT_NORMAL, 0);
    ptr_system->createSound(ptr_path, FMOD_DEFAULT, 0, &ptr_sound);
    ptr_system->playSound(ptr_sound, 0, false, &ptr_channel);
    switch (mode) {
        case com_laputa_fmod_FmodHelper_MODE_NORMAL:

            break;
        case com_laputa_fmod_FmodHelper_MODE_LOLI:
            // 音调提高
            ptr_system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &ptr_dsp);
            ptr_dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 3.0F);
            ptr_channel->addDSP(0, ptr_dsp);
            break;
        case com_laputa_fmod_FmodHelper_MODE_DASHU:
            // 频率
            float f;
            ptr_channel->getFrequency(&f);
            ptr_channel->setFrequency(f * 2.0f);
            break;
        case com_laputa_fmod_FmodHelper_MODE_KONGLING:
            // 回音
            ptr_system->createDSPByType(FMOD_DSP_TYPE_ECHO, &ptr_dsp);
            ptr_dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200);
            ptr_dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 90);
            ptr_channel->addDSP(0, ptr_dsp);
            break;
        default:
            ptr_system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &ptr_dsp);
            ptr_dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7F);
            ptr_channel->addDSP(0, ptr_dsp);

            ptr_system->createDSPByType(FMOD_DSP_TYPE_ECHO, &ptr_dsp);
            ptr_dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200);
            ptr_dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 30);
            ptr_channel->addDSP(1, ptr_dsp);
            // 颤抖
            ptr_system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &ptr_dsp);
            ptr_dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY, 20);
            ptr_dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.8);
            ptr_channel->addDSP(2, ptr_dsp);
            break;
    }

    bool isPlaying = true;
    while (isPlaying) {
        ptr_channel->isPlaying(&isPlaying);
        usleep(200 * 1000);
    }

    ptr_dsp->release();
    ptr_sound->release();
    ptr_system->release();
    ptr_system->close();
    ptr_system = nullptr;
    ptr_sound = nullptr;
    ptr_channel = nullptr;
    ptr_dsp = 0;
    env->ReleaseStringUTFChars(path, ptr_path);
}