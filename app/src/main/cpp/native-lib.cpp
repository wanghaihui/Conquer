#include <jni.h>
#include <string>

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

extern "C" JNIEXPORT void
JNICALL
Java_com_wc_conquer_MainActivity_crash(JNIEnv *env, jobject obj) {
    crash();
}
