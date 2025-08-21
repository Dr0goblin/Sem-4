% Create a Prolog program that models family relationships using facts and rules for parenthood, gender, and sibling relations.
male(bohn).
male(ben).
female(anna).
female(mary).

% Parents
parent(bohn, anna).
parent(mary, anna).
parent(john, ben).
parent(mary, ben).

% Relations
father(X, Y) :- parent(X, Y), male(X).
mother(X, Y) :- parent(X, Y), female(X).

sibling(X, Y) :-
X \= Y,
parent(P, X), parent(P, Y).

brother(X, Y) :- sibling(X, Y), male(X).
sister(X, Y) :- sibling(X, Y), female(X).

grandparent(X, Z) :- parent(X, Y), parent(Y, Z).
