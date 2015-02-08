# Enunț

Carl Friedrich când era mic avea o cutie în care ținea N bilețele, cu numerele de la 1 la N pe care le folosea la aritmetică. Fratele lui mai mare din când în când îi mai fura câte un singur bilețel ca să îl enerveze. După ce se întâmpla asta, Carl trebuia să scoată din cutie fiecare bilețel, să le noteze, să observe care număr a fost furat, să rescrie pe hârtie numărul și să îl adauge din nou în cutie. Fascinat fiind de matematică, a observat că fratele lui fura câteva numere mai mult decât altele. Din nefericire, el nu are un calculator, așa că vă roagă pe voi să rezolvați problema.

## Date de intrare

Fişierul de intrare lipsa.in va pe prima linie două numere, N și M, reprezentând numărul de bilețele și de câte ori fratele mai mare i-a furat un bilețel. Pe următoarele M-1 linii, se află câte N-1 numere, reprezentând bilețelele pe care Carl le găsea după ce fratele îi spunea că i-a furat un bilețel

## Date de ieșire

În fişierul de ieşire lipsa.out pe prima linie vor fi două numere, X și Y, reprezentând de câte ori a fost furat cel mai mult un bilețel, și câte de astfel de bilețele există. Pe următoarea linie, vor fi Y numere, reprezentând bilețele furate de cele mai multe ori.

## Restricții

```
2 <= N <= 1.000.000
1 <= M <= 100
```

## lipsa.in

```
5 7
5 2 3 4
4 3 2 5
1 2 5 3
4 5 3 1
2 3 5 1
1 2 4 5
1 2 4 5
```

## lipsa.out

```
2 3
1 3 4 
```


# Particularități

- dacă vor sorta si apoi vor număra care apar de cele mai multe ori, atunci vor trebui să aibă grijă dacă ultimul dintre ele se gaseste in lista aia (chestia asta să nu se găsească în exemplul meu [copiii trebuie sa fie atenti :-)])
- pot fi mai multe numere care lipsesc de cele mai multe ori
- am rezolvat-o in 30 de minute

# Cazuri speciale

- fură același număr de fiecare dată
- fură toate numerele o dată