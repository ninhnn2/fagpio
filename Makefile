NAME_MODULE = fagpio
OBJ_DIR = build_$(NAME_MODULE)
CXX=/home/fanning/workspace/f1c100s/licheepi_nano_sdk/buildroot-2021.02.3/buildroot-2021.02.3/output/host/bin/arm-buildroot-linux-gnueabi-g++
CC=/home/fanning/workspace/f1c100s/licheepi_nano_sdk/buildroot-2021.02.3/buildroot-2021.02.3/output/host/bin/arm-buildroot-linux-gnueabi-gcc

CFLAGS = -I.
OBJ = $(OBJ_DIR)/fagpio.o
IP_ADDR = 192.168.1.100

#all: create $(OBJ_DIR)/$(NAME_MODULE)
all: lib

create:
	@echo mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o: %.c
	@echo CXX $<
	@$(CC) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/$(NAME_MODULE): $(OBJ)
	@echo ---------- START LINK PROJECT ----------
	@echo $(CC) -o $@ $^ $(CFLAGS)
	@$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean
clean:
	@echo rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR) *.o	

.PHONY: lib
lib:
	$(CC) -c -Wall -Werror -fpic fagpio.c
	$(CC) -shared -o libfagpio.so fagpio.o

#.PHONY: install
#install:
#	cp libfagpio.so /home/fanning/workspace/f1c100s/licheepi_nano_sdk/rootfs/lib/fagpio/
#	cp fagpio.h /home/fanning/workspace/f1c100s/licheepi_nano_sdk/rootfs/lib/fagpio/

.PHONY: copy
copy:
	sshpass -p "000" scp $(OBJ_DIR)/$(NAME_MODULE) root@$(IP_ADDR):/rom/work


