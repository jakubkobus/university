with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Strings.Fixed;   use Ada.Strings.Fixed;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Zad8 is
  function img(number : in Integer) return String is
  begin
    return Trim(number'Image, Ada.Strings.Left);
  end img;


  n : Integer;
  t : Integer := 3;
  i : Integer := 1;
  result : array(1 .. 31) of Integer;
begin
  Put("Podaj liczbe: ");
  Get(n);

  Put(img(n) & "=");

  while n mod 2 = 0 loop
    result(i) := 2;
    i := i + 1;
    n := n / 2;
  end loop;

  while n > 1 loop
    if t * t > n then
      result(i) := n;
      i := i + 1;
      n := 1;
    else
      while n mod t = 0 loop
        result(i) := t;
        i := i + 1;
        n := n / t;
      end loop;

      t := t + 2;
    end if;
  end loop;

  n := result(1);
  t := 1;

  for j in 2 .. i - 1 loop
    if result(j) = n then
      t := t + 1;
    else
      if t = 1 then Put(img(n) & "*");
      else Put(img(n) & "^" & img(t) & "*");
      end if;

      n := result(j);
      t := 1;
    end if;
  end loop;

  if t = 1 then Put_Line(img(n));
  else Put_Line(img(n) & "^" & img(t));
  end if;
end Zad8;
