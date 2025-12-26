with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Zad8 is
  n, p, t, m : Integer;
begin
  Put_Line("Podaj: n p");
  Get(n);
  Get(p);

  t := n;
  m := 0;

  while t >= 1 loop
    m := m * p + (t mod p);
    t := t / p;
  end loop;

  if m = n then Put_Line("TAK");
  else Put_Line("NIE");
  end if;
end Zad8;