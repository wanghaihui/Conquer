#include <jni.h>
#include <string>
#include <stdio.h>
#include <android/log.h>

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
    std::string hello = "Hello from C++";
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


