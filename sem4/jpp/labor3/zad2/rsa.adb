with Ada.Numerics.Discrete_Random;

package body RSA is
  function GCD (A, B : Long_Long_Integer) return Long_Long_Integer is
    Temp_A : Long_Long_Integer := A;
    Temp_B : Long_Long_Integer := B;
    Temp   : Long_Long_Integer;
  begin
    while Temp_B /= 0 loop
      Temp := Temp_B;
      Temp_B := Temp_A mod Temp_B;
      Temp_A := Temp;
    end loop;
    return Temp_A;
  end GCD;

  function Extended_GCD
   (A, B : Long_Long_Integer; X, Y : out Long_Long_Integer)
    return Long_Long_Integer
  is
    X1, Y1, D : Long_Long_Integer;
  begin
    if B = 0 then
      X := 1;
      Y := 0;
      return A;
    end if;

    D := Extended_GCD (B, A mod B, X1, Y1);
    X := Y1;
    Y := X1 - Y1 * (A / B);
    return D;
  end Extended_GCD;

  function Mod_Inverse (A, M : Long_Long_Integer) return Long_Long_Integer is
    X, Y, G : Long_Long_Integer;
  begin
    G := Extended_GCD (A, M, X, Y);
    if G /= 1 and G /= -1 then
      raise Invalid_Argument with "Non-existent inverse element error";
    end if;
    return (X mod M + M) mod M;
  end Mod_Inverse;

  function Power (Base : T; Exp : Long_Long_Integer) return T is
    Result : T := To_Element (1);
    B      : T := Base;
    E      : Long_Long_Integer := Exp;
  begin
    while E > 0 loop
      if E mod 2 = 1 then
        Result := Result * B;
      end if;
      B := B * B;
      E := E / 2;
    end loop;
    return Result;
  end Power;

  package Random_LLI is new Ada.Numerics.Discrete_Random (Long_Long_Integer);

  function Create (P, Q : Long_Long_Integer) return RSA_Info is
    Info     : RSA_Info;
    Gen      : Random_LLI.Generator;
    Rand_Val : Long_Long_Integer;
  begin
    Info.P := P;
    Info.Q := Q;
    Info.N := P * Q;

    if Info.N /= Ring_Mod then
      raise Invalid_Argument
       with "Product of p and q does not fit to the ring characteristics";
    end if;

    Info.Phi := (P - 1) * (Q - 1);

    Random_LLI.Reset (Gen);

    loop
      Rand_Val := Random_LLI.Random (Gen);
      Info.E := (abs Rand_Val mod (Info.Phi - 2)) + 2;
      exit when GCD (Info.E, Info.Phi) = 1;
    end loop;

    Info.D := Mod_Inverse (Info.E, Info.Phi);

    return Info;
  end Create;

  function Get_Modulo (Info : RSA_Info) return Long_Long_Integer is
  begin
    return Info.N;
  end Get_Modulo;

  function Get_Public_Key (Info : RSA_Info) return T is
  begin
    return To_Element (Info.E);
  end Get_Public_Key;

  function Encrypt (Info : RSA_Info; M : T) return T is
  begin
    return Power (M, Info.E);
  end Encrypt;

  function Decrypt (Info : RSA_Info; S : T) return T is
  begin
    return Power (S, Info.D);
  end Decrypt;
end RSA;
