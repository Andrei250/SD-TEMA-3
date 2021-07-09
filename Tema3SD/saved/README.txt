Dumitrescu Andrei 313CC

Task1:
    Citesc graful in 2 liste de adiacenta. O lista contine graful orientat,
    iar cealalta graful neorientat cu muchiile acestuia.
    Verific daca graful are cicluri initiale, iar daca nu are formez un vector
    de structuri pentru a calcula costul minim al formarii unui ciclu 
    in nodul respectiv calculand cost1 suma muchiilor care si-au pastrat 
    sensul si cost2 suma muchiilor inversate, iar raspunsul este minimul
    dintre acestea. La final aflu nodul cu valoarea cea mai mica. Daca 
    nu exista un ciclu care se poate forma atunci afisez -1.

Task2:
    Am citit graful intr-o lista de adiacenta implementata dinamic si apoi 
    am aplicat algoritmul lui dijkstra cu toti reprezentantii ca noduri
    initiale. La fiecare pas am verificat daca nodurile in care urmeaza
    sa trec au costul mai mare si exista o varianta mai buna de 
    reprezentant fata de nodul acela si am facut update la valoarea nodului.
    La afisare am verificat daca la acel nod se poate ajunge sau nu.

Task3:
    Am citit graful intr-o lista de adiacenta implementata dinamic si apoi am
    aplicati un algoritm BFS pentru fiecare pereche de noduri start stop si
    am creeat pentru fiecare noduri o lista cu posibili parinti ai drumului
    minim. Astfel dupa aceea am plecat de la stop spre start si am verificat
    ce noduri se afla pe toate drumurile minime.

Task4:
    Am citit matricea si directiile in care trebuie sa mearga David. Apoi am 
    aplicat un DFS pe matrice astfel incat pentru fiecare nod retin directia
    in care urmeaza sa mearga si in functie de acea directie ce noduri
    parcurge. Nodurile care urmeaza sa fie adaugate indeplinesc conditia ca
    valoarea lor este mai mica decat ce a nodului din care vin. La final
    am numarat nodurile cu valoarea K + 1, care sunt noduri terminale.

Bonus:
    Am citit graful si am sortat muchiile crescator. Apoi am utilizat Kruskal
    pentru a creea un arbore doar cu muchii de cost minim. Astfel pentru 
    fiecare muchie am verificat daca capetele sale fac parte din aceeasi
    componenta. Daca nu faceau parte le uneam folosind algoritmul UnionByRank
    de complexitate logaritmica. Dupa am facut un DFS pe graful cu muchiile
    minime pentru a stabili parintele fiecarui nod si nivelul pe care se afla.
    Apoi fac citirea fiecare perechi de noturi start stop si aplic LCA 
    pentru aceste 2 noduri si aflu muchia de cost maxim de pe drumul dintre
    cele 2 noduri.