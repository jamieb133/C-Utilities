CC = clang
AR = ar

BUILD_DIR = build
CUTILS_LIB = $(BUILD_DIR)/cutils.a
SRC_DIR = src
INC_DIR = inc
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

TEST_DIR = test
TEST_BUILD_DIR = $(BUILD_DIR)/test
TEST_EXE = $(TEST_BUILD_DIR)/test
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(TEST_BUILD_DIR)/%.o,$(TEST_SRCS))

CFLAGS = -g -Iinc -O0
LDFLAGS = -lm -pthread

ifeq ($(SAN),asan)
	CFLAGS += -fsanitize=address
	LDFLAGS += -fsanitize=address
else ifeq ($(SAN),tsan)
	CFLAGS += -fsanitize=thread
	LDFLAGS += -fsanitize=thread
endif

all: dirs $(CUTILS_LIB) $(TEST_EXE)

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(TEST_BUILD_DIR)

$(CUTILS_LIB): $(OBJS)
	@echo "Linking $<"
	$(AR) rcs $@ $(OBJS)	

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c dirs
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -Wall -Wextra -c $< -o $@

$(TEST_EXE): $(CUTILS_LIB) $(TEST_OBJS)
	@echo "Linking $<"
	$(CC) $(TEST_OBJS) $(CUTILS_LIB) -o $@ $(LDFLAGS)

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXE)
	@$(TEST_EXE)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all dirs clean test

