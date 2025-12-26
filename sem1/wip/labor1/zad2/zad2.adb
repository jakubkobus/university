with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Zad2 is
  a, b, c : Integer;
begin
  Put_Line("Podaj: a b");
  Get(a);
  Get(b);

  while b /= 0 loop
    c := b;
    b := a mod b;
    a := c;
  end loop;

  if a < 0 then a := a * (-1); end if;

  Put_Line("NWD =" & a'Image);
end Zad2;