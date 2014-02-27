LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

SOURCE_FILES := $(wildcard $(LOCAL_PATH)/../../Sources/*.cpp)
SOURCE_FILES += $(wildcard $(LOCAL_PATH)/../../Libraries/libpng-1.6.9/*.c)
SOURCE_FILES += $(wildcard $(LOCAL_PATH)/../../zlib-1.2.8/*.c)
#SOURCE_FILES += $(wildcard $(LOCAL_PATH)/../../Libraries/gcdpp/*.cpp)

LOCAL_MODULE := ieCore
LOCAL_CFLAGS := -Werror -D__NDK__ -DGXX_EXPERIMENTAL_CXX0X
LOCAL_CFLAGS += -O2
LOCAL_CFLAGS += -DNDEBUG 
#LOCAL_CFLAGS += -g
#LOCAL_CFLAGS += -ggdb
#LOCAL_CFLAGS += -O1
LOCAL_CPPFLAGS += -std=c++11
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Sources\
	 				$(LOCAL_PATH)/../../Libraries\
	 				$(LOCAL_PATH)/../../Libraries/glm-0.9.5.2\
	 				$(LOCAL_PATH)/../../Libraries/libpng-1.6.9\
					$(LOCAL_PATH)/../../Libraries/zlib-1.2.8\
					$(LOCAL_PATH)/../../Libraries/ogles2/include
LOCAL_SRC_FILES := $(SOURCE_FILES:$(LOCAL_PATH)/%=%)
LOCAL_STATIC_LIBRARIES := android_native_app_glue
include $(BUILD_STATIC_LIBRARY)
$(call import-module,android/native_app_glue)
