with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Strings.Fixed;   use Ada.Strings.Fixed;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Zad5 is
  function binomialCoefficient(n, k : in Natural) return Natural is
    k_cpy : Natural := Natural'Min(k, n - k);
    min : Natural;
    arr : array(0 .. k) of Natural;
  begin
    if k_cpy = 0 then return 1; end if;

    arr(0) := 1;

    for i in 1 .. n loop
      if i <= k_cpy then 
        min := i - 1;
        arr(i) := 1;
      else
        min := k_cpy;
      end if;

      for j in reverse 1 .. min loop
        arr(j) := arr(j) + arr(j - 1);
      end loop;
    end loop;

    return arr(k_cpy);
  end binomialCoefficient;

  function img(number : in Natural) return String is
  begin
    return Trim(number'Image, Ada.Strings.Left);
  end img;


  n, k : Natural;
begin
  Put_Line("Podaj: n k");
  Get(n); Get(k);

  Put_Line("Dwumian(" & img(n) & ", " & img(k) & ") = " & img(binomialCoefficient(n, k)));
end Zad5;