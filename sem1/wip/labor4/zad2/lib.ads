package Lib is
  type SieveArray is array(Natural range <>) of Boolean;

  function countPrimes(n : in Positive) return Natural;
  function nthPrime(n : Natural) return Natural;
  function isPrime(n : in Integer) return Boolean;

  private

  function iSqrt(n : in Natural) return Natural;
  procedure computeSieve(sieve : in out SieveArray; n : in Positive);
end Lib;