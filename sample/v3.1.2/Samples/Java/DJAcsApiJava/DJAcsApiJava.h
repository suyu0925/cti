/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class DJKeygoe_DJAcsAPIDef */

#ifndef _Included_DJKeygoe_DJAcsAPIDef
#define _Included_DJKeygoe_DJAcsAPIDef
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsOpenStream
 * Signature: (ILDJKeygoe/ServerID_t;BIIILjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsOpenStream
  (JNIEnv *, jobject, jint, jobject, jbyte, jint, jint, jint, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsCloseStream
 * Signature: (ILjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsCloseStream
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsSetMaster
 * Signature: (IBLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetMaster
  (JNIEnv *, jobject, jint, jbyte, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsSetESR
 * Signature: (ILDJKeygoe/EsrFunc;II)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetESR
  (JNIEnv *, jobject, jint, jobject, jint, jint);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsGetDeviceList
 * Signature: (ILjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsGetDeviceList
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsSetTimer
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetTimer
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsOpenDevice
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsOpenDevice
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsCloseDevice
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsCloseDevice
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsResetDevice
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsResetDevice
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetDevTimer
 * Signature: (ILDJKeygoe/DeviceID_t;I)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetDevTimer
  (JNIEnv *, jobject, jint, jobject, jint);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsGetDevState
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetDevState
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetDevGroup
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetDevGroup
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsMakeCallOut
 * Signature: (ILDJKeygoe/DeviceID_t;[B[BLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsMakeCallOut
  (JNIEnv *, jobject, jint, jobject, jbyteArray, jbyteArray, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetParam
 * Signature: (ILDJKeygoe/DeviceID_t;SSLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam
  (JNIEnv *, jobject, jint, jobject, jshort, jshort, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsGetParam
 * Signature: (ILDJKeygoe/DeviceID_t;SSLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetParam
  (JNIEnv *, jobject, jint, jobject, jshort, jshort, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsAlertCall
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsAlertCall
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsAnswerCallIn
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsAnswerCallIn
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsLinkDevice
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLinkDevice
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsUnlinkDevice
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsUnlinkDevice
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsClearCall
 * Signature: (ILDJKeygoe/DeviceID_t;ILjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClearCall
  (JNIEnv *, jobject, jint, jobject, jint, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsJoinToConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;LDJKeygoe/CmdParamData_Conf_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsJoinToConf
  (JNIEnv *, jobject, jint, jobject, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsLeaveFromConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;LDJKeygoe/CmdParamData_Conf_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLeaveFromConf
  (JNIEnv *, jobject, jint, jobject, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsClearConf
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClearConf
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsPlay
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PlayProperty_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPlay
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsInitPlayIndex
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsInitPlayIndex
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsBuildPlayIndex
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PlayProperty_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsBuildPlayIndex
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControlPlay
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/ControlPlay_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlPlay
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsRecord
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/RecordProperty_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRecord
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControlRecord
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/ControlRecord_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlRecord
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendFax
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;[B[BLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendFax
  (JNIEnv *, jobject, jint, jobject, jobject, jbyteArray, jbyteArray, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsStopSendFax
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsStopSendFax
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsReceiveFax
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;[B[BLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsReceiveFax
  (JNIEnv *, jobject, jint, jobject, jobject, jbyteArray, jbyteArray, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsStopReceiveFax
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsStopReceiveFax
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsChangeMonitorFilter
 * Signature: (ILDJKeygoe/DeviceID_t;ILjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsChangeMonitorFilter
  (JNIEnv *, jobject, jint, jobject, jint, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendIOData
 * Signature: (ILDJKeygoe/DeviceID_t;SS[B)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendIOData
  (JNIEnv *, jobject, jint, jobject, jshort, jshort, jbyteArray);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendSignalMsg
 * Signature: (ILDJKeygoe/DeviceID_t;S)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendSignalMsg
  (JNIEnv *, jobject, jint, jobject, jshort);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsOpenStreamExt
 * Signature: (ILDJKeygoe/ServerID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsOpenStreamExt
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsCloseStreamExt
 * Signature: (ILDJKeygoe/ServerID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsCloseStreamExt
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsPlayCSP
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/CSPPlayProperty_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPlayCSP
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendCSPData
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/CSPPlayDataInfo_t;[BLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendCSPData
  (JNIEnv *, jobject, jint, jobject, jobject, jbyteArray, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControlPlayCSP
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/ControlPlay_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlPlayCSP
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsRecordCSP
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/RecordCSPProperty_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRecordCSP
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControlRecordCSP
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/ControlRecord_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlRecordCSP
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsInitPlay3gppIndex
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsInitPlay3gppIndex
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsBuildPlay3gppIndex
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Play3gppProperty_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsBuildPlay3gppIndex
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_cts3gppPlay
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Play3gppProperty_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1cts3gppPlay
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControl3gppPlay
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Control3gppPlay_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControl3gppPlay
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_cts3gppRecord
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Record3gppProperty_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1cts3gppRecord
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControl3gppRecord
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Control3gppRecord_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControl3gppRecord
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsQueryLicense
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsQueryLicense
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctxRegister
 * Signature: (I[BBLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxRegister
  (JNIEnv *, jobject, jint, jbyteArray, jbyte, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctxLink
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;BLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxLink
  (JNIEnv *, jobject, jint, jobject, jobject, jbyte, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctxSendAppData
 * Signature: (I[B[BB[BIBBLDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxSendAppData
  (JNIEnv *, jobject, jint, jbyteArray, jbyteArray, jbyte, jbyteArray, jint, jbyte, jbyte, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendRawFrame
 * Signature: (ILDJKeygoe/DeviceID_t;S[B)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendRawFrame
  (JNIEnv *, jobject, jint, jobject, jshort, jbyteArray);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsJoinTo3GVConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;LDJKeygoe/Acs_MediaEx_Input_V;LDJKeygoe/Acs_MediaEx_Output_V;BLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsJoinTo3GVConf
  (JNIEnv *, jobject, jint, jobject, jobject, jobject, jobject, jbyte, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsLeaveFrom3GVConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLeaveFrom3GVConf
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsClear3GVConf
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClear3GVConf
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsGetLayout
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetLayout
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetLayout
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Acs_3GVConf_LayoutList;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetLayout
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsGetVisibleList
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetVisibleList
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetVisibleList
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Acs_3GVConf_VisibleList;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetVisibleList
  (JNIEnv *, jobject, jint, jobject, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsPutTextInPicture
 * Signature: (I[BLDJKeygoe/PutTextInPicture_Param;ILjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPutTextInPicture
  (JNIEnv *, jobject, jint, jbyteArray, jobject, jint, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsRestart3GVConf
 * Signature: (ILDJKeygoe/DeviceID_t;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRestart3GVConf
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsGetRelateMod
 * Signature: (IBB)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsGetRelateMod
  (JNIEnv *, jobject, jint, jbyte, jbyte);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsPutUsrEvt
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/UserEvt_Head_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPutUsrEvt
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsLedCtrl
 * Signature: (IBLDJKeygoe/UserLedCtrl;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsLedCtrl
  (JNIEnv *, jobject, jint, jbyte, jobject);

#ifdef __cplusplus
}
#endif
#endif
