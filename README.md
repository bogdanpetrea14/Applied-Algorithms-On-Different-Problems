# Applied-Algorithms-On-Different-Problems
Some C++ programs aiming to help practicing the use of well known algorithms, like Dijkstra, BFS, DFS and so on

Serverele
Complexitate temporala: O(nlog(n)) si spatiala: O(n)

Cautarea se va face in intervalul min(Ci) si max(Ci). Ulterior, pentru intervalul
acesta, vom calcula puterea pentru mijlocul intervalului si pentru mijloc + toleranta.
Pe baza acestor calcule(daca a doua putere calculata este mai mare decat prima,
putem creste puterea, deci marim intervalul al mij si max, altfel scadem la min si mij).

Colorare

Complexitate temporala: O(k + log(n)) si spatiala: O(k)

Problema se rezolva cu programare dinamica si formule matematice. Observam ca pentru fiecare
bloc de tipul H, numarul de posibilitati de colorare este de 2 * 3 ^ blocuri, iar pentru
cele de tipul V este 3 * 2 ^ (blocuri - 1). Astfel, restrangem zonele consecutive de acelasi tip,
avand doar zone alternante de H si V. Calculam puterile de 2 si 3 necesare pentru a rezolva problema, in
final impartind la 3 ^ (numarul de trecerei de la H la V si viceversa).
Ridicarea la putere a fost inspirata de aici https://infoas.ro/lectie/104/ridicarea-la-putere-in-timp-logaritmic-in-c-exponentiere-rapida

Compresie

Complexitate temporala: O(A + B), unde A si B sunt lungimile secventelor si spatiala: O(A + B)

Calculam pentru fiecare sir, sirul sumelor partiale. Astfel, daca cele doua siruri nu au ultima
suma egala, inseamna ca nu exista o posibilitate de compresie. Altfel, numaram elementele din sirul
sumelor partiale ale lui A care se regasesc si in B, acesta fiind rezultatul final al comprimarii (lungimea
finala a sirului comprimat).


Criptare

Complexitate temporala: O(n * m) pentru generarea lungimii, O(n ^ 2) pentru sortare si spatiala: O(n + m), unde n 
e numarul de cuvinte si m lungimea maxima a unui cuvant.

Algoritmul genereaza frecventa tuturor literelor si calculeaza pentru fiecare o posibila parola (acest lucru
a mers acum, pentru ca stiam ca sunt maxim 8 litere existente in text, daca ar fi fost mai multe caractere, 
atunci ar fi devenit destul de ineficient si ar fi trebuit sa avem alta abordare). Basically, sortam lista de
cuvinte ca sa contina la inceput cuvintele care au cel mai mare raport intre continerea literei si lungimea cuvantului,
urmand cuvintele care nu contin deloc litera (in cazul acesta, sortam cuvintele dupa lungime).
De fiecare data, adauagam un nou cuvant si verificam daca se pastreaza dominanta unei litere, facand asta pentru
fiecare litera care apare in text. La final, alegem rezultatul maxim.


Oferta

Complexitate temporala: O(n) si spatiala: O(n)

Folosim un vector de programare dinamica. Pentru cazurile de baza, avem primele 3 produse care vor fi combinate.
Ulterior, pentru un produs i, verificam care este minimul intre pastreaza produsului singur, combinarea lui cu cel
de dinainte, sau combinarea sa cu cele de dinainte, adunand dp ul corespunzator (la cel singur dp[i - 1], la gruparea
a doua produse, dp[i - 2], si la trei dp[i - 3]).

Numarare
---

> Complexitate temporala, O(N + M)
- pentru crearea grafurilor, O(M) pentru fiecare
- sortarea topologica, O(N + M)
- numararea drumurilor, O(N + M)

> Complexitate spatiala, O(N + M)

> Functionalitate
- programul numara drumurile distincte, comune intre doua grafuri, dintre primul si ultimul nod, folosind sortarea topologica combinata cu programarea dinamica
- la citire, construim primul graf, si, in loc sa il construim si pe al doilea, citim fiecare muchie pe rand, construind astfel un graf care reprezinta drumurile comune din cele doua
- dupa, vom genera o sortare topologica a grafului rezultat, peste care vom folosi programarea dinamica pentru a genera toate drumurile de la primul nod la ultimul


Trenuri
---

> Complexitate temporala, O(N + M)
- O(M) pentru construirea grafului
- O(N + M) pentru DFS

> Complexitate spatiala, O(N + M)

> Functionalitate
- programul construieste cel mai lung drum intre doua orase
- pornind din orasul de start, incercam sa construim, folosind DFS-ul, drumul cel mai lung
- cand calculam rezultatele, adica distantele intre orase, le memoram intr-un memo, pentru a evita recalcularea lor (astfel putand reduce complexitatea temporala)


Drumuri
---

> Complexitatea temporala, O((N + M)log(N))\
> Complexitatea spatiala, O(N + M)

> Functionalitate

- algoritmul calculeaza costul minim dintre doua puncte la un al treilea (adica costul minim pe submultimea de muchii intre drumurile dintre x si z si y si z)
- pentru acest lucru, avem o abordare directa, in care calculam distanta de la nodurile x si y la toate celelalte noduri, rezultatul final fiind suma dintre **dist_x[z]** si **dist_y[z]**
- totusi, exista cateva probleme cu aceasta abordare, una foarte importanta fiind ca nu ia in considerare drumuri comune (adica daca intre cele doua drumuri ar putea exista o portiune comuna, nu se tine cont si e numarata de doua ori)
- un alt caz pe care algorimtul nu functioneaza e atunci cand drumurie de la x si y catre z, independente, au un drum de cost minim, dar daca le luam impreuna, gasim o submultime cu suma tuturor muchiilor mai mica

		|---------------3------------------|
		|                                  |
		s2-------1--------|                |
							|                |
							v                v
		s1-------1------->1--------3------>end
		|                                  ^
		|                                  |
		|>--------------3------------------|



---
---
