# Teleport

Bobut a cazut intr-o capacana intinsa de fratii lui extraterestri, si este in pericol. El s-a trezit la capatul unui coridor foarte lung impartit in `N` celule. Pentru a scapa el trebuie sa ajunga dincolo de capatul opus. 
Incercand sa scape, Bobut a descoperit toate proprietatile speciale ale coridorului:

* Celulele din coridor sunt numerotate de la `0` la `N-1`.
* El s-a trezit in celula cu numarul `0`.
* O data ce a ajuns intr-o celula, este imposibil sa ajunga intr-o celula cu numar de ordine mai mic.
* In fiecare celula este scris un numar pe podea.
* Sunt posibile 3 moduri de deplasare:
  * Facand un pas, el se poate deplasa in celula cu numarul de ordine consecutiv.
  * Din orice celula el se poate teleporta `V` celule mai in fata, unde `V` este numarul scris pe podeaua celulei in care se afla.
  * Teleportorul lui personal il poate teleporta `K` celula mai in fata, dar din pacate mai are baterie pentru `M` astfel de teleportari

Bobut nu doar ca vrea sa scape, ci vrea sa scape trecand prin cat mai putine celule.

# Cerinta

Scrieti un program care determina care este numarul minim de celule prin care Bobut trebuie sa treaca astfel incat sa ajunga exact dupa ultima celula din coridor.

# Date de intrare

Fisierul de intrare `teleport.in` contine pe prima linie 3 numere naturale `N`, `M` si `K` reprezentand numarul de celule din coridor, numarul de teleportari disponibile in teleportorul lui personal respectiv lungimea unei teleportari personale.
Pe a doua linie sunt N numere separate prin spatiu reprezentand numerele scrise in celulele coridorului.

# Date de iesire

Fisierul de iesire `teleport.out` va contine un singur numar reprezentand numarul minim de celule prin care Bobut trebuie sa treaca pana ajunge in afara coridorului.

# Restrictii

* 1 <= N <= 100000
* 0 <= M <= 3
* Pentru 30% din teste, valoarea lui M este 0
* 0 <= Numarul scris pe podea <= 100

# Exemple

in: 
10 1 5
2 8 3 1 0 3 2 2 2 2

out:
3

Sunt 2 moduri de a iesi in 3 pasi. 1 (pas) 2 ( teleport podea) 10 (pas) 11
sau 1 (teleport podea) 3 (teleport podea) 6 ( teleport personal ) 11
