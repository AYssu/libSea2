# LOCAL_PATH := $(call my-dir)


LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := Sea2
LOCAL_SRC_FILES := ../../../include/libSea2.a
include $(PREBUILT_STATIC_LIBRARY)



    
include $(CLEAR_VARS)
LOCAL_SRC_FILES := main.cpp
LOCAL_STATIC_LIBRARIES := Sea2

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../../../include/ \

LOCAL_MODULE := main
LOCAL_LDFLAGS += -llog -landroid

include $(BUILD_EXECUTABLE)
