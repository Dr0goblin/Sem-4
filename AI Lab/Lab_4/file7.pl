% Use Definite Clause Grammars (DCG) in Prolog to parse simple English sentences consisting of a noun phrase and a verb phrase

sentence --> noun_phrase, verb_phrase.


noun_phrase --> determiner, noun.
verb_phrase --> verb.
verb_phrase --> verb, noun_phrase.


% Lexicon
determiner --> [the].
determiner --> [a].


noun --> [cat].
noun --> [dog].
noun --> [fish].


verb --> [sleeps].
verb --> [eats].
verb --> [likes].