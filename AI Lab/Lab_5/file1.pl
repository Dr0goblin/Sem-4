% Design and implement a simple frame-based knowledge representation system in Prolog using the concept of classes, slots, inheritance, and instances.Your system should allow defining classes with default attributes (slots), creating instances of classes, overriding slot values for specific instances, and retrieving slot values with inheritance.


:- dynamic class/2.
:- dynamic slot/3.
:- dynamic instance/2.
:- dynamic value/3.

define_class(Name, Parent) :-
    assertz(class(Name, Parent)).

add_slot(Class, Slot, Default) :-
    assertz(slot(Class, Slot, Default)).

create_instance(Name, Class) :-
    assertz(instance(Name, Class)).

set_value(Instance, Slot, Value) :-
    assertz(value(Instance, Slot, Value)).

get_value(Thing, Slot, Value) :-
    value(Thing, Slot, Value).

get_value(Thing, Slot, Value) :-
    instance(Thing, Class),
    get_class_value(Class, Slot, Value).

get_value(Thing, Slot, Value) :-
    class(Thing, _),
    get_class_value(Thing, Slot, Value).

get_class_value(Class, Slot, Value) :-
    slot(Class, Slot, Value).

get_class_value(Class, Slot, Value) :-
    class(Class, Parent),
    get_class_value(Parent, Slot, Value).

show_instance(Instance) :-
    instance(Instance, Class),
    format('Instance: ~w (Class: ~w)~n', [Instance, Class]),
    findall(Slot-Value, get_value(Instance, Slot, Value), Slots),
    show_slots(Slots).

show_class(Class) :-
    class(Class, Parent),
    format('Class: ~w (Parent: ~w)~n', [Class, Parent]),
    findall(Slot-Default, slot(Class, Slot, Default), Slots),
    show_slots(Slots).

show_slots([]).
show_slots([Slot-Value|Rest]) :-
    format('  ~w: ~w~n', [Slot, Value]),
    show_slots(Rest).

% Example knowledge base
class(animal, nothing).
class(mammal, animal).
class(dog, mammal).

slot(animal, legs, 4).
slot(animal, eyes, 2).
slot(mammal, hair, true).
slot(mammal, milk, true).
slot(dog, sound, bark).
slot(dog, tail, true).


instance(buddy, dog).
instance(max, dog).

value(buddy, color, brown).
value(buddy, name, 'Buddy').
value(max, color, black).