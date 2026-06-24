GHC = ghc
GHC_FLAGS = -dynamic
HS_SRC = main.hs
HS_BIN = main_hs

OCAML = ocamlopt
ML_SRC = main.ml
ML_BIN = main_ml

SML = mlton
SML_SRC = main.sml
SML_BIN = main_sml

.PHONY: all run run_hs run_ml run_sml clean haskell ocaml sml

all: haskell ocaml sml

haskell: $(HS_SRC)
	$(GHC) $(GHC_FLAGS) $(HS_SRC) -o $(HS_BIN)

ocaml: $(ML_SRC)
	$(OCAML) $(ML_SRC) -o $(ML_BIN)

sml: $(SML_SRC)
	$(SML) -output $(SML_BIN) $(SML_SRC)

run:
	./$(HS_BIN)
	./$(ML_BIN)
	./$(SML_BIN)

run_hs:
	./$(HS_BIN)

run_ml:
	./$(ML_BIN)

run_sml:
	./$(SML_BIN)

clean:
	rm -f $(HS_BIN) $(ML_BIN) $(SML_BIN)
	rm -f *.o *.hi
	rm -f *.cmi *.cmx
