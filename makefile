.PHONY = run, clean

run: executable
	@./executable

executable:
	@g++ src/main.cpp -o executable -I include -L lib -l SDL2-2.0.0

clean:
	@rm executable
