% Create a Simple Medical Expert System Using Prolog.

% Symptom facts for example patients
symptom(alex, fever).
symptom(alex, cough).
symptom(alex, body_ache).


symptom(beth, runny_nose).
symptom(beth, sore_throat).
symptom(beth, cough).


symptom(carl, fever).
symptom(carl, chills).
symptom(carl, headache).


% Disease rules (very simplified!)
disease(P, flu) :-
symptom(P, fever), symptom(P, cough), symptom(P, body_ache).


disease(P, common_cold) :-
symptom(P, runny_nose), symptom(P, sore_throat), symptom(P, cough).


disease(P, malaria) :-
symptom(P, fever), symptom(P, chills), symptom(P, headache).


% Treatments
treatment(flu, rest_and_fluids).
treatment(common_cold, rest_and_fluids).
treatment(malaria, see_doctor_antimalarials).


% Main queries
diagnose(Patient, Disease) :- disease(Patient, Disease).
recommend(Patient, Treatment) :- diagnose(Patient, D), treatment(D, Treatment).