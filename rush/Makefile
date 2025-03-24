EX00_FILES = ex00/main.elf ex00/victim.elf ex00/tester.elf
EX01_FILES = ex01/main.elf ex01/victim.elf ex01/tester.elf

FILES = $(EX00_FILES) $(EX01_FILES) $(EX02_FILES) 

ex00: $(EX00_FILES)
	cd ex00 && ./tester.elf

ex01: $(EX01_FILES)
	cd ex01 && ./tester.elf

%.elf: %.c
	cc -Wall -Werror -Wextra $< -o $@

clean:
	rm -rf $(FILES)

.PHONY: ex00 ex01 ex02