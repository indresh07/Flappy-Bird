#  Author : Indresh Kumar Gupta
#  Purpose : To compile all the cpp files
#  Version : 1.2

libs := -Wno-deprecated -lGL -lGLU -lglut -lncurses -std=c++0x -L../GameEngine/bin -lge `pkg-config --cflags --libs sdl2 glew`
objDir := obj
incDir := include
srcDir := src
binDir := bin
files := $(basename $(notdir $(wildcard src/*)))
all:
	@make --no-print-directory object
	@make --no-print-directory executable

executable: main.cpp | $(binDir) 
	@echo -n "Generating flappy... "
	@g++ -o $(binDir)/flappy main.cpp $(files:%=$(objDir)/%.o) $(libs) 
	@echo "Done"

object: $(files:%=$(objDir)/%.o)

$(objDir)/%.o : $(srcDir)/%.cpp | $(objDir)
	@echo -n "Generating $(notdir $@)... "
	@g++ -c -o $@ $< $(libs)
	@echo "Done"

$(binDir)/% : $(objDir)/%.o  | $(binDir)
	@echo -n "Generating $(notdir $@)... "
	@g++ -o $@ $< $(libs)
	@echo "Done"

$(objDir):
	@mkdir $(objDir)

$(binDir):
	@mkdir $(binDir)

clean:
	@rm -f $(binDir)/*
	@rm -f $(objDir)/*
	@rmdir $(binDir)
	@rmdir $(objDir)