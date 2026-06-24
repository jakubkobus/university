fun binomial n k =
    if k = 0 then 1
    else if k = n then 1
    else binomial (n - 1) k + binomial (n - 1) (k - 1);



fun binomial2 n k =
    let
        fun getNth lst k_val i =
            if i = k_val then hd lst else getNth (tl lst) k_val (i + 1)

        fun generateRow prev_row i len =
            if i > len then []
            else if i = 0 then 1 :: generateRow prev_row (i + 1) len
            else if i = len then 1 :: generateRow prev_row (i + 1) len
            else (getNth prev_row (i - 1) 0 + getNth prev_row i 0) :: generateRow prev_row (i + 1) len

        fun pascalTriangle num =
            if num = 0 then [1]
            else generateRow (pascalTriangle (num - 1)) 0 (length (pascalTriangle (num - 1)))
    in
        getNth (pascalTriangle n) k 0
    end;



fun mergeSort l =
    let
        fun takeN lst num i = if i = num then [] else hd lst :: takeN (tl lst) num (i + 1)
        fun dropN lst num i = if i = num then lst else dropN (tl lst) num (i + 1)

        fun merge a b =
            if length a = 0 then b
            else if length b = 0 then a
            else if hd a < hd b then hd a :: merge (tl a) b
            else hd b :: merge a (tl b)

        val len = length l
    in
        if len <= 1 then l
        else
            let
                val half = len div 2
                val left = takeN l half 0
                val right = dropN l half 0
            in
                merge (mergeSort left) (mergeSort right)
            end
    end;



fun de a b =
    if b = 0 then (1, 0, a)
    else
        let
            val (x1, y1, gcd_val) = de b (a mod b)
        in
            (y1, x1 - (a div b) * y1, gcd_val)
        end;



fun primeFactors n =
    let
        fun pfLoop curr_n i result =
            if curr_n = 1 then result
            else if curr_n mod i = 0 then pfLoop (curr_n div i) i (result @ [i])
            else pfLoop curr_n (i + 1) result
    in
        pfLoop n 2 []
    end;



fun totient n =
    let
        fun GCD a b = if b = 0 then a else GCD b (a mod b)
        fun tLoop n_val i count =
            if i > n_val then count
            else if GCD n_val i = 1 then tLoop n_val (i + 1) (count + 1)
            else tLoop n_val (i + 1) count
    in
        tLoop n 1 0
    end;




fun totient2 n =
    let
        fun contains lst x =
            if length lst = 0 then false
            else if hd lst = x then true
            else contains (tl lst) x

        fun removeDups lst result =
            if length lst = 0 then result
            else if contains result (hd lst) then removeDups (tl lst) result
            else removeDups (tl lst) (result @ [hd lst])

        fun t2Loop val_ factors =
            if length factors = 0 then val_
            else t2Loop (val_ div (hd factors) * ((hd factors) - 1)) (tl factors)

        val factors = removeDups (primeFactors n) []
    in
        t2Loop n factors
    end;



fun primes n =
    let
        fun isPrime num j =
            if j * j > num then true
            else if num mod j = 0 then false
            else isPrime num (j + 1)

        fun pLoop i n_val result =
            if i > n_val then result
            else if isPrime i 2 then pLoop (i + 1) n_val (result @ [i])
            else pLoop (i + 1) n_val result
    in
        pLoop 2 n []
    end;



fun print_list lst =
    if length lst = 0 then print "\n"
    else (
        print (Int.toString (hd lst) ^ " ");
        print_list (tl lst)
    );

fun print_tuple (x, y, z) =
    print ("(" ^ Int.toString x ^ ", " ^ Int.toString y ^ ", " ^ Int.toString z ^ ")\n");

val _ = print ("1. binomial 5 2 = " ^ Int.toString (binomial 5 2) ^ "\n");
val _ = print ("2. binomial2 5 2 = " ^ Int.toString (binomial2 5 2) ^ "\n");

val _ = print "3. mergesort [4,2,5,1,3] = ";
val _ = print_list (mergeSort [4,2,5,1,3]);

val _ = print "4. de 30 20 = ";
val _ = print_tuple (de 30 20);

val _ = print "5. primeFactors 60 = ";
val _ = print_list (primeFactors 60);

val _ = print ("6. totient 10 = " ^ Int.toString (totient 10) ^ "\n");
val _ = print ("7. totient2 10 = " ^ Int.toString (totient2 10) ^ "\n");

val _ = print "8. primes 20 = ";
val _ = print_list (primes 20);
