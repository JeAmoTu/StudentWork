CC := gcc -lsqlite3
Target := chat_server
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += callback deal_action main
Allobjs := $(addsuffix /src/*.o,$(Modules))
