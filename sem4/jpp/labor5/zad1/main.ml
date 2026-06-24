let rec binomial n k =
  if k = 0 then 1
  else if k = n then 1
  else binomial (n - 1) k + binomial (n - 1) (k - 1)



let rec b2GetNth lst k i =
  if i = k then List.hd lst
  else b2GetNth (List.tl lst) k (i + 1)

let rec b2GenerateRow prev_row i len =
  if i > len then []
  else if i = 0 then 1 :: b2GenerateRow prev_row (i + 1) len
  else if i = len then 1 :: b2GenerateRow prev_row (i + 1) len
  else (b2GetNth prev_row (i - 1) 0 + b2GetNth prev_row i 0) :: b2GenerateRow prev_row (i + 1) len

let rec b2PascalTriangle n =
  if n = 0 then [1]
  else b2GenerateRow (b2PascalTriangle (n - 1)) 0 (List.length (b2PascalTriangle (n - 1)))

let binomial2 n k = b2GetNth (b2PascalTriangle n) k 0



let rec msTake lst n i =
  if i = n then [] else List.hd lst :: msTake (List.tl lst) n (i + 1)

let rec msDrop lst n i =
  if i = n then lst else msDrop (List.tl lst) n (i + 1)

let rec msMerge a b =
  if List.length a = 0 then b
  else if List.length b = 0 then a
  else if List.hd a < List.hd b then List.hd a :: msMerge (List.tl a) b
  else List.hd b :: msMerge a (List.tl b)

let rec mergeSort l =
  let len = List.length l in
  if len <= 1 then l
  else
    let half = len / 2 in
    let left = msTake l half 0 in
    let right = msDrop l half 0 in
    msMerge (mergeSort left) (mergeSort right)



let rec de a b =
  if b = 0 then (1, 0, a)
  else
    let (x1, y1, gcd_val) = de b (a mod b) in
    (y1, x1 - (a / b) * y1, gcd_val)



let rec pfLoop n i result =
  if n = 1 then result
  else if n mod i = 0 then pfLoop (n / i) i (result @ [i])
  else pfLoop n (i + 1) result

let primeFactors n = pfLoop n 2 []



let rec tGCD a b =
  if b = 0 then a else tGCD b (a mod b)

let rec tLoop n i count =
  if i > n then count
  else if tGCD n i = 1 then tLoop n (i + 1) (count + 1)
  else tLoop n (i + 1) count

let totient n = tLoop n 1 0



let rec t2Contains lst x =
  if List.length lst = 0 then false
  else if List.hd lst = x then true
  else t2Contains (List.tl lst) x

let rec t2RemoveDups lst result =
  if List.length lst = 0 then result
  else if t2Contains result (List.hd lst) then t2RemoveDups (List.tl lst) result
  else t2RemoveDups (List.tl lst) (result @ [List.hd lst])

let rec t2Loop val_ factors =
  if List.length factors = 0 then val_
  else t2Loop (val_ / List.hd factors * (List.hd factors - 1)) (List.tl factors)

let totient2 n =
  let factors = t2RemoveDups (primeFactors n) [] in
  t2Loop n factors



let rec pIsPrime num j =
  if j * j > num then true
  else if num mod j = 0 then false
  else pIsPrime num (j + 1)

let rec pLoop i n result =
  if i > n then result
  else if pIsPrime i 2 then pLoop (i + 1) n (result @ [i])
  else pLoop (i + 1) n result

let primes n = pLoop 2 n []



let rec print_list lst =
  if List.length lst = 0 then print_string "\n"
  else (
    print_int (List.hd lst);
    print_string " ";
    print_list (List.tl lst)
  )

let print_tuple (x, y, z) =
  print_string "("; print_int x; print_string ", ";
  print_int y; print_string ", "; print_int z; print_string ")\n"

let () =
  print_string "1. binomial 5 2 = "; print_int (binomial 5 2); print_string "\n";
  print_string "2. binomial2 5 2 = "; print_int (binomial2 5 2); print_string "\n";

  print_string "3. mergesort [4;2;5;1;3] = ";
  print_list (mergeSort [4;2;5;1;3]);

  print_string "4. de 30 20 = ";
  print_tuple (de 30 20);

  print_string "5. primeFactors 60 = ";
  print_list (primeFactors 60);

  print_string "6. totient 10 = "; print_int (totient 10); print_string "\n";
  print_string "7. totient2 10 = "; print_int (totient2 10); print_string "\n";

  print_string "8. primes 20 = ";
  print_list (primes 20)
