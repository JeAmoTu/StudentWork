CC := gcc
Target := park_manage
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += main choose charge count_wait_queue init interface is_empty_queue is_full_stack is_malloc my_strcmp out park pop_park_stack push_link_queue push_park_stack push_temp_stack see
Allobjs := $(addsuffix /src/*.o,$(Modules))
