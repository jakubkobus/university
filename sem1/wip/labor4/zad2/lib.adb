with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

package body Lib is
  function iSqrt(n : in Natural) return Natural is
  begin
    return Natural(Integer(Sqrt(Float(n))));
  end iSqrt;

  procedure computeSieve(sieve : in out SieveArray; n : in Positive) is
    j : Positive;
  begin
    for i in 2 .. n loop
      sieve(i) := True;
    end loop;

    for i in 2 .. n loop
      if sieve(i) then
        j := i + i;
        while j <= n loop
          sieve(j) := False;
          j := j + i;
        end loop;
      end if;
    end loop;
  end computeSieve;

  function countPrimes(n : in Positive) return Natural is
    sieve : SieveArray(1 .. n);
    numberOfPrimes : Natural := 0;
  begin
    computeSieve(sieve, n);

    for i in 2 .. n loop
      if sieve(i) then
        numberOfPrimes := numberOfPrimes + 1;
      end if;
    end loop;

    return numberOfPrimes;
  end countPrimes;

  function nthPrime(n : Natural) return Natural is
    primes : array(0 .. n - 1) of Natural;
    candidate : Natural := 3;
    iterator : Natural := 1;
    i, s : Natural;
    isPrime : Boolean;
  begin
    if n < 1 then return 0; end if;

    primes(0) := 2;

    while iterator < n loop
      s := iSqrt(candidate);
      isPrime := True;
      i := 1;

      while isPrime and primes(i) <= s and i < iterator loop
        if candidate mod primes(i) = 0 then isPrime := False;
        else i := i + 1; end if;
      end loop;

      if isPrime then
        primes(iterator) := candidate;
        iterator := iterator + 1;
      end if;

      candidate := candidate + 2;
    end loop;

    return primes(n - 1);
  end nthPrime;

  function isPrime(n : in Integer) return Boolean is
    isqrtn, i : Integer;
  begin
    if n <= 1 then
      return False;
    elsif n = 2 or n = 3 or n = 5 then
      return True;
    elsif n mod 2 = 0 or n mod 3 = 0 or n mod 5 = 0 then
      return False;
    end if;

    isqrtn := isqrt(n);
    i := 5;
    while i <= isqrtn loop
      if n mod i = 0 or n mod (i + 2) = 0 then
        return false;
      end if;

      i := i + 6;
    end loop;

    return True;
  end isPrime;
end Lib;