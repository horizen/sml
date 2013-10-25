
C_SRCS += \
$(SRCPATH)/sml_queue.c \
$(SRCPATH)/sml_string.c \

OBJS += \
test_queue.so \
test_string.so \

$(OBJS): $(C_SRCS)
