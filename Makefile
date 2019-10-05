
CORE = core/Asteroid.cpp core/Cow.cpp core/Hunter.cpp core/Health.cpp core/Position.cpp core/Score.cpp core/Terrain.cpp core/World.cpp core/Object.cpp

SRCS_TXT = $(CORE) txt/txtgame.cpp txt/maintxt.cpp
FINAL_TARGET_TXT = spacecow_txt

SRCS_SDL = $(CORE) sdl2/sdlGame.cpp sdl2/mainsdl.cpp
FINAL_TARGET_SDL = spacecow_sdl

ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SDL = -Iextern/SDL2_mingw/SDL2-2.0.3/include \
						-Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2 \
						-Iextern/ncursesw/include/
	LIBS_SDL = 	-Lextern \
			-Lextern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_mixer-2.0.1/i686-w64-mingw32/lib \
			-Lextern/ncursesw/lib/ \
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll -lncurses
else
	INCLUDE_DIR_SDL = -I/usr/include/SDL2 # SDL2 Library
	LIBS_SDL = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	INCLUDE_DIR_NCURSES = -I/usr/include # ncurses library
	LIBS_NCURSES = -lncurses -pedantic
endif

CC					= g++
LD 					= g++
LDFLAGS  			=
CPPFLAGS 			= -Wall -ggdb -std=c++11  #-O2   # pour optimiser
OBJ_DIR 			= obj
SRC_DIR 			= src
BIN_DIR 			= bin
INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/sdl2 -Isrc/txt

default: make_dir $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SDL)

make_dir:
ifeq ($(OS),Windows_NT)
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR) $(OBJ_DIR)\txt $(OBJ_DIR)\sdl2 $(OBJ_DIR)\core
else
	 test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) $(OBJ_DIR)/txt $(OBJ_DIR)/sdl2 $(OBJ_DIR)/core
	 test -d $(BIN_DIR) || mkdir -p $(BIN_DIR)
endif

$(BIN_DIR)/$(FINAL_TARGET_TXT): $(SRCS_TXT:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_NCURSES)

$(BIN_DIR)/$(FINAL_TARGET_SDL): $(SRCS_SDL:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_SDL)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR_SDL) $(INCLUDE_DIR_NCURSES) $(INCLUDE_DIR) $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJ_DIR)\txt\*.o $(OBJ_DIR)\sdl2\*.o $(OBJ_DIR)\core\*.o $(BIN_DIR)\$(FINAL_TARGET_TXT).exe $(BIN_DIR)\$(FINAL_TARGET_SDL).exe
else
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SDL)
endif

doc: $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SDL)
	doxygen doc/space_cow.doxy
