% Write a Prolog program to solve the water jug puzzle: measure exactly 2 gallons using two jugs of capacities 4 and 3 gallons.

% Capacities: A = 4-gallon jug, B = 3-gallon jug

% --- Moves ---
move((A,B), (4,B), fill_a) :- A < 4.
move((A,B), (A,3), fill_b) :- B < 3.
move((A,B), (0,B), empty_a) :- A > 0.
move((A,B), (A,0), empty_b) :- B > 0.

% Pour A -> B
move((A,B), (A1,B1), pour_a_to_b) :-
    A > 0, B < 3,
    Transfer is min(A, 3-B),
    A1 is A - Transfer,
    B1 is B + Transfer.

% Pour B -> A
move((A,B), (A1,B1), pour_b_to_a) :-
    B > 0, A < 4,
    Transfer is min(B, 4-A),
    A1 is A + Transfer,
    B1 is B - Transfer.

% --- Goal condition: 2 gallons in jug A ---
goal((2,_)).

% --- BFS Solver ---
solve(Path) :-
    bfs([[(start,(0,0))]], Path).

bfs([[(_,State)|Rest]|_], [(start,(0,0))|Rest]) :-
    goal(State), !.

bfs([Path|Paths], Solution) :-
    Path = [(_,State)|_],
    findall([(Action,NextState)|Path],
            (move(State,NextState,Action),
             \+ member((_,NextState), Path)), % avoid revisiting
            NewPaths),
    append(Paths, NewPaths, Paths1),
    bfs(Paths1, Solution).
