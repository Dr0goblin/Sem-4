% Semrntic network with inheritance and querying

:- dynamic r/3.

% Add a relation fact
a(X, R, Y) :- assertz(r(X, R, Y)).

% Check direct relation
d(X, R, Y) :- r(X, R, Y).

% Check inherited relation (first direct, then via is_a)
i(X, R, Y) :- r(X, R, Y).
i(X, R, Y) :- r(X, is_a, Z), i(Z, R, Y).

% Find path between nodes (avoiding cycles)
p(X, Y, P) :- p(X, Y, [X], P).
p(Y, Y, V, V).
p(X, Y, V, P) :-
    (r(X, _, Z); r(Z, _, X)),
    \+ member(Z, V),
    p(Z, Y, [Z|V], P).

% Get all inherited properties of X
g(X, L) :- findall(R-Y, i(X, R, Y), L).

% Show all relations
s :- findall(X-R-Y, r(X, R, Y), L), maplist(writeln, L).

% Example network
r(animal, has, skin).
r(animal, breathes, air).
r(mammal, is_a, animal).
r(mammal, has, fur).
r(dog, is_a, mammal).
r(dog, makes, bark).
r(buddy, is_a, dog).
r(buddy, color, brown).