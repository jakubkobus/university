with Ada.Text_IO; use Ada.Text_IO;
with Ada.Exceptions;
with Ada.Strings.Fixed;
with ModuloRing;
with Diffie_Hellman;

procedure Main is
  function Trim_Image (Val : Long_Long_Integer) return String is
  begin
    return
     Ada.Strings.Fixed.Trim (Long_Long_Integer'Image (Val), Ada.Strings.Left);
  end Trim_Image;

  P : constant Long_Long_Integer := 1234567891;

  package DHRing is new ModuloRing (N => P);
  use type DHRing.Ring;

  package DH_Handler is new
   Diffie_Hellman
    (T          => DHRing.Ring,
     Ring_Mod   => P,
     "*"        => DHRing."*",
     "/"        => DHRing."/",
     "="        => DHRing."=",
     To_Element => DHRing.To_Ring);

  Setup   : DH_Handler.DH_Setup;
  Alice   : DH_Handler.DH_User;
  Bob     : DH_Handler.DH_User;
  Charlie : DH_Handler.DH_User;

  Alice_Pub, Bob_Pub            : DHRing.Ring;
  Message, Encrypted, Decrypted : DHRing.Ring;

begin
  Setup := DH_Handler.Create_Setup;
  Put_Line
   ("getGenerator() -> "
    & Trim_Image (DHRing.To_Integer (DH_Handler.Get_Generator (Setup))));
  New_Line;

  Alice := DH_Handler.Create_User;
  Bob := DH_Handler.Create_User;

  Alice_Pub := DH_Handler.Get_Public_Key (Alice, Setup);
  Bob_Pub := DH_Handler.Get_Public_Key (Bob, Setup);

  Put_Line ("Alice public key: " & Trim_Image (DHRing.To_Integer (Alice_Pub)));
  Put_Line ("Bob public key: " & Trim_Image (DHRing.To_Integer (Bob_Pub)));
  New_Line;

  DH_Handler.Set_Key (Alice, Setup, Bob_Pub);
  DH_Handler.Set_Key (Bob, Setup, Alice_Pub);

  Message := DHRing.To_Ring (12042026);
  Put_Line ("Alice message: " & Trim_Image (DHRing.To_Integer (Message)));

  Encrypted := DH_Handler.Encrypt (Alice, Message);
  Put_Line
   ("Encrypted message by Alice: "
    & Trim_Image (DHRing.To_Integer (Encrypted)));

  Decrypted := DH_Handler.Decrypt (Bob, Encrypted);
  Put_Line
   ("Decrypted message by Bob: " & Trim_Image (DHRing.To_Integer (Decrypted)));

  if Message = Decrypted then
    Put_Line ("[INFO] Success: message == decrypted");
  else
    Put_Line ("[INFO] Failure: message /= decrypted");
  end if;

  Charlie := DH_Handler.Create_User;

  Decrypted := DH_Handler.Decrypt (Charlie, Encrypted);

exception
  when E : others =>
    Put_Line
     ("[WARN] Exception catched: " & Ada.Exceptions.Exception_Message (E));
end Main;
