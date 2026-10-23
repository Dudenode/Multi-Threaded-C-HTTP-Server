CC = clang
CFLAGS = -g -Wall -Iinclude
LDFLAGS = -lpthread

SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

TARGET = $(BIN_DIR)/server

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)