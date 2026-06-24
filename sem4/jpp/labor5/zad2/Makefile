PL = swipl
PL_FLAGS = --goal=main --stand_alone=true
PL_SRC = main.pl
PL_BIN = main_pl

.PHONY: all run clean

all: $(PL_BIN)

$(PL_BIN): $(PL_SRC)
	$(PL) $(PL_FLAGS) -o $(PL_BIN) -c $(PL_SRC)

run:
	./$(PL_BIN)

clean:
	rm -f $(PL_BIN)
