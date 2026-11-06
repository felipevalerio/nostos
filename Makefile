CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++17

SDL_DIR = C:/Libraries/SDL3/SDL3-3.4.20/x86_64-w64-mingw32
SDL_INCLUDE = $(SDL_DIR)/include
SDL_LIB = $(SDL_DIR)/lib
SDL_BIN = $(SDL_DIR)/bin

CXXFLAGS += -I$(SDL_INCLUDE)
LDFLAGS = -L$(SDL_LIB) -lSDL3

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = main.exe

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	powershell -NoProfile -Command "Copy-Item '$(SDL_BIN)/SDL3.dll' '.' -Force"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo Limpando pastas obj e bin...
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(TARGET) del $(TARGET)

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run