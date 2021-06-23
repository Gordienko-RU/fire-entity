.PHONY = run

run: executable
	@./executable

executable:
	@g++ main.cpp -o executable
