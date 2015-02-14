# Teleport

Bobut și prietena lui Neytiri au căzut într-o capacană întinsă de frații lor extratereștri, și sunt în pericol. Bobut s-a trezit la capătul unui coridor foarte lung împarțit în `N` celule. La sfârșitul coridorului se află prietena lui care, îl așteaptă de Valentine's Day să meargă la un concert romantic.
Încercând să scape, Bobut a descoperit toate proprietățile speciale ale coridorului:

* Celulele din coridor sunt numerotate de la `0` la `N-1`.
* El s-a trezit în celula cu numărul `0`.
* O dată ce a ajuns într-o celulă, este imposibil să ajungă într-o celulă cu număr de ordine mai mic.
* În fiecare celulă este scris un număr pe podea.
* Sunt posibile 3 moduri de deplasare:
  * Făcând un pas, el se poate deplasa în celulă cu numărul de ordine consecutiv.
  * Din orice celulă el se poate teleporta `V` celule mai in față, unde `V` este numărul scris pe podeaua celulei în care se află.
  * Teleportorul lui personal îl poate teleporta `K` celule mai in față, dar din păcate mai are baterie pentru `M` astfel de teleportări.

Bobut nu doar că vrea sa scape, vrea să ajungă în numărul cel mai mic de pași la prietena lui.

# Cerință

Scrieți un program care determină care este numărul minim de celule prin care Bobut trebuie să treacă astfel încât să ajungă exact după ultima celula din coridor.

# Date de intrare

Fișierul de intrare `teleport.in` conține pe prima linie 3 numere naturale `N`, `M` și `K` reprezentând numărul de celule din coridor, numărul de teleportări disponibile în teleportorul lui personal respectiv lungimea unei teleportări personale.
Pe a doua linie sunt N numere separate prin spațiu reprezentând numerele scrise în celulele coridorului.

# Date de ieșire

Fișierul de ieșire `teleport.out` va conține un singur număr, reprezentând numărul minim de celule prin care Bobut trebuie să treacă până ajunge în afară coridorului.

# Restricții

* 1 <= N <= 100000
* 0 <= M <= 3
* Pentru 30% din teste, valoarea lui M este 0
* 0 <= Numărul scris pe podea <= 100

# Exemple

in:
10 1 5
2 8 3 1 0 3 2 2 2 2

out:
3

Sunt 2 moduri de a ieși în 3 pași. 1 (pas) 2 (teleport podea) 10 (pas) 11
sau 1 (teleport podea) 3 (teleport podea) 6 (teleport personal) 11
