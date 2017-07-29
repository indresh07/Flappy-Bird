#  Author : Indresh Kumar Gupta
#  Purpose : To compile all the cpp files
#  Version : 1.2

libs := -Wno-deprecated -lGL -lGLU -lglut -std=c++0x `pkg-config --cflags --libs sdl2 glew`
objDir := obj
incDir := include
srcDir := src
binDir := bin
files := $(basename $(notdir $(wildcard src/*)))
all:
	@make --no-print-directory object
	@make --no-print-directory lib

object: $(files:%=$(objDir)/%.o)

lib: $(files:%=$(objDir)/%.o) | $(binDir)
	@echo -n "Generating libge.a... "
	@ar crf $(binDir)/libge.a $(files:%=$(objDir)/%.o)
	@echo "Done"

$(objDir)/%.o : $(srcDir)/%.cpp | $(objDir)
	@echo -n "Generating $(notdir $@)... "
	@g++ -c -o $@ $< $(libs) -std=c++11
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