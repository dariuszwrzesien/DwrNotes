**Konwersja typów - *number***

Jeśli wartość inna niż typu **number** używana jest w sposób wymagający, aby była typu **number**,
stosowana jest operacja abstrakcyjna **ToNumber**.

Wartości:
* true lub fasle, stają się wartościami 1 i 0,
* undefined staje się NaN,
* null przyjmuje wartość 0

Jeśli konwertowany typ nie jest typem prymitywnym to szukana będzie metoda **valueOf()** lub **toString**
która zapewni wartość do przeprowadzenia konwersji typów.
Jeśli żadna operacja nie może zapeniwć wartości prymitywnej, zostanie zgłoszony błąd *TypeError*.

```javascript
    var a = {
            valueOf: function(){
            return "42";
        }
    };

    var b = {
        toString: function(){
            return "42";
        }
    };

    var c = [4,2];

    c.toString = function(){
        return this.join( "" ); // "42"
    };

    Number(a);       // 42
    Number(b);       // 42
    Number(c);       // 42
    Number("");      // 0
    Number([]);      // 0
    Number(null);    // 0
    Number(["abc"]); // NaN

```


