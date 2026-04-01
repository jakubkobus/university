package body My_Lib is
  function GCD (A, B : Unsigned_64) return Unsigned_64 is
    Temp_A : Unsigned_64 := A;
    Temp_B : Unsigned_64 := B;
    Temp   : Unsigned_64;
  begin
    while Temp_B /= 0 loop
      Temp := Temp_B;
      Temp_B := Temp_A mod Temp_B;
      Temp_A := Temp;
    end loop;

    return Temp_A;
  end GCD;

  function SmallestPrimeFactor (N : Unsigned_64) return Unsigned_64 is
    I : Unsigned_64 := 3;
  begin
    if N <= 1 then
      return 0;
    end if;

    if N mod 2 = 0 then
      return 2;
    end if;

    while I * I <= N loop
      if N mod I = 0 then
        return I;
      end if;

      I := I + 2;
    end loop;

    return N;
  end SmallestPrimeFactor;

  function Totient (N : Unsigned_64) return Unsigned_64 is
    Result : Unsigned_64 := N;
    Temp_N : Unsigned_64 := N;
    P      : Unsigned_64 := 2;
  begin
    if Temp_N = 0 then
      return 0;
    end if;

    while P * P <= Temp_N loop
      if Temp_N mod P = 0 then
        while Temp_N mod P = 0 loop
          Temp_N := Temp_N / P;
        end loop;

        Result := Result - (Result / P);
      end if;

      P := P + 1;
    end loop;

    if Temp_N > 1 then
      Result := Result - (Result / Temp_N);
    end if;

    return Result;
  end Totient;

  function ExtendedGCD
   (A, B : Integer_64; X, Y : out Integer_64) return Integer_64
  is
    X1, Y1, G : Integer_64;
  begin
    if A = 0 then
      X := 0;
      Y := 1;
      return B;
    end if;

    G := ExtendedGCD (B mod A, A, X1, Y1);
    X := Y1 - (B / A) * X1;
    Y := X1;

    return G;
  end ExtendedGCD;

  function SolveDiophantine (A, B, C : Unsigned_64) return Solution is
    Sol                       : Solution :=
     (X => 0, Y => 0, HasSolution => False);
    S_A, S_B, S_C             : Integer_64;
    X0, Y0, G                 : Integer_64;
    A_Prime, B_Prime, C_Prime : Integer_64;
    X_Base, Y_Base, Y_Temp    : Integer_64;
    K_X, K_Y, K               : Integer_64;
  begin
    S_A := Integer_64 (A);
    S_B := Integer_64 (B);
    S_C := Integer_64 (C);

    if S_A = 0 and S_B = 0 then
      if S_C = 0 then
        Sol.HasSolution := True;
      end if;

      return Sol;
    end if;

    if S_A = 0 then
      return Sol;
    end if;

    G := ExtendedGCD (S_A, S_B, X0, Y0);

    if S_C mod G /= 0 then
      return Sol;
    end if;

    A_Prime := S_A / G;
    B_Prime := S_B / G;
    C_Prime := S_C / G;

    X_Base := X0 * C_Prime;
    Y_Temp := Y0 * C_Prime;
    Y_Base := -Y_Temp;

    K_X := (-X_Base) / B_Prime;
    while X_Base + K_X * B_Prime < 0 loop
      K_X := K_X + 1;
    end loop;

    K_Y := (-Y_Base) / A_Prime;
    while Y_Base + K_Y * A_Prime < 0 loop
      K_Y := K_Y + 1;
    end loop;

    if K_X > K_Y then
      K := K_X;
    else
      K := K_Y;
    end if;

    Sol.X := Unsigned_64 (X_Base + K * B_Prime);
    Sol.Y := Unsigned_64 (Y_Base + K * A_Prime);
    Sol.HasSolution := True;

    return Sol;
  end SolveDiophantine;
end My_Lib;
