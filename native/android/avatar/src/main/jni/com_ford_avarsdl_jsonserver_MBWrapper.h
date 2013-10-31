/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_ford_avarsdl_jsonserver_MBWrapper */

#ifndef _Included_com_ford_avarsdl_jsonserver_MBWrapper
#define _Included_com_ford_avarsdl_jsonserver_MBWrapper
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Function:    JNI_OnLoad
 */
jint JNI_OnLoad(JavaVM *vm, void *reserved);

/*
 * Function:    InvokeJSONServerSend
 */
void InvokeJSONServerSend(jint, jstring);
/*
 * Class:     com_ford_avarsdl_jsonserver_MBWrapper
 * Method:    CreateInstance
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_ford_avarsdl_jsonserver_MBWrapper_CreateInstance
  (JNIEnv *, jclass);

/*
 * Class:     com_ford_avarsdl_jsonserver_MBWrapper
 * Method:    StartMessageBroker
 * Signature: (Lcom/ford/avarsdl/jsonserver/JSONServer;)V
 */
JNIEXPORT void JNICALL Java_com_ford_avarsdl_jsonserver_MBWrapper_StartMessageBroker
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_ford_avarsdl_jsonserver_MBWrapper
 * Method:    StopMessageBroker
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_ford_avarsdl_jsonserver_MBWrapper_StopMessageBroker
  (JNIEnv *, jobject);

/*
 * Class:     com_ford_avarsdl_jsonserver_MBWrapper
 * Method:    DestroyMessageBroker
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_ford_avarsdl_jsonserver_MBWrapper_DestroyMessageBroker
  (JNIEnv *, jobject);

/*
 * Class:     com_ford_avarsdl_jsonserver_MBWrapper
 * Method:    OnMessageReceived
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_ford_avarsdl_jsonserver_MBWrapper_OnMessageReceived
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     com_ford_avarsdl_jsonserver_MBWrapper
 * Method:    MethodForThread
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_ford_avarsdl_jsonserver_MBWrapper_MethodForThread
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
