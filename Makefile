CC = clang++
CFLAGS = -Wall -Wextra -g 
LDFLAGS = -lncurses -lasound -lpthread

# Direktori dan file
SRC_DIR = src
INC_DIR = include
SRC = $(SRC_DIR)/main.cc
OBJ = $(SRC:.cc=.o)
TARGET = snake_game

# Warna untuk output terminal
GREEN = \033[0;32m
NC = \033[0m

.PHONY: all clean run rebuild

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "$(GREEN)Linking...$(NC)"
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "$(GREEN)Build selesai!$(NC)"

%.o: %.c
	@echo "$(GREEN)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(GREEN)Membersihkan...$(NC)"
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	@echo "$(GREEN)Menjalankan game...$(NC)"
	./$(TARGET)

rebuild: clean all
