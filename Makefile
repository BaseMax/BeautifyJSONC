COMPILER = cc
CFLAGS = -O2 -g -Wall -Werror

all: beautify_json

beautify_json:
	@echo "[+] Building project..."
	$(COMPILER) $(CFLAGS) -o beautify_json ./src/beautify_json.c ./src/main.c

clean:
	@echo "[+] Cleaning..."
	rm -f beautify_json
