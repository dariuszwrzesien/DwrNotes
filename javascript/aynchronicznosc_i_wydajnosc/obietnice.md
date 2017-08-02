**Promises** - obietnice

Ideą stojącą za powstaniem i korzystaniem z obietnic jest zerwanie z nagminnie wykorzystywanymi funkcjami zwrotnymi.
Jeśli umieścimy nasz kod zapewniający kontynuację działania programu w funkcji wywołania zwrotnego, a funkcję tę w innej części kodu
i zaciskamy kciuki aby wywołanie się powiodło to tym samym odwracamy kontrolę przepływu programu.

Rozważmy następujące zadanie:
"Dodaj x i y , ale jeśli którakolwiek z wymienionych wartości nie jest jeszcze gotowa, to poczekaj
i dodaj je natychmiast, gdy tylko stanie się to możliwe".

Powyższe zadanie można rozwiązać w oparciu o funkcje zwrotne (callback).

```javascript
    function add(getX, getY, callback) {
        var x, y;

        getX(function(xVal){
            x = xVal;
            if (y != undefined) { //czy obie wartości są gotowe
                callback(x+y);
            }
        });

        getY(function(yVal){
            y = yVal;
            if (x != undefined) {
                callback(x+y);
            }
        });
    }

    //Funkcje fetchX() i fetchY są synchroniczne lub asynchroniczne
    add(fetchX, fetchY, function(sum){
        console.log(sum);
    })

```

Poniżej zaprezentowano rozwiązanie z użyciem obietnic:

```javascript
function add (xPromise, yPromise) {
    // Wywołanie Promise.all([ .. ]) pobiera tablicę obietnic.
    // Wartością zwrotną jest nowa obietnica oczekująca
    // na zakończenie wszystkich pozostałych.

    return Promise.all([xPromise, yPromise])
            .then(function(values) { // Kiedy obietnica zostanie rozwiązana, pobieramy otrzymane wartości 'X' i 'Y', a następnie je dodajemy.
                // W poniższym poleceniu values to tablica komunikatów
                // otrzymanych z wcześniej rozwiązanych obietnic.
                return values[0] + values[1];
            });
}

// Funkcje fetchX() i fetchY() zwracają obietnice dla
// odpowiednich wartości, które mogą być dostępne
// teraz lub później.
add(fetchX(), fetchY())
    .then(function(sum){ // Mamy obietnicę odpowiedzialną za obliczenie sumy dwóch liczb.
        console.log(sum);
    });

```

