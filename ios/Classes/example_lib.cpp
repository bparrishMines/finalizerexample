#include <jni.h>

#include "include/dart_api_dl.h"

static JavaVM *jvm;
static jclass classObject;
static jobject objectInstance;

void release_jobject(void* isolate_callback_data, void* peer) {
  JNIEnv* env;
  jint result = jvm->GetEnv((void**)&env, JNI_VERSION_1_6);
  if (result == JNI_EDETACHED) {
    result = jvm->AttachCurrentThread(&env, NULL);
    if (result == JNI_OK) {
      jmethodID printDisposeMessageID = env->GetMethodID(classObject, "printDisposeMessage", "()V");
      env->CallVoidMethod(objectInstance, printDisposeMessageID);

      env->DeleteGlobalRef(objectInstance);
      objectInstance = NULL;
      jvm->DetachCurrentThread();
    }
  }
}

DART_EXPORT void initialize_dl(void* initialize_api_dl_data) {
  Dart_InitializeApiDL(initialize_api_dl_data);
}

DART_EXPORT void create_jobject() {
  JNIEnv* env;
  jint result = jvm->GetEnv((void**)&env, JNI_VERSION_1_6);
  if (result == JNI_EDETACHED) {
    result = jvm->AttachCurrentThread(&env, NULL);
    if (result == JNI_OK) {
      jmethodID constructor = env->GetMethodID(classObject, "<init>", "()V");
      objectInstance = env->NewObject(classObject, constructor);
      objectInstance = env->NewGlobalRef(objectInstance);

      jvm->DetachCurrentThread();
    }
  }
}

DART_EXPORT void attach_finalizer(Dart_Handle handle) {
  void *peer = 0x0;
  intptr_t size = 4096;
  Dart_NewFinalizableHandle_DL(handle, peer, size, &release_jobject);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_finalizerexample_FinalizerexamplePlugin_initializeLib(JNIEnv *env, jobject object, jobject clazz) {
  env->GetJavaVM(&jvm);
  classObject = (jclass) env->NewGlobalRef(clazz);
}
