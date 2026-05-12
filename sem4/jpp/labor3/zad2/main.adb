with Ada.Text_IO; use Ada.Text_IO;
with Ada.Exceptions;
with Ada.Strings.Fixed;
with ModuloRing;
with RSA;

procedure Main is
  function Trim_Image (Val : Long_Long_Integer) return String is
  begin
    return
     Ada.Strings.Fixed.Trim (Long_Long_Integer'Image (Val), Ada.Strings.Left);
  end Trim_Image;

  P : constant Long_Long_Integer := 10007;
  Q : constant Long_Long_Integer := 10009;

  package RSA_Ring is new ModuloRing (N => P * Q);
  use type RSA_Ring.Ring;

  package RSA_Handler is new
   RSA
    (T          => RSA_Ring.Ring,
     Ring_Mod   => P * Q,
     "*"        => RSA_Ring."*",
     To_Element => RSA_Ring.To_Ring);

  RSA_Info  : RSA_Handler.RSA_Info;
  Message   : RSA_Ring.Ring;
  Encrypted : RSA_Ring.Ring;
  Decrypted : RSA_Ring.Ring;
begin
  RSA_Info := RSA_Handler.Create (P, Q);

  Put_Line
   ("Public key: "
    & Trim_Image
       (RSA_Ring.To_Integer (RSA_Handler.Get_Public_Key (RSA_Info))));
  Put_Line
   ("getModulo() -> " & Trim_Image (RSA_Handler.Get_Modulo (RSA_Info)));
  New_Line;

  Message := RSA_Ring.To_Ring (12042026);
  Put_Line ("Message: " & Trim_Image (RSA_Ring.To_Integer (Message)));

  Encrypted := RSA_Handler.Encrypt (RSA_Info, Message);
  Put_Line ("Encrypted: " & Trim_Image (RSA_Ring.To_Integer (Encrypted)));

  Decrypted := RSA_Handler.Decrypt (RSA_Info, Encrypted);
  Put_Line ("Decrypted: " & Trim_Image (RSA_Ring.To_Integer (Decrypted)));

  if Message = Decrypted then
    Put_Line ("[INFO] Success: message == decrypted");
  else
    Put_Line ("[INFO] Failure: message /= decrypted");
  end if;

exception
  when E : others =>
    Put_Line
     ("[WARN] Exception catched: " & Ada.Exceptions.Exception_Message (E));
end Main;
