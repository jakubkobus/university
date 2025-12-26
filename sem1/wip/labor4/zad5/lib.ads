package Lib is
  type FactorsArray is array(Natural range <>) of Natural;

  function totient(n : in Natural) return Natural;

  private

  function Log2i(n : Natural) return Natural;
  procedure primeFactors(factors : in out FactorsArray; size : in out Natural);
end Lib;