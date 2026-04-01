with Ada.Text_IO; use Ada.Text_IO;
with ModuloRing;

procedure Main is
  package Ring7 is new ModuloRing (N => 7);
  package Ring6 is new ModuloRing (N => 6);

  use Ring7;
  use Ring6;

  function To_Str (B : Boolean) return String
  is (if B then "true" else "false");

begin
  begin
    Put_Line ("--- Z7 (Ring<7>) ---");
    Put_Line ("[IN] a = 10, b = -4");

    declare
      A : Ring7.Ring := To_Ring (10);
      B : Ring7.Ring := To_Ring (-4);
    begin
      Put_Line ("a =" & To_Integer (A)'Img);
      Put_Line ("b =" & To_Integer (B)'Img);

      Put_Line ("a == b -> " & To_Str (A = B));
      Put_Line ("a + b =" & To_Integer (A + B)'Img);

      Put_Line ("a * 5 =" & To_Integer (A * To_Ring (5))'Img);
      Put_Line ("a / 2 =" & To_Integer (A / To_Ring (2))'Img);
      Put_Line ("a ^ 2 =" & To_Integer (A * A)'Img);
    end;
  exception
    when E : others =>
      Put_Line (Standard_Error, "[WARN] Exception catched in Ring7 section");
  end;

  Put_Line ("");
  Put_Line ("--- Z6 (Ring<6>) ---");
  Put_Line ("[IN] x = 5, y = 2");

  declare
    X : Ring6.Ring := Ring6.To_Ring (5);
    Y : Ring6.Ring := Ring6.To_Ring (2);
    Z : Ring6.Ring;
  begin
    Put_Line ("x =" & To_Integer (X)'Img);
    Put_Line ("y =" & To_Integer (Y)'Img);
    Put_Line ("x * y =" & To_Integer (X * Y)'Img);

    Put_Line ("");
    Put_Line ("Exception handling:");
    Put_Line ("Dividing x / y ...");

    Z := X / Y;
  exception
    when Ring6.No_Inverse =>
      Put_Line
       (Standard_Error,
        "[WARN] Exception catched: Non-existent inverse element error"
        & Ring6.To_Integer (Y)'Img
        & "^(-1)");
    when Ring6.Division_By_Zero =>
      Put_Line
       (Standard_Error, "[WARN] Exception catched: Zero division error");
    when others =>
      Put_Line (Standard_Error, "[WARN] Unknown exception catched");
  end;

  Put_Line ("");
  Put_Line ("Dividing by zero...");
  declare
    Result : Ring7.Ring;
  begin
    Result := To_Ring (5) / To_Ring (0);
  exception
    when Ring7.Division_By_Zero =>
      Put_Line
       (Standard_Error, "[WARN] Exception catched: Zero division error");
    when others =>
      Put_Line (Standard_Error, "[WARN] Unknown exception catched");
  end;
end Main;
