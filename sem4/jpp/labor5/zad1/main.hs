binomial n k =
  if k == 0 then 1
  else if k == n then 1
  else binomial (n-1) k + binomial (n-1) (k-1)



binomial2 n k = (b2PascalTriangle n) !! k

b2PascalTriangle n =
    if n == 0 then [1]
    else b2GenerateRow (b2PascalTriangle (n - 1)) 0 (length (b2PascalTriangle (n - 1)))

b2GenerateRow prevRow i len =
    if i > len then []
    else if i == 0 then 1 : b2GenerateRow prevRow (i + 1) len
    else if i == len then 1 : b2GenerateRow prevRow (i + 1) len
    else (prevRow !! (i - 1) + prevRow !! i) : b2GenerateRow prevRow (i + 1) len



mergeSort l =
    if length l <= 1 then l
    else
        let half = length l `div` 2
            left = msTake l half 0
            right = msDrop l half 0
        in msMerge (mergeSort left) (mergeSort right)

msTake l n i = if i == n then [] else (head l) : msTake (tail l) n (i + 1)
msDrop l n i = if i == n then l else msDrop (tail l) n (i + 1)

msMerge a b =
    if length a == 0 then b
    else if length b == 0 then a
    else if head a < head b then head a : msMerge (tail a) b
    else head b : msMerge a (tail b)



de a b =
    if b == 0 then (1, 0, a)
    else
        let (x1, y1, gcd_val) = de b (a `mod` b)
        in (y1, x1 - (a `div` b) * y1, gcd_val)



primeFactors n = pfLoop n 2 []

pfLoop n i result =
    if n == 1 then result
    else if n `mod` i == 0 then pfLoop (n `div` i) i (result ++ [i])
    else pfLoop n (i + 1) result



totient n = tLoop n 1 0

tLoop n i count =
    if i > n then count
    else if tGCD n i == 1 then tLoop n (i + 1) (count + 1)
    else tLoop n (i + 1) count

tGCD a b = if b == 0 then a else tGCD b (a `mod` b)



totient2 n =
    let factors = t2RemoveDups (primeFactors n) []
    in t2Loop n factors

t2RemoveDups lst result =
    if lst == [] then result
    else if t2Contains result (head lst) then t2RemoveDups (tail lst) result
    else t2RemoveDups (tail lst) (result ++ [head lst])

t2Contains lst x =
    if lst == [] then False
    else if head lst == x then True
    else t2Contains (tail lst) x

t2Loop val factors =
    if factors == [] then val
    else t2Loop (val `div` (head factors) * ((head factors) - 1)) (tail factors)



primes n = pLoop 2 n []

pLoop i n result =
    if i > n then result
    else if pIsPrime i 2 then pLoop (i + 1) n (result ++ [i])
    else pLoop (i + 1) n result

pIsPrime num j =
    if j * j > num then True
    else if num `mod` j == 0 then False
    else pIsPrime num (j + 1)




main = do
    putStr "1. binomial 5 2 = "
    print (binomial 5 2)

    putStr "2. binomial2 5 2 = "
    print (binomial2 5 2)

    putStr "3. mergesort [4,2,5,1,3] = "
    print (mergeSort [4,2,5,1,3])

    putStr "4. de 2 65537 = "
    print (de 2 65537)

    putStr "5. primeFactors 60 = "
    print (primeFactors 60)

    putStr "6. totient 65535 = "
    print (totient 65535)

    putStr "7. totient 65536 = "
    print (totient 65536)

    putStr "8. totient 65537 = "
    print (totient 65537)

    putStr "9. totient2 65535 = "
    print (totient2 65535)

    putStr "10. totient2 65536 = "
    print (totient2 65536)

    putStr "11. totient2 65537 = "
    print (totient2 65537)
