generic
  type T is private;
  Ring_Mod : Long_Long_Integer;
  with function "*" (Left, Right : T) return T is <>;
  with function "/" (Left, Right : T) return T is <>;
  with function "=" (Left, Right : T) return Boolean is <>;
  with function To_Element (Value : Long_Long_Integer) return T is <>;
package Diffie_Hellman is

  Logic_Error : exception;

  type DH_Setup is private;
  function Create_Setup return DH_Setup;
  function Get_Generator (Setup : DH_Setup) return T;
  function Power (Base : T; Exp : Long_Long_Integer) return T;

  type DH_User is private;
  function Create_User return DH_User;
  function Get_Public_Key (User : DH_User; Setup : DH_Setup) return T;
  procedure Set_Key
   (User : in out DH_User; Setup : DH_Setup; Other_Public : T);
  function Encrypt (User : DH_User; M : T) return T;
  function Decrypt (User : DH_User; C : T) return T;

private
  type DH_Setup is record
    Generator : T;
  end record;

  type DH_User is record
    Secret        : Long_Long_Integer;
    Key_Set       : Boolean := False;
    Symmetric_Key : T;
  end record;

end Diffie_Hellman;
