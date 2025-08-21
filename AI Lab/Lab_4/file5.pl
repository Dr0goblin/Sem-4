% Use Prolog rules and a given fact to demonstrate that if all mammals are warm-blooded and all cats are mammals, then all cats are warm-blooded.

% All warm-blooded animals are mammals
warm_blooded(X) :- mammal(X).

% All mammals are cats
mammal(X) :- cat(X).

cat(lion).
cat(tiger).