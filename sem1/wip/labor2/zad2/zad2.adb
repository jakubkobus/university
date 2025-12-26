with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Zad2 is
  function NWD(a, b : in Integer) return Positive is
    a_cpy, b_cpy, c : Integer;
  begin
    a_cpy := a;
    b_cpy := b;

    while b_cpy /= 0 loop
      c := b_cpy;
      b_cpy := a_cpy mod b_cpy;
      a_cpy := c;
    end loop;

    return abs(a_cpy);
  end NWD;

  a, b : Integer;
begin
  Put_Line("Podaj: a b");
  Get(a);
  Get(b);

  Put_Line("NWD =" & NWD(a, b)'Image);
end Zad2;