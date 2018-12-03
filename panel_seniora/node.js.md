###Język
- Zna podstawową składnię języka
- Wie co to hoisting
```javascript
    a = 2;
    var a;
    console.log( a ) //2
```
Powyższy kod kompilator traktuje w taki sposób:
```javascript
    var a; //tworzy zmienną
    a = 2; //przypisuje zmiennej wartość
    console.log( a );
```
Hoisting to **przeniesienie deklaracji** zmiennych i funkcji na początek kodu.
Przeniesienie na początek kodu dotyczy jedynie deklaracji, natomiast wszelka
logika (np. przypisanie) **jest pozostawiona na dotychczasowym miejscu**.

Hoistingowi podlegają zmienne i funkcję, jednak funkcję mają pierwszeństwo przed zmiennymi.
Każda powielająca się deklaracja funkcji nadpisuje poprzednią.

Podsumowując, wszystkie deklaracje w zakresie, niezależnie od miejsca ich występowania, są przetwarzane przed rozpoczęciem wykonywania kodu. Można powiedzieć że deklaracje (funkcji i zmiennych) są przenoszone na początek ich zakresów - i to właśnie jest hoisting. Kod odpowiedzialny za przypisanie lub wykonanie pozostaje w dotychczasowym miejscu.

- Wie w jaki sposób skopiować obiekt w JS (jak wygląda to low-level – złożoność)

Proste przypisanie obiektu do zmiennej nie tworzy oczywiście nowej instancji tego obiektu, zamiast tego tworzony jest wskaźnik
do obiektu co skutkuje tym że jeśli będziemy zmieniać coś w nowoutworzonym obiekcie to również zmieniać się będzie obiekt kóry posłużył nam do przypisania.

```javascript
const ob1 = {
test: '123'
}

const ob2 = ob1;
console.log(ob2.test); //123

ob2.ddd = '321';

console.log(ob1); //{test:'123', ddd: '321'}
```

Naiwnym wydaje się sposób kopiowania po parametrach bo gdy natrafimy na obiekt kótry posiada jako paramaetr inny obiekt
skopiujemy jego referencję.

```javascript
function copy(mainObj) {
  let objCopy = { }; // objClone will store a copy of the mainObj
  let key;

  for ( key in mainObj ) {
    objCopy[key] = mainObj[key]; // copies each property to the objClone object
  }
  return objCopy;
}

const mainObj = {
  a: 2,
  b: 5,
  c: {
    x: 7,
    y: 4,
  },
  d: function d() {
    return 3;
  }
}

const a = copy(mainObj);
a.d = () => {
  return 4;
}
a.c.x = 123;

console.log( a );
console.log( mainObj );
```
Płytkie (shallow) kopiowanie obiektów:

Object.assign();
Pozostaje nadal problem z referencjami do obiektów w obiekcie - kopiowane są funkcje

Użycie JSON...

JSON.parse(JSON.stringify(object));

Nie nadaje się do użytku gdy obiekt zawiera jakieś metody.

- Rozumie jak działa referencja
- Zna i rozumie Strict Mode
Przy włączonym Strict Mode:

Przypadkowe zmienne globalne są traktowane jako błąd. 

```javascript
"use strict";

//przypadkowe zdefiniowanie zmiennej globalnej

for (i = 0; i < length; i++) { // TypeError
    // some code...
};

//literowki

var userName = '';

function setUserName(name) {
    user_name = name; // TypeError
};
```
Próba nadpisania nienadpisywalnych obiektów globalnych to błąd.
```javasctipt
"use strict";

NaN = 3; // TypeError
Infinity = 3; // TypeError
```
Duplikujące się nazwy własności w obiektach to błąd
```javascript
"use strict";

var o = {'a': 1, 'b': 2, 'a': 3} // SyntaxError

```
Argumenty w funkcjach muszą mieć unikalne nazwy
```javascript
"use strict";

function concat(a, b, a) { // SyntaxError
    return '' + a + b + a;
}
```

- Potrafi podzielić aplikację na osobne pliki i moduły (require)
- Zna bardzo dobrze pojęcie scope i closure (w szczególności zna ryzyka z tym związane, memory leak) -

**Zakres** to zbiór reguł określających miejsce i sposób wyszukiwania zmiennej, na przykład za pomocą nazwy.

Zakres może być zagnieżdżony w innym zakresie. Jeśli zmienna nie zostanie znaleziona w zakresie bieżącym,
Silnik sprawdza kolejny zakres zewnętrzny i kontynuuje tę operację aż znajdzie zmienną lub dotrze do najbardziej
zewnętrznego (globalnego) zakresu.

Wyżej wspomniane wyszukiwanie może być związane z przypisaniem wartości zmiennej i wówczas mamy odwołanie typu LHS

```javascript
    var a = 42;
```

lub może być związane z pobraniem wartości zmiennej (odwołanie typu RHS).

```javascript
    console.log(a);
```

**Domknięcie** można potraktować jako sposób „zapamiętania” i kontynuacji
dostępu do zakresu funkcji (jej zmiennych) nawet po zakończeniu wykonywania
danej funkcji.

```javascript
    function prefixer(prefix) {

        function join(string) {
            return prefix + string;
        }

        return join;
    }

    var prefixAAA = prefixer('AAA_');
    var prefixZZZ = prefixer('ZZZ_');



    console.log(prefixAAA('przykladowy_string'));
    console.log(prefixAAA('kolejny_przykladowy_string'));
    console.log(prefixZZZ('tym_razem_inny_prefix_niz_poprzednio'));
```

Sposób działania powyższego kodu:
1. podczas wywołania prefixer('AAA_') i przypisania do zmiennej prefixAAA, otrzymujemy odwołanie do funkcji wewnetrznej
join(...), która pamięta że wartością zmiennej prefix jest AAA_.
2. podczas wywołania prefixer('ZZZ_') otrzymujemy także odwołanie do funkcji wewnętrznej join(...),
która pamięta przekazaną wartość prefix = 'ZZZ_';
3. w trakcie wywołania prefixAAA('przykladowy_string') następuje defacto wywołanie funkcji join(...)
z parametrem ('przykladowy_string') wartosc zmiennej prefix została natomiast zamknieta tam już wcześniej
podczas przypisania prefixAAA = prefixer('AAA_'), stąd też w rezultacie otrzymujemy:
**AAA_przykladowy_string**
4. Podobnie sytuacja ma się w kolenych wywołaniach funkcji:
prefixAAA('kolejny_przykladowy_string');
prefixZZZ('tym_razem_inny_prefix_niz_poprzednio');

W rezultacie wywołania skryptu otrzymujemy:

AAA_przykladowy_string

AAA_kolejny_przykladowy_string 

ZZZ_tym_razem_inny_prefix_niz_poprzednio

- Potrafi wyjaśnić jak działa prototype w JS

Kiedy odwołujemy się do właściwości obiektu ale ta właściwość nie istnieje
to Javascript użyje odwołania do wewnętrznego prototypu obiektu.
Wewnętrzne powiązanie odwowłania prototypu obiektu do innego powstaje w
chwili tworzenia danego obiektu.

```javasctipt
    var object1 = {
        a: 'Hello world'
    }

    var bar = Object.create( object1 );
    bar.b = "Witaj !!!";

    bar.b; // "Witaj !!!"
    bar.a; // "Hello world" // delegacja do object1
```

Metoda **Object.create()** tworzy nowy obiekt na podstawie prototypu i własności.
Ogólna postać metody wygląda następująco

**Object.create(*proto*[, propertiesObject])**


*proto*
- obiekt który jest prototypem dla nowo tworzonego obiektu.

*propertiesObject*
- opcjonalne, właściwości które zostaną dodane do nowo
utowrzonego obiektu.

Wracając do prototypowania,  właściwość **a** tak naprawdę nie istnieje w obiekcie bar,
ale z powodu połączenia prototypu między *bar* i *object1* Javascript automatycznie przechodzi do szukania
właściwości *a* w obiekcie *object1*.

**Prototypy macierzyste**

Każdy z wbudowanych objektów macierzystych zawiera własny obiekt **.prototype**
(Array.prototype, String.prototype itd.)

Obiekty te mają unikatowe zachowanie w odniesieniu do konkretnego potypu obiektów,
i tak na przykład wartości prymitywne typu **string** dzięki automatycznemu opakowaniu w
obiekt macierzysty **String**, mają dostęp do **String.prototype**.

Konkewncja zawarta w dokumentacji pozwala tez na zapis skrócony:
**String.prototype.XYZ** można zapisać w postaci **string.XYZ**.

```javascript
    var a = 'abc';
    var i = a.indexOf('b');
    var c = a.charAt(0);
    var s = a.substr(2);
    var s2 = a.substr(1);

    console.log(i); //1
    console.log(c); //"a"
    console.log(s); //"c"
    console.log(s2); //"bc"
```

Żadna z powyższych metod nie modyfikuje łańcucha bezpośrednio. Wprowadzenie zmian powoduje powstanie nowej wartości na postawie istniejącej.

Inne prototypy zawierają zachowania odpowienie dla ich typów, np. **Number.prototype.toFixed()** itd.

Natomiast wszystkie funkcje dysponują dostępem do metod: **apply(...), call(...), bind(...)**, ponieważ
są one defniowane przez właściwość **Function.prototype**

- Rozumie koncepcję typów w JS oraz rozumie ich reprezentację natywną (zajętość w pamięci, string – utf, number)
- Rozumie koncepcję eventów, potrafi wykorzystać EventEmitera
- Jest na bieżąco z nowymi wersjami języka (wie co będzie dostępne w przyszłości)

https://github.com/tc39/proposals

Z ciekawostek:
Prywatne zmienne oznaczone # - w testach


- Orientuje się w temacie ECMAScript 6, 7 (arrow function, string interpolation, classes, generators, WeakSet)
arrow function: https://developer.mozilla.org/pl/docs/Web/JavaScript/Reference/Functions/Funkcje_strzalkowe

string interpolation: https://developer.mozilla.org/pl/docs/Web/JavaScript/Referencje/template_strings

classes: https://developer.mozilla.org/pl/docs/Web/JavaScript/Reference/Classes

generators: http://shebang.pl/artykuly/es6-bez-tajemnic-generatory/

WeakSet: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WeakSet

WeakSet objects are collections of objects. An object in the WeakSet may occur only once; it is unique in the WeakSet's collection.

The main differences to the Set object are:

In contrast to Sets, WeakSets are collections of objects only and not of arbitrary values of any type.
The WeakSet is weak: References to objects in the collection are held weakly. If there is no other reference to an object stored in the WeakSet, they can be garbage collected. That also means that there is no list of current objects stored in the collection. WeakSets are not enumerable


- Potrafi szczegółowo opowiedzieć o function.prototype.(call/bind/apply)




- Wie jak działa garbage collector i rozumie co oznacza w tym kontekście trzymanie referencji do obiektów





- Używa w praktyce znanych mu wzorców
- Rozumie szerszy koncept używania eventów – publisher/subscriber pattern
- Rozumie działanie "require" i zna konsekwencje miejsca jego użycia (cache, czas życia, wiele wersji tej samej biblioteki)





- Potrafi opowiedzieć o Object.defineProperty i wie jak zaimplementować setter/getter w node
- Potrafi pracować ze strumieniami w node.js
- Wie co to binding.gyp i potrafi odnaleźć w natywnym module kod C++ odpowiedzialny za daną funkcję
- Zna przydatne w js elementy programowania funkcyjnego (np. funkcje wyższego rzędu)
- Wie co to typedArray i zna idee widoków na nich

###Asynchroniczność
- Wie co to jest callback
- Potrafi poprawnie rozpoznać w przykładowym kodzie jakie operacje są asynchroniczne a jakie synchroniczne
- Umie zaimplementować obsługę błędów w kodzie asynchronicznym (error-first callback)
- Wie i rozumie konsekwencje tego, że node jest single-thread
- Zna idee promise’ów 
- Potrafi wyjaśnić jakie są ograniczenia i jakie zalety stosowania promise’ów
- Potrafi wyjaśnić co to jest "Event Loop" i "Thread Pool"
- Zna child_processes i sposoby komunikacji z wątkami
- Zna pattern: coroutine i yield’y
- Zna pattern: async/await

###Umiejętności praktyczne
- Potrafi do gotowego serwisu dodać własną metodę REST’ową (bazując na przykładzie).
- Zna idee middleware’ów i potrafi zaimplementować własny
- Potrafi debugować i profilować aplikację
- Potrafi samodzielnie w sensowny sposób zorganizować strukturę plików na serwerze
- Potrafi zaimplementować dwukierunkową komunikację serwer-klient (np. socket.io)
- Potrafi debugować i profilować aplikację
- Potrafi zaimplementować serwer wykorzystujący wszystkie dostępne rdzenie maszyny
- Potrafi samodzielnie zaimplementować mikroserwis obsługujący http codes, headersy, body, gzip compresion, multi-threads, static resources, etags etc
- Potrafi zlokalizować (profiler/node-heapdump) i usunąć memory leaki
- Rozumie koncepcje reverse-proxy i ssl-off-load i umie ją zaimplementować np. przy użyciu nginx’a
- Potrafi zaproponować zestaw bibliotek adresujący typowe problemy w projekcie

###Narzędzia
- Wie jak działa package.json i potrafi używać podstawowej składni narzędzia npm (yarn)
- Potrafi korzystać z task runnera (grunt/gulp/etc) i w razie potrzeby zrozumieć konfigurację konkretnego zadania
- Zna idee semantic versioning
- Wie czym się różnią dependencies, devDependencies, peerDependencies w package.json
- Potrafi skonfigurować testy automatyczne i wpiąć je w task runner (grunt/gulp/mocha/etc)
- Zna idee semantic versioning
- Wie czym się różnią dependencies, devDependencies, peerDependencies w package.json
- Zna jakiś system szablonów (np. ejs)
- Potrafi skonfigurować i świadomie stosować *lint
- Potrafi zapewnić swojemu mikroserwisowi stałe działanie (forever, pm2, etc)
- Potrafi rozstawić serwer npm do prywatnych modułów
- Zna zaawansowane metody npm (dedupe, shrinkwrap, outdated)
