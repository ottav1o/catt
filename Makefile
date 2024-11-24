# Compiler settings
CC     = gcc
CFLAGS = -Wall -Wextra
LIBS   = 

# Color configuration
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BOLD   = \033[1m
ITALIC = \033[3m
RESET  = \033[0m

# Variables
SOURCE     = ./src
BUILD_DIR  = ./dist
BINARY_OUT = $(BUILD_DIR)/bin
CFILES     = $(wildcard $(SOURCE)/*.c)
HEADERS    = $(wildcard $(SOURCE)/*.h)

TARGET_OBJECTS = $(CFILES:$(SOURCE)/%.c=$(BUILD_DIR)/%.o)

TARGET = $(BINARY_OUT)/catt

all: $(TARGET)

$(BINARY_OUT):
	@mkdir -p $@

$(BUILD_DIR):
	@mkdir -p $@

$(TARGET): $(TARGET_OBJECTS) | $(BUILD_DIR) $(BINARY_OUT)
	@echo -e '$(BOLD)Linking:$(RESET) "$^" $(ITALIC)-->$(RESET) "$@"'
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SOURCE)/%.c $(HEADERS) | $(BUILD_DIR)
	@echo -e '$(GREEN)Compiling$(RESET) "$<" --> "$@"'
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

info:
	@echo -e '$(BOLD)Compiler        :$(RESET) $(CC)'
	@echo -e '$(BOLD)Compiler Flags  :$(RESET) $(CFLAGS)'
	@echo -e '$(BOLD)Source directory:$(RESET) $(SOURCE)'
	@echo -e '$(BOLD)Build directory :$(RESET) $(BUILD_DIR)'
	@echo -e '$(BOLD)Source files    :$(RESET) $(CFILES)'
	@echo -e '$(BOLD)Header files    :$(RESET) $(HEADERS)'
	@echo -e '$(BOLD)Objects         :$(RESET) $(TARGET_OBJECTS)'
	@echo -e '$(BOLD)Target          :$(RESET) $(TARGET)'
	@echo -e '$(BOLD)Link option     :$(RESET) $(LIBS)'

.PHONY: all info clean

