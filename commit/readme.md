#Commit

Se da o secventa de instructiuni in limbajul Valentin. Afisati ce este returnat dupa executarea acestor intructiuni !

In limbajul Valentin este foarte dificil sa prelucrezi operatiunile concurente. Doua operatiuni sunt considerate concurente daca acceseaza acelasi tabel pentru  modificare, adaugare sau stergere. Datele sunt stocate in tabele definite prin o serie de coloane. Fiecare coloana are doua proprietati: nume - un sir de maxim 10 caractere, cheie_primara - 0 sau 1,  daca este 1 atunci tabelul nu accepta duplicate in aceasta coloana, daca este 0 accepta duplicate in aceasta coloana.

Avem doar 3 tipuri de operatii: 
 -- update : modifica anumite informatii dintr-un tabel
 -- insert : insereaza o linie intr-un tabel(de forma coloanelor tabelului respectiv)
 -- delete : sterge o linie dintr-un tabel
 -- FINALIZEAZA

Comunitatea Valentina are mai multi clienti care executa acest tip de operatii. Din pacate pot aparea concurente intre operatiile acestora.
Secventa de operatii ale unui client, pornind de la prima operatiune pana la o operatiune FINALIZEAZA, se numeste tranzactie. Dupa o operatiune FINALIZEAZA incepe o noua tranzactie.

Daca in timpul tranzactiei unui client, alt client executa o operatie care are efect asupra aceluiasi tabel, al doilea client asteapta pana la operatiunea FINALIZEAZA a primului client, dupa care va incerca sa execute operatiunea lui.

Operatiunile returneaza succes, sau eroare, in cazul in operatiunilor insert care nu respecta unicitatea unei coloane care are atributul cheie_primara = 1.

##Cerinta
Dandu-se o secventa de intructiuni valentiniene, afisati rezultatele returnate de acestea, in ordinea executiei lor. Fiecare operatiune este codificata prin numarul tranzactiei din care face parte, si 
