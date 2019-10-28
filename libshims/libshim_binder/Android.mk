LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := libbinder_interface.cpp
LOCAL_MODULE := libshim_binder
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SHARED_LIBRARIES := libbinder libutils

include $(BUILD_SHARED_LIBRARY)
