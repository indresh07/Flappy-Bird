all: 
	@make --no-print-directory lib
	@make --no-print-directory flappy

lib:
	@$(MAKE) --no-print-directory -C GameEngine/

flappy:
	@$(MAKE) --no-print-directory -C FlappyBirds\ v2.0/

clean:
	@echo -n "Deleting files... "
	@$(MAKE) --no-print-directory clean -C GameEngine/
	@$(MAKE) --no-print-directory clean -C FlappyBirds\ v2.0/
	@echo "Done"