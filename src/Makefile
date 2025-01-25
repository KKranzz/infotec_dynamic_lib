# Переменные
CXX := g++
CXXFLAGS := -Wall -Werror -Wextra
LIB_SRC := ./lib/lib_logger.cpp
LIB_OBJ := ./build/lib_logger.o
LIB_SO := ./build/lib_logger.so
APP_SRC := ./application/main.cpp ./application/logger_client.cpp
APP_BIN := ./build/logger_client
BUILD_DIR := ./build

# Цели
.PHONY: all clean rebuild lib

all: lib app

# Цель для библиотеки
lib: $(LIB_SO)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIB_OBJ): $(LIB_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -fPIC $(LIB_SRC) -o $(LIB_OBJ)

$(LIB_SO): $(LIB_OBJ)
	$(CXX) -shared -o $(LIB_SO) $(LIB_OBJ)

# Цель для приложения
app: $(LIB_SO) $(APP_BIN)

$(APP_BIN): $(APP_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(APP_BIN) $(APP_SRC) $(LIB_SO)

clean:
	rm -rf $(BUILD_DIR)/*

rebuild: clean all
