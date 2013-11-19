
C_SRCS += \
$(SRCPATH)/sml_queue.c \
$(SRCPATH)/sml_string.c \
$(SRCPATH)/sml_random.c 

OBJS += \
test_queue.so \
test_string.so \
test_random.so

$(OBJS): $(C_SRCS)
