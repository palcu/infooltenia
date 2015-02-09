# Enunț

> CONJECTÚRĂ, conjecturi, s. f. Părere bazată pe ipoteze sau pe presupuneri; prezumție, supoziție. – Din fr. conjecture, lat. conjectura.
dexonline.ro

Conjecturile sunt probleme încă nedemonstrate, dar la care matematicienii nu au găsit încă o caz particular care să nege presupunarea. Una din aceste conjecturi se numește Lychrel și enunțul ei este extrem de simplu. Se ia un număr, se adună cu alt număr obținut prin oglindirea lui și se așteaptă să se găsească un palindrom. Dacă nu se întâmplă asta, se repetă operația cu noul număr.

De exemplu 49:

49+
94=
143+
341=
484 <- palindrom

Dar unele numere, ca 196, nu ajung să fie palindrom niciodată. Scrieți un algoritm care pentru câteva numere date și numărul de iterații care trebuie efectuate, va afișa în câte iterații numărul devine palindrom sau dacă acesta nu devine în numărul maxim de iterații


## Date de intrare
Fişierul de intrare conjectura.in va pe prima linie două numere, N și M, reprezentând numărul de numere și numărul maxim de iterații care trebuie efectuate. Pe următoarele M linii se va afla câte un număr X, reprezentând numerele care trebuie verificate.

## Date de ieșire
Fișierul de ieșire conjectura.out va conține pe fiecare linie numărul de iterații până când acel număr devine palindrom sau LYCHREL dacă acesta nu devine în numărul maxim de iterații

## Restricții

```
Pentru 30 de puncte:
1 <= N <= 10
1 <= M <= 10
1 <= X <= 100

Pentru 100 de puncte:
1 <= N <= 100
1 <= M <= 50
1 <= X <= 1.000.000
```
