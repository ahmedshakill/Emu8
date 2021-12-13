LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
SDL_image_PATH := ../SDL_image

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SDL_image_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := main.cpp chip8.cpp OpCodeInstruction.cpp game.cpp  LoadROM.cpp menu.cpp controller.cpp #YourSourceHere.c

LOCAL_SHARED_LIBRARIES := SDL2 \
SDL2_image \
# SDL2_ttf \
# SDL2_mixer \
# SDL2_net

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -landroid

include $(BUILD_SHARED_LIBRARY)
