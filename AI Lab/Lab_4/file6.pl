% Write a program in Prolog for the following FOPL.
% All engineers are problem solvers.
% All software developers are engineers.
% All problem solvers are analytical thinkers.
% Everyone who drinks coffee is good at something.
% Alice is a software developer.
% Alice drinks coffee.
% To Prove: Alice is an analytical thinker and good at something.

% Universals
problem_solver(X) :- engineer(X).
engineer(X) :- software_developer(X).
analytical_thinker(X) :- problem_solver(X).


% Existential: there exists some skill S such that good_at(X, S)
% We encode it with a placeholder atom `some_skill`.
good_at(X, some_skill) :- drinks_coffee(X).


% Facts about Alice
software_developer(alice).
drinks_coffee(alice).