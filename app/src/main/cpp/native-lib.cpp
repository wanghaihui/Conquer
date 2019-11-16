#include <jni.h>
#include <string>
#include <stdio.h>
#include <android/log.h>
#include <iostream>

#define LOG_TAG "haihui"

#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT jstring
JNICALL
Java_com_wc_conquer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

#if defined(__arm__)
    #if defined(__ARM_ARCH_7A__)
        #if defined(__ARM_NEON__)
            #if defined(__ARM_PCS_VFP)
                #define ABI "armeabi-v7a/NEON (hard-float)"
            #else
                #define ABI "armeabi-v7a/NEON"
            #endif
        #else
            #if defined(__ARM_PCS_VFP)
                #define ABI "armeabi-v7a (hard-float)"
            #else
                #define ABI "armeabi-v7a"
            #endif
        #endif
    #else
        #define ABI "armeabi"
    #endif
#elif defined(__i386__)
    #define ABI "x86"
#elif defined(__x86_64__)
    #define ABI "x86_64"
#elif defined(__mips64) /* mips64el-* toolchain defines __mips__ too */
    #define ABI "mips64"
#elif defined(__mips__)
    #define ABI "mips"
#elif defined(__aarch64__)
    #define ABI "arm64-v8a"
#else
    #define ABI "unknown"
#endif

    std::string hello = "Hello from C++, ";
    hello += "Compiled with ABI " ABI ".";
    return env->NewStringUTF(hello.c_str());
}

// 引起crash
void crash() {
    volatile int *a = (int *) (NULL);
    *a = 1;
}

void pointer() {
    int a = 100;
    char str[20] = "c.biancheng.net";
    ALOGD("%#X, %#X\n", (unsigned int) &a, (unsigned int) str);
}

extern "C" JNIEXPORT void
JNICALL
Java_com_wc_conquer_MainActivity_crash(JNIEnv *env, jobject obj) {
    //crash();
    pointer();
}




