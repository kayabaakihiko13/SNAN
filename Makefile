CC = g++
CXXFLAGS = -g -O2 -Wall
LDFLAGS = -lncurses

# Direktori instalasi
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
HS_FILE = snakehs
TARGET = snake_game

# File source
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:.cc=.o)

# Warna untuk output terminal
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m

# Fungsi untuk print variabel
define print-var
	@printf "${YELLOW}%-12s${NC} = ${BLUE}%s${NC}\n" "$(1)" "$($(1))"
endef

.PHONY: all clean install uninstall run debug vars

all: vars $(TARGET)

$(TARGET): $(OBJS)
	@echo "\n${GREEN}🔗 Linking...${NC}"
	$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "${GREEN}✅ Build selesai!${NC}\n"

%.o: %.cc
	@echo "${GREEN}🔨 Compiling $<...${NC}"
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "\n${GREEN}🧹 Membersihkan...${NC}"
	rm -f $(OBJS) $(TARGET) $(HS_FILE)
	@echo "${GREEN}✅ File objek, binary, dan highscore dihapus${NC}\n"

install: $(TARGET)
	@echo "\n${GREEN}📦 Menginstal ke $(BINDIR)...${NC}"
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)
	rm -f $(HS_FILE)
	@echo "${GREEN}✅ Instalasi selesai!${NC}\n"

uninstall:
	@echo "\n${GREEN}🗑️ Menghapus instalasi...${NC}"
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
	rm -f $(HS_FILE)
	@echo "${GREEN}✅ Terima kasih telah menggunakan game ini${NC}\n"

run: $(TARGET)
	@echo "\n${GREEN}🎮 Menjalankan game...${NC}\n"
	./$(TARGET)

debug: CXXFLAGS += -DDEBUG -g3
debug: clean $(TARGET)
	@echo "\n${GREEN}🐛 Mode debug diaktifkan${NC}\n"
