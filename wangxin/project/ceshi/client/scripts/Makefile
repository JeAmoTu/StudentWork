CC := gcc -lpthread -lsqlite3
Target := chat_client
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += main check_action create_msg interface interface1 set_disp_mode thread_read thread_write
Allobjs := $(addsuffix /src/*.o,$(Modules))
