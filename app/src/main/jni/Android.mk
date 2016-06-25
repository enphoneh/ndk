LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE :=demo
LOCAL_LDLIBS:=-L$(SYSROOT)/usr/lib -llog
LOCAL_SRC_FILES :=com_aven_ndk_Watcher.cpp
include $(BUILD_SHARED_LIBRARY)