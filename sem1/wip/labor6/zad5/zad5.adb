with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Command_Line;    use Ada.Command_Line;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Zad5 is
  type intArr_t is array(Positive range <>) of Integer;
  type boolArr_t is array(Positive range <>) of Boolean;

  procedure printArray(position : in out intArr_t) is
  begin
    for i in position'Range loop
      Put(Integer'Image(position(i) + 1) & " ");
    end loop;
    New_Line;
  end printArray;

  procedure USTAW(
    i           : Integer;
    position    : in out intArr_t;
    n           : Integer;
    bije_wiersz : in out boolArr_t;
    bije_przek1 : in out boolArr_t;
    bije_przek2 : in out boolArr_t;
    sol         : in out Integer) is
  begin
    for j in 1 .. n loop
      if not (bije_wiersz(j) or bije_przek1(i + j) or bije_przek2(i - j + n)) then
        position(i) := j;
        bije_wiersz(j) := True;
        bije_przek1(i + j) := True;
        bije_przek2(i - j + n) := True;

        if i < n then
          USTAW(i + 1, position, n, bije_wiersz, bije_przek1, bije_przek2, sol);
        else
          printArray(position);
          sol := sol + 1;
        end if;

        position(i) := 0;
        bije_wiersz(j) := False;
        bije_przek1(i + j) := False;
        bije_przek2(i - j + n) := False;
      end if;
    end loop;
  end Ustaw;

  procedure HETMAN(n : Integer) is
    position    : intArr_t(1 .. N) := (others => 0);
    bije_wiersz : boolArr_t(1 .. N) := (others => False);
    bije_przek1 : boolArr_t(1 .. 2 * N) := (others => False);
    bije_przek2 : boolArr_t(1 .. 2 * N) := (others => False);
    solutions   : Integer := 0;
  begin
    USTAW(1, position, n, bije_wiersz, bije_przek1, bije_przek2, solutions);
    Put_Line("Number of solutions: " & solutions'Img);
  end Hetman;

  n : Integer;
begin
  n := Integer'Value(Argument(1));
  HETMAN(n);
end Zad5;
