%Write a Prolog program that determines friendship between two people based on common interests.
likes(john,pizza).
likes(mary,coffee).
likes(himal,alcohol).
likes(remi,tea).
likes(rai,pizza).
% if two people like same thing they must be friend
friend(X,Y):-likes(X,Thing), likes(Y,Thing) , X \= Y.