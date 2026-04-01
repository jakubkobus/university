package body ModuloRing is
  function Extended_GCD (A, B : Integer; X, Y : out Integer) return Integer is
    X1, Y1, GCD : Integer;
  begin
    if B = 0 then
      X := 1;
      Y := 0;
      return A;
    end if;

    GCD := Extended_GCD (B, A rem B, X1, Y1);
    X := Y1;
    Y := X1 - Y1 * (A / B);
    return GCD;
  end Extended_GCD;

  function Mod_Inverse (A, M : Integer) return Integer is
    X, Y, GCD : Integer;
  begin
    GCD := Extended_GCD (A, M, X, Y);
    if GCD /= 1 and GCD /= -1 then
      raise No_Inverse;
    end if;

    return (X mod M);
  end Mod_Inverse;

  function To_Ring (Value : Integer) return Ring is
  begin
    return (Value => Value mod N);
  end To_Ring;

  function To_Integer (Item : Ring) return Integer is
  begin
    return Item.Value;
  end To_Integer;

  function "+" (Left, Right : Ring) return Ring is
  begin
    return To_Ring (Left.Value + Right.Value);
  end "+";

  function "-" (Left, Right : Ring) return Ring is
  begin
    return To_Ring (Left.Value - Right.Value);
  end "-";

  function "*" (Left, Right : Ring) return Ring is
  begin
    return To_Ring (Left.Value * Right.Value);
  end "*";

  function "/" (Left, Right : Ring) return Ring is
    Inv : Integer;
  begin
    if Right.Value = 0 then
      raise Division_By_Zero;
    end if;

    Inv := Mod_Inverse (Right.Value, N);
    return To_Ring (Left.Value * Inv);
  end "/";

  function "<" (Left, Right : Ring) return Boolean is
  begin
    return Left.Value < Right.Value;
  end "<";

  function ">" (Left, Right : Ring) return Boolean is
  begin
    return Left.Value > Right.Value;
  end ">";

  function "<=" (Left, Right : Ring) return Boolean is
  begin
    return Left.Value <= Right.Value;
  end "<=";

  function ">=" (Left, Right : Ring) return Boolean is
  begin
    return Left.Value >= Right.Value;
  end ">=";
end ModuloRing;
