generic
  N : Positive;
package ModuloRing is

  type Ring is private;

  Division_By_Zero : exception;
  No_Inverse       : exception;

  function To_Ring (Value : Integer) return Ring;
  function To_Integer (Item : Ring) return Integer;

  function "+" (Left, Right : Ring) return Ring;
  function "-" (Left, Right : Ring) return Ring;
  function "*" (Left, Right : Ring) return Ring;
  function "/" (Left, Right : Ring) return Ring;

  function "<" (Left, Right : Ring) return Boolean;
  function ">" (Left, Right : Ring) return Boolean;
  function "<=" (Left, Right : Ring) return Boolean;
  function ">=" (Left, Right : Ring) return Boolean;

private
  type Ring is record
    Value : Natural;
  end record;

end ModuloRing;
