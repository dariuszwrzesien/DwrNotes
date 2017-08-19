**Konwersja typów - *boolean***

W języku JavaScript występują słowa kluczowe **true** i **false**, które zachowują się tak jak można się tego spodziewać.
Niestety można spotkać się z błędnym przekonaniem że wartości **1** i **0** są tożsame z **true** i **false**.
W innych językach może to być prawdą ale w JavaSctipt nie jest. W języku JavaScript **1** i **0** to wartości
typu **number**, można oczywiście wykonac konwersję **1** na **true** ale te wartości nie są takie same.

**Wartości fałszywe - "falsy"**

W języku JavaScript wszystkie wartości mozna podzielić na dwie kategorie:
1. Wartości, które staną się wartościami **false** po wykonaniu konwersji na typ **boolean**.
2. Wszystkie inne wartości niż powyższe staną się wartościami **true**.

A zatem istnieje wąska lista wartości które w wyniku konwersji typu na **boolean** staną się wartościami **false**.
Zatem wartości fałszywe (ang. falsy) to:

* undefined,
* null,
* false,
* +0, -0 i NaN,
* ""

**Wartości prawdziwe - truly**

Wartość jest prawdziwa gdy nie ma jej na liście wartości fałszywych.

```javascript
var a = "false",
var b = "0",
var c = "''",

var d = Boolean(a && b && c);

console.log(d); //true

var e = []; //pusta tablica
var f = {}; //pusty obiekt
var g = function(){}; //pusta funkcja
var h = Boolean(e && f && g);

console.log(h); //true
```

Należy pamiętać że wywołanie konwersji odbywa się bez słowa kluczowego **new**.
Słowem kluczowym **new Boolean(...)** tworzymy obiekt opakowujący.

**Operator jednoargumetowy *"!"* i *"!!"***

Operator negacji **!** jawnie przeprowadza konwersję typu na typ **boolean**.
Problem polega na ty, że operator ten dokonuje również odwrócenia wartości z prawdziwej na fałszywą, lub odwrotnie.
Zatem najczęściej wykorzystywany sposób konwersji jawnej na typ **booolean** to zastosowanie podwójenej negacji **!!**.


```javascript
var a = "0";
var b = [];
var c = {};
var d = "";
var e = 0;
var f = null;
var g;

Boolean(a); //true
Boolean(b); //true
Boolean(c); //true

Boolean(d); //false
Boolean(e); //false
Boolean(f); //false
Boolean(g); //false

var a = "0";
var b = [];
var c = {};
var d = "";
var e = 0;
var f = null;
var g;

!!a; //true
!!b; //true
!!c; //true

!!d; //false
!!e; //false
!!f; //false
!!g; //false
```

Gdyby nie użyto funkcji Boolean(..) lub operatora !! , dowolna z tych operacji konwersji typów
opartych na operacji ToBoolean przebiegłaby niejawnie w przypadku zastosowania ich w kontekście
typu **boolean** , takiego jak instrukcja if (..) .. . Celem jest tutaj jednak jawne wymuszenie konwersji
typu wartości na typ **boolean** , aby wyraźnie pokazać, że zamierzona jest konwersja typów bazująca
na operacji **ToBoolean**.
