#
# This file is part of mutest, a simple micro unit testing framework for C.
#
# mutest was written by Leandro Lucarella <llucax@gmail.com> and is released
# under the BOLA license, please see the LICENSE file or visit:
# http://blitiri.com.ar/p/bola/
#
# This is the samples Makefile.
#
# Please, read the README file for more details.
#

# Show the tests summary
V = -v

# Set to 0 if you don't want to compile the C++ test suite
CPP_SUITE = 1
SRCPATH = ..
CFLAGS = -Wall -std=c99
LD = $(CC)
LDFLAGS = -I$(SRCPATH)/src/
MUTEST = mutest

TEST_OBJS = test_string.o test_queue.o test_random.o
TEST_SOS = $(TEST_OBJS:.o=.so)


all: test-py

test-py: $(TEST_SOS)

-include subdir.mk

clean:
	$(RM) $(TEST_SOS)

.c.so:
	$(CC) $(CFLAGS) $(LDFLAGS) -DMUTEST_PY -fPIC -shared -o $@ $^


.SUFFIXES: .so

.PHONY: all test clean

