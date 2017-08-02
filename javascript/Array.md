**Array.every**

Metoda  every() sprawdza, czy wszystkie elementy w tablicy przechodzą test zrealizowany w postaci dostarczonej funkcji.

Metoda ***every*** wykonuje dostarczoną funkcję callback raz dla każdego elementu tablicy do momentu, kiedy znajdzie taki element,
dla którego funkcja callback zwróci wartość false. Jeżeli taki element zostanie znaleziony, test zostanie przerwany,
a metoda ***every*** zwróci wartość false. W przeciwnym wypadku (callback zwraca wartość true dla wszystkich elementów) ***every***
zwróci true. Funkcja callback wywoływana jest jedynie dla indeksów tablicy, którym została przypisana wartość;

```javascript
    function isBigEnough(element, index, array) {
      return (element >= 10);
    }
    passed = [12, 5, 8, 130, 44].every(isBigEnough);
    // fałsz
    passed = [12, 54, 18, 130, 44].every(isBigEnough);
    // prawda
````

**Array.some**

Sprawdza, czy jakikolwiek element tablicy zalicza test zaimplementowany przez dostarczoną funkcję.

metoda ***some*** wykonuje funkcję callback() na każdym elemencie tablicy, aż znajdzie taki, dla którego callback zwróci
prawdę (true). Jeżeli taki element zostanie znaleziony, ***some*** zakończy swoje działanie i zwróci prawdę (true),
w przeciwnym przypadku (gdy callback zwróci fałsz dla każdego z elementów) ***some*** zwróci false.
Tablice traktowane są jako "zwarte" - czyli callback zostanie wywołane **dla każdego elementu o indeksie mniejszym
niż długość tablicy**, *nawet jeśli poszczególne indeksy nie zostały wcześniej zadeklarowane*.

```javascript
    function isBigEnough(element, index, array) {
      return (element >= 10);
    }
    passed = [2, 5, 8, 1, 4].some(isBigEnough);
    // fałsz
    passed = [12, 5, 8, 1, 44].some(isBigEnough);
    // prawda
```

**Array.reduce**