.PHONY = run, clean

run: executable
	@./executable

executable:
  # It's ugly to include each cpp file manually, re-work. 
	@g++ src/main.cpp -o executable -I include src/Window/Window.cpp src/Swarm/Swarm.cpp src/Point/Point.cpp src/BoxBlur/BoxBlur.cpp -L lib -l SDL2-2.0.0

clean:
	@rm executable
