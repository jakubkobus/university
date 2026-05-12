generic
  N : Long_Long_Integer;
package ModuloRing is

  type Ring is private;

  Division_By_Zero : exception;
  No_Inverse       : exception;

  function To_Ring (Value : Long_Long_Integer) return Ring;
  function To_Integer (Item : Ring) return Long_Long_Integer;

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
    Value : Long_Long_Integer;
  end record;

end ModuloRing;
