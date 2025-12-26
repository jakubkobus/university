with Ada.Text_IO;       use Ada.Text_IO;
with Ada.Command_Line;  use Ada.Command_Line;
with Ada.Strings.Fixed; use Ada.Strings.Fixed;

with Lib;

procedure Zad5 is
  n : Natural;
begin
  for i in 1 .. Argument_Count loop
    n := Integer'Value(Argument(i));
    
    Put_Line("totient(" & Argument(i) & ") = " & Lib.totient(n)'Image);
  end loop;
  
end Zad5;