with Ada.Numerics.Discrete_Random;

package body Diffie_Hellman is

  package Random_LLI is new Ada.Numerics.Discrete_Random (Long_Long_Integer);
  Gen : Random_LLI.Generator;

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

  function Create_Setup return DH_Setup is
    P : constant Long_Long_Integer := Ring_Mod;
    N : Long_Long_Integer := P - 1;

    Factors : array (1 .. 64) of Long_Long_Integer;
    Count   : Natural := 0;
    I       : Long_Long_Integer := 2;

    Candidate : T;
    Gen_Val   : Long_Long_Integer;
    Is_Gen    : Boolean;
  begin
    while I * I <= N loop
      if N mod I = 0 then
        Count := Count + 1;
        Factors (Count) := I;
        while N mod I = 0 loop
          N := N / I;
        end loop;
      end if;
      I := I + 1;
    end loop;

    if N > 1 then
      Count := Count + 1;
      Factors (Count) := N;
    end if;

    loop
      Gen_Val := (abs Random_LLI.Random (Gen)) mod (P - 1) + 1;
      Candidate := To_Element (Gen_Val);
      Is_Gen := True;

      for J in 1 .. Count loop
        if Power (Candidate, (P - 1) / Factors (J)) = To_Element (1) then
          Is_Gen := False;
          exit;
        end if;
      end loop;

      if Is_Gen then
        return (Generator => Candidate);
      end if;
    end loop;
  end Create_Setup;

  function Get_Generator (Setup : DH_Setup) return T is
  begin
    return Setup.Generator;
  end Get_Generator;

  function Create_User return DH_User is
    U : DH_User;
  begin
    U.Secret := (abs Random_LLI.Random (Gen)) mod (Ring_Mod - 2) + 1;
    U.Key_Set := False;
    return U;
  end Create_User;

  function Get_Public_Key (User : DH_User; Setup : DH_Setup) return T is
  begin
    return Power (Setup.Generator, User.Secret);
  end Get_Public_Key;

  procedure Set_Key (User : in out DH_User; Setup : DH_Setup; Other_Public : T)
  is
  begin
    User.Symmetric_Key := Power (Other_Public, User.Secret);
    User.Key_Set := True;
  end Set_Key;

  function Encrypt (User : DH_User; M : T) return T is
  begin
    if not User.Key_Set then
      raise Logic_Error with "Encryption without a set key";
    end if;
    return M * User.Symmetric_Key;
  end Encrypt;

  function Decrypt (User : DH_User; C : T) return T is
  begin
    if not User.Key_Set then
      raise Logic_Error with "Decryption without a set key";
    end if;
    return C / User.Symmetric_Key;
  end Decrypt;

begin
  Random_LLI.Reset (Gen);
end Diffie_Hellman;
