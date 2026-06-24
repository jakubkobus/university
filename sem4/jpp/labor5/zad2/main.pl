mergeSort([], []) :- !.
mergeSort([X], [X]) :- !.
mergeSort(List, Sorted) :-
    msLength(List, Len),
    Half is Len div 2,
    msTake(List, Half, Left),
    msDrop(List, Half, Right),
    mergeSort(Left, SortedLeft),
    mergeSort(Right, SortedRight),
    msMerge(SortedLeft, SortedRight, Sorted).

msLength([], 0) :- !.
msLength([_|T], L) :-
  msLength(T, L1),
  L is L1 + 1.

msTake(_, 0, []) :- !.
msTake([H|T], N, [H|Rest]) :- N > 0, N1 is N - 1, msTake(T, N1, Rest).

msDrop(L, 0, L) :- !.
msDrop([_|T], N, Rest) :- N > 0, N1 is N - 1, msDrop(T, N1, Rest).

msMerge([], L, L) :- !.
msMerge(L, [], L) :- !.
msMerge([H1|T1], [H2|T2], [H1|Rest]) :-
    H1 < H2, !,
    msMerge(T1, [H2|T2], Rest).
msMerge([H1|T1], [H2|T2], [H2|Rest]) :-
    msMerge([H1|T1], T2, Rest).



de(A, 0, 1, 0, A) :- !.
de(A, B, X, Y, Z) :-
    B > 0,
    Mod is A mod B,
    Div is A div B,
    de(B, Mod, X1, X, Z),
    Y is X1 - Div * Y1.



primeFactors(N, X) :- pfLoop(N, 2, [], X).

pfLoop(1, _, Acc, X) :- !, X = Acc.
pfLoop(N, I, Acc, X) :-
    Mod is N mod I,
    Mod =:= 0,
    !,
    N1 is N div I,
    pfAppend(Acc, [I], NewAcc),
    pfLoop(N1, I, NewAcc, X).
pfLoop(N, I, Acc, X) :-
    I1 is I + 1,
    pfLoop(N, I1, Acc, X).

pfAppend([], L, L) :- !.
pfAppend([H|T], L, [H|Rest]) :- pfAppend(T, L, Rest).



totient(N, T) :- tLoop(N, 1, 0, T).

tLoop(N, I, Count, T) :-
    I > N, !,
    T = Count.
tLoop(N, I, Count, T) :-
    tGCD(N, I, Gcd),
    Gcd =:= 1, !,
    Count1 is Count + 1,
    I1 is I + 1,
    tLoop(N, I1, Count1, T).
tLoop(N, I, Count, T) :-
    I1 is I + 1,
    tLoop(N, I1, Count, T).

tGCD(A, 0, A) :- !.
tGCD(A, B, G) :- Mod is A mod B, tGCD(B, Mod, G).



primes(N, X) :- pLoop(2, N, [], X).

pLoop(I, N, Acc, X) :-
    I > N, !,
    X = Acc.
pLoop(I, N, Acc, X) :-
    isPrime(I, 2), !,
    pfAppend(Acc, [I], NewAcc),
    I1 is I + 1,
    pLoop(I1, N, NewAcc, X).
pLoop(I, N, Acc, X) :-
    I1 is I + 1,
    pLoop(I1, N, Acc, X).

isPrime(Num, J) :-
    J * J > Num, !.
isPrime(Num, J) :-
    Mod is Num mod J,
    Mod =:= 0, !, fail.
isPrime(Num, J) :-
    J1 is J + 1,
    isPrime(Num, J1).



:- initialization(main, main).

main :-
    mergeSort([4,2,5,1,3], Sorted),
    format('1. mergeSort [4,2,5,1,3] = ~w~n', [Sorted]),

    de(30, 20, X, Y, Z),
    format('2. de 30 20 = (~w, ~w, ~w)~n', [X, Y, Z]),

    primeFactors(60, Factors),
    format('3. primeFactors 60 = ~w~n', [Factors]),

    totient(10, T),
    format('4. totient 10 = ~w~n', [T]),

    primes(20, PrimesList),
    format('5. primes 20 = ~w~n', [PrimesList]),

    halt.
