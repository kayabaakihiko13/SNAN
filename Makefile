# Compiler dan flags
CC = g++
CXXFLAGS = -g -O2 -Wall
LDFLAGS = -lncurses

# Direktori instalasi
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
TARGET = snake_game

# File source
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:.cc=.o)

# Warna untuk output terminal
GREEN = \033[0;32m
NC = \033[0m

.PHONY: all clean install uninstall run debug

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "$(GREEN)Linking...$(NC)"
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "$(GREEN)Build selesai!$(NC)"

%.o: %.cc
	@echo "$(GREEN)Compiling $<...$(NC)"
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "$(GREEN)Membersihkan...$(NC)"
	rm -f $(OBJS) $(TARGET)

install: $(TARGET)
	@echo "$(GREEN)Menginstal ke $(BINDIR)...$(NC)"
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)

uninstall:
	@echo "$(GREEN)Menghapus instalasi...$(NC)"
	@echo "$(GREEN)Terima Kasih atas menginstall game ini"
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)

run: $(TARGET)
	@echo "$(GREEN)Menjalankan game...$(NC)"
	./$(TARGET)

debug: CXXFLAGS += -DDEBUG -g3
debug: clean $(TARGET)
