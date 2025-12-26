with Ada.Text_IO;            use Ada.Text_IO;
with Ada.Integer_Text_IO;    use Ada.Integer_Text_IO;
with Ada.Containers.Vectors; use Ada.Containers;

procedure Zad8 is
  GUESS_MIN  : constant Integer := 1;
  GUESS_MAX  : constant Integer := 6;
  GUESS_SIZE : constant Integer := 4;

  type guessArr_t is array (1 .. GUESS_SIZE) of Integer;

  type CompareResult is record
    hits      : Integer;
    misplaced : Integer;
  end record;

  package Guess_Vector is new Vectors(Positive, guessArr_t);
  use Guess_Vector;

  function compare(correct : in guessArr_t; guess : in guessArr_t) return CompareResult is
    hits        : Integer := 0;
    misplaced   : Integer := 0;
    correctLeft : guessArr_t := (others => 0);
    guessLeft   : guessArr_t := (others => 0);
    countLeft   : Integer := 0;
  begin
    for i in correct'Range loop
      if correct(i) = guess(i) then
        hits := hits + 1;
      else
        countLeft := countLeft + 1;
        correctLeft(countLeft) := correct(i);
        guessLeft(countLeft) := guess(i);
      end if;
    end loop;

    for i in 1 .. countLeft loop
      for j in 1 .. countLeft loop
        if guessLeft(i) = correctLeft(j) and then correctLeft(j) /= 0 then
          misplaced := misplaced + 1;
          correctLeft(j) := 0;
          exit;
        end if;
      end loop;
    end loop;

    return (hits, misplaced);
  end compare;


  guess           : guessArr_t := (others => GUESS_MIN);
  allCombinations : Guess_Vector.Vector;
  hits            : Integer := 0;
  misplaced       : Integer := 0;
  attempt         : Integer := 0;
begin
  for i in GUESS_MIN .. GUESS_MAX loop
    for j in GUESS_MIN .. GUESS_MAX loop
      for k in GUESS_MIN .. GUESS_MAX loop
        for l in GUESS_MIN .. GUESS_MAX loop
          declare
            comb : guessArr_t := (i, j, k, l);
          begin
            allCombinations.Append(comb);
          end;
        end loop;
      end loop;
    end loop;
  end loop;

  while hits /= GUESS_SIZE loop
    attempt := attempt + 1;

    Put(attempt'Img & ":");
    for i in 1 .. GUESS_SIZE loop
      Put(guess(i)'Img);
    end loop;
    Put_Line(" ?");

    Put("Na swoim miejscu: ");
    Get(hits);

    Put("Nie na swoim miejscu: ");
    Get(misplaced);

    declare
      validCombinations : Guess_Vector.Vector;
    begin
      for comb of allCombinations loop
        if Compare(comb, guess) = (hits, misplaced) then
          validCombinations.Append(comb);
        end if;
      end loop;

      if validCombinations.Length > 0 then
        guess := validCombinations(1);
        allCombinations := validCombinations;
      else
        Put_Line("Oszukujesz!");
        return;
      end if;
    end;
  end loop;

  Put_Line("Wygralem!");
end Zad8;
