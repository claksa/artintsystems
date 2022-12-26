% database
spouse(finwe,indis).
spouse(finwe, miriel).
spouse(nerdanel, feanor).
spouse(fingolfin, anaire).
spouse(finarfin, earwen).
spouse(tata, tatie).
spouse(tuor, idril).
spouse(aredhel, eol).
spouse(angrod, eldalote).
spouse(galadriel, celeborn).
spouse(elrond, celebrian).
spouse(elenwe, turgon).

parent(tata, finwe).
parent(tatie, finwe).
parent(finwe, findis).
parent(finwe, fingolfin).
parent(finwe, irime).
parent(finwe, finarfin).
parent(finwe, feanor).
parent(indis, findis).
parent(indis, fingolfin).
parent(indis, irime).
parent(indis, finarfin).
parent(miriel, feanor).
parent(mahtan, nerdanel).
parent(feanor, maedhros).
parent(feanor, maglor).
parent(feanor, celegrom).
parent(feanor, caranthir).
parent(feanor, curufin).
parent(curufin, celebrimbor).
parent(nerdanel, maedhros).
parent(nerdanel, maglor).
parent(nerdanel, celegorm).
parent(nerdanel, caranthir).
parent(nerdanel, curufin).
parent(fingolfin, fingon).
parent(fingolfin, turgon).
parent(fingolfin, aredhel).
parent(fingolfin, argon).
parent(anaire, fingon).
parent(anaire, turgon).
parent(anaire, aredhel).
parent(anaire, argon).
parent(turgon, idril).
parent(elenwe, idril).
parent(idril, earendil).
parent(tuor, earendil).
parent(aredhel, maeglin).
parent(eol, maeglin).
parent(olwe, earwen).
parent(finarfin, angrod).
parent(finarfin, finrod).
parent(finarfin, aegnor).
parent(finarfin, galadriel).
parent(earwen, angrod).
parent(earwen, finrod).
parent(earwen, aegnor).
parent(earwen, galadriel).
parent(angrod, orodeth).
parent(edalote, orodeth).
parent(orodeth, gil-galad).
parent(orodeth, finduilas).
parent(galadriel, celebrian).
parent(celeborn, celebrian).
parent(celebrian, elladan).
parent(celebrian, elrohir).
parent(celebrian, arwen).
parent(elrond, elladan).
parent(elrond, elrohir).
parent(elrond, arwen).

% rules
in_full_fam(C):- parent(X, C), parent(Y, C), X\=Y.
have_common_children(P1, P2) :- parent(P1, X), parent(P2, X), P1\=P2.
sibling(X,Y) :- in_full_fam(X), parent(P2, X), parent(P2, Y), parent(P1,X), parent(P1,Y), P1 \= P2, X\=Y.
sibling(X,Y) :- not(in_full_fam(X)), parent(P, X), parent(P, Y), X\=Y.
stepsibling(X, R) :- in_full_fam(X), have_common_children(P1, P2), parent(P1, X), not(parent(P2, X)), parent(P2, R), X \= R.
% X -- тётя/дядя, R -- племянник
nephew(X, R) :- parent(Z,R), sibling(X,Z).
spouse(X,Y) :- spouse(Y, X).
parents(C, [P1, P2]) :- in_full_fam(C), parent(P1, C), parent(P2, C), P1\=P2.
parents(C, R) :- not(in_full_fam(C)), parent(R, C).
% X -- внук; R -- бабушка/дедушка
grandparent(X, R) :- parent(R, P), parent(P, X).
cousin(X, Y):-parent(Z1, X), parent(Z2, Y), sibling(Z1, Z2), Z1 \= Z2, X \= Y.
% R -- супруг ребёнка, X -- родитель, Y -- ребёнок
children_in_law(X, Y, R) :- spouse(Y, R), parent(X, Y).
% R -- сиблинг супруга X
sibling_in_law(X, R) :- spouse(X, Y), sibling(Y, R), X\=R.
% X -- потомок, R -- предок.
ancestor(X, R) :- parent(R, X).
ancestor(X, R) :- parent(R, P), ancestor(X, P).
