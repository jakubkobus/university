generic
  type T is private;
  Ring_Mod : Long_Long_Integer;
  with function "*" (Left, Right : T) return T is <>;
  with function To_Element (Value : Long_Long_Integer) return T is <>;
package RSA is
  Invalid_Argument : exception;

  type RSA_Info is private;

  function Create (P, Q : Long_Long_Integer) return RSA_Info;

  function Get_Modulo (Info : RSA_Info) return Long_Long_Integer;
  function Get_Public_Key (Info : RSA_Info) return T;

  function Encrypt (Info : RSA_Info; M : T) return T;
  function Decrypt (Info : RSA_Info; S : T) return T;

private
  type RSA_Info is record
    P, Q, N, Phi, E, D : Long_Long_Integer;
  end record;
end RSA;
