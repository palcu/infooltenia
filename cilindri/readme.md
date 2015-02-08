# Conuri

Un trunchi de con este un corp geometric obtinut prin sectionarea unui con obisnuit, cu un plan paralel cu baza, si inlaturarea conului mic rezultat.
Se da un sir de trunchiuri de con, definite prin raza bazei mici si raza bazei mari. Inaltimile sunt neglijabile.

Găsiti cel mai lung subsir format din suprapunerea de trunchiuri, astfel incat oricare doi corpuri consecutive sa fie unite perfect (bazele dintre ele sa fie de aceeasi raza). Un corp poate fi rotit pentru a se potrivi perfect peste baza de deasupra a corpului anterior.

## Date de intrare
Pe prima linie va fi un numar natural N, reprezentand lungimea sirului initial de trunchiuri de con.
Urmatoarele N linii, vor contine doua numere naturale, r1[i] si r2[i], adica razele bazelor trunchiului i.

## Date de iesire
Fisierul de iesire va contine un singur numar, lungimea subsirului de lungime maxima formata din cilindri cu proprietatea din enunt.

## Exemplu

```
5 
1 5
2 4
1 2
3 4
4 1
```

Out

```
3
```

Explicatie:
Subsirul va fi format din corpurile:

2, 3, 5
