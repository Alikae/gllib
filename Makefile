VULKAN_SDK_PATH =       /home/god/prog/libs/sdk.1.1.121.0/x86_64

LDFLAGS         =       -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
CFLAGS		=	-I$(VULKAN_SDK_PATH)/include

SRCS	=	srcs/main.c \
		srcs/graphics.c \
		srcs/shaders.c \
		srcs/read_file.c \
		glad/glad.c

all:
	gcc -g3 $(CFLAGS) $(SRCS) -I. $(LDFLAGS)

dbg:
	gcc -g $(CFLAGS) $(SRCS) -I. $(LDFLAGS)

clean:
	/bin/rm -f a.out
