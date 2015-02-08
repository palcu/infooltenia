# Clasa a 9-a

## Lipsa @palcu

1.000.000 numere, citesti 999.999 de 100 ori, trebuie sa iti dai seama care a lipsit de cele mai multe ori.

```
5 5
1 2 3 4 -> 5
4 3 2 5 -> 1
1 2 4 5 -> 3
4 5 3 1 -> 2
2 3 4 1 -> 5
```

Raspuns 5.

Maxim memorie 512 bytes.

### Delimitari

Pentru 50 de puncte le lasam mai putine numere sa poata sa faca vectori caracteristici.

## Lychrel numbers @palcu

Se dă un număr să se verifice dacă e [Lychrel](https://en.wikipedia.org/wiki/Lychrel_number) in maxim 50 de iteratii. Problema asta ar avea numere mari, adunari si verificare de palindom.

# Clasa a 10-a

## World of Warcraft @palcu

Ai o matrice, unde ai celule ocupate. Ai N oameni pe pozitiile (Xi, Yi). Sa se determine celula din matrice unde toate caracterele ar efectua cei mai putini pasi ca sa se intalneasca toate. Garantez ca toti se intalnesc undeva.

### Delimitari

Pentru 50 de puncte le dam doar 2 oameni.
De asemenea, le lăsăm pentru 100 de puncte soluția în care fac Lee pentru fiecare caracter. Șmenul e că trebuie să se prindă că au nevoie de o singură matrice, și să ia din matricea aia celula cu cea mai mică valoare.

# Problemele la echipaj

## Cutii Google @palcu

Ai N cutii, pentru fiecare cutie ai latura ei si greutate. Sa se spuna lungimea cea mai mare a pentru un turn de cutii, unde latura si greutatea sunt mereu mai mici sus.

## Studenți Eminenți @andrei

Se da o secventa de N de numere. Sa se verifice daca exista 4 numere care dau o anumita suma, poate si cate combinatii exista :)
Indicii valorilor ce formeaza o solutie trebuie sa fie distincti.

-- Complexitate 1 - O(N ^ 2) -> hash-uri
-- Complexitate 2 - O(N ^ 2 * log) -> sortare
-- Complexitate 3 - O(N ^ 3 * log) -> 3 for-uri + cautare binara
-- Complexitate 4 - O(N ^ 4) + bulaneli care sper sa intre aici 

