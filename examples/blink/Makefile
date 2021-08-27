NAME_MODULE = blink
OBJ_DIR = build_$(NAME_MODULE)
CXX=/home/fanning/workspace/f1c100s/licheepi_nano_sdk/buildroot-2021.02.3/buildroot-2021.02.3/output/host/bin/arm-buildroot-linux-gnueabi-g++
CC=/home/fanning/workspace/f1c100s/licheepi_nano_sdk/buildroot-2021.02.3/buildroot-2021.02.3/output/host/bin/arm-buildroot-linux-gnueabi-gcc

#CXX=/home/fanning/workspace/f1c100s/licheepi_nano_sdk/toolchain/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++
#CC=/home/fanning/workspace/f1c100s/licheepi_nano_sdk/toolchain/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc

CFLAGS += -I.

LDFLAGS	+= -L.

OBJ = $(OBJ_DIR)/blink.o

#Library libs
LDLIBS	+= $(LIBS) \
		-lpthread		\
		-lrt			\
		-lm 			\
		-lfagpio		\
		-Xlinker -rpath=.	\

IP_ADDR = 192.168.1.100
all: create $(OBJ_DIR)/$(NAME_MODULE)
create:
	@echo mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o: %.c
	@echo CXX $<
	@$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS) $(LDLIBS)
$(OBJ_DIR)/$(NAME_MODULE): $(OBJ)
	@echo ---------- START LINK PROJECT ----------
	@echo $(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)
.PHONY: clean
clean:
	@echo rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR) *.o	

.PHONY: lib
lib:
	$(CC) -c -Wall -Werror -fpic fagpio.c
	$(CC) -shared -o libfagpio.so fagpio.o

.PHONY: copy
copy:
	sshpass -p "000" scp -r ./$(OBJ_DIR)/$(NAME_MODULE) root@$(IP_ADDR):/rom/
