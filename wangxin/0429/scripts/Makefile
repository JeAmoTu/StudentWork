CC := gcc
CFLAGS := -Wall -O3
Target := main1
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += main add sub
Allobjs := $(addsuffix /src/*.o,$(Modules))
