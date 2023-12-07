#include <jni.h>
#include <string>
#include "jni_helper.hpp"
#include <android/log.h>

using namespace lsplant;

#define LOG_TAG "jni_helper"
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define ALOGF(...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)


extern "C" JNIEXPORT jstring
JNICALL
Java_com_example_jnihelper_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_jnihelper_MainActivity_reverseStringArray(JNIEnv *env, jobject thiz, jobjectArray string_array) {
    auto classNameList = ScopedLocalRef<jobjectArray>(env, string_array);
    ALOGI("classNameList: size %d", classNameList.size());
    ALOGW("for in");
    int count;
    count = 0;
    for (auto& className : classNameList) {
        ALOGD("for count=%d", count++);
        if (className.get() == nullptr){
            ALOGI("class: nullptr");
            break;
        }
        auto str = JUTFString(env, (jstring)className.get(), "null str");
        ALOGV("class: %s", str.get());
    }
    ALOGE("for count end=%d", count);
    ALOGW("for const in");
    count = 0;
    for (const auto& className : classNameList) {
        ALOGD("for count=%d", count++);
        if (className.get() == nullptr){
            ALOGI("class: nullptr");
            break;
        }
        auto str = JUTFString(env, (jstring)className.get(), "null str");
        ALOGV("class: %s", str.get());
    }
    ALOGE("for count end=%d", count);
    ALOGW("for");
    count = 0;
    for (int i = 0; i < classNameList.size(); i++) {
        ALOGD("for count=%d", count++);
        if (classNameList[i].get() == nullptr){
            ALOGI("class: nullptr");
            break;
        }
        auto str = JUTFString(env, (jstring)classNameList[i].get(), "null str");
        ALOGV("class: %s", str.get());
    }
    ALOGW("for iter");
    count = 0;
    for (auto i = classNameList.begin(); i != classNameList.end(); ++i) {
        ALOGD("for count=%d", count++);
        if ((*i).get() == nullptr){
            ALOGI("class: nullptr");
            break;
        }
        auto str = JUTFString(env, (jstring)(*i).get(), "null str");
        ALOGV("class: %s", str.get());
    }
    ALOGE("for count end=%d", count);
    ALOGW("for const iter");
    count = 0;
    for (auto i = classNameList.cbegin(); i != classNameList.cend(); ++i) {
        ALOGD("for count=%d", count++);
        if ((*i).get() == nullptr){
            ALOGI("class: nullptr");
            break;
        }
        auto str = JUTFString(env, (jstring)(*i).get(), "null str");
        ALOGV("class: %s", str.get());
    }
    ALOGE("for count end=%d", count);
    return string_array;
}