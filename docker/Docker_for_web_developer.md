
## Komendy

docker images - obrazy dockerowe
docker ps - uruchomione kontenery
docker ps -a - wszytskie kontenery

docker run [image_name] - tworzy kontener z obrazu i uruchamia
docker run -p 80:80 [image_name] - to samo co wyżej z tym że mapuje port z locala na port dockerowy
docker run -d --name my-postgres postgre - uruchamia kontener dokerowy "postgres" jako deamon (-d), ustawia mu nazwę zdefiniowaną przez użytkownika "my-postgres"

docker-machine env default ?
docker-machine ls
docker-machine status
docker-machine start
docker-machine stop

docker rmi - usuwa obraz dockerowy (remove images)

docker exec -it [docker_container_name] /bin/bash - dostanie się do działającego kontenera dockerowego za pomocą basha

---

## Tworzenie Data Volume
```
docker run -p 8080:3000 -v $(pwd):/var/www node 
```
-v - tworzy volume,

$(pwd):/var/www - host location - nasz obecny folder w którym sie znajdujemy mapujemy do folder /var/www w kontenerze,
node - to nazwa obrazu dokerowego

```
docker inspect [container_id/name] - pokazuje jak mapowany jest volume
```
```
Mounts:[
{
...
"Source": "/src"
"Destination": "/var/www"
...
"RW": true
}
]
```


#### Odpalenie dokera wraz z wystarowaniem node

docker run -p 8080:3000 -v $(pwd):/var/www -w"/var/www" node npm start

-w"/var/www" - wskazuje w jakim folderze mamy sie znajdowac na kontenerze, chodzi o to że jeśli nie wskazalibyśmy -w"/var/www" a uruchomilibyśmy "npm start" to komenda ta odpaliła by się w innym folderze niż oczekujemy

---

## Budowanie własnego obrazu dokerowego

Przykładowa lista tego co zamieścimy w Dockerfile

```
FROM		node				- jakiego innego obrazu użyjemy do budowy naszego
MAINTAINER	DWR                             - osoba odpowiedzialna
ENV             NODE_ENV=production             - ustawia zmienna srodowiskowa
COPY		. /var/www			- skopiuj zawartość katalogu w którym się znajdujemy do katalogu /var/www
WORKDIR		/var/www			- ustaw katalog roboczy na /var/www
RUN		npm install			- uruchom komendy
EXPOSE		8080				- otwórz port
ENTRYPOINT	["node", "server.js"]
```

przykładowy Dockerfile dla Node.js znajduje sie w pliku Dockerfile_nodejs

Komenda do budowania obrazu z Dockerfile:

```
docker build -f Dockerfile -t <your username>/node .
```

Kropka na końcu wskazuje kontekst wywołania - więc np. miejsce w którym docker będzie szukał Dockerfile'a

---

## Łączenie kilku kontenerów dokerowych

### Łączenie kontenerów metodą LINKOWANIA (legacy) - metoda polecana do zastosowań DEVELOPERSKICH

Załóżmy że mamy do uruchomienia obraz zawierający naszą aplikację i chcemy go zlikowac z obrazem z bazą danych mongo.

1. Nasz obraz oparty jest o Dockerfile_nodejs i wygląda następująco

```
FROM node:latest

MAINTAINER: Dwr

ENV NODE_ENV=production
ENV PORT=3000

COPY     . /var/www
WORKDIR  /var/www

VOLUME ["/var/www"]

RUN      npm install

EXPOSE $PORT

ENTRYPOINT ["npm", "start"]
```

2. BUDUJEMY kontener za pomocą polecenia:
```
docker build -f Dockerfile_nodejs -t dwr/node .
```
3. Następnie URUCHAMIAMY kontener z mongodb za pomocą polecenia
```
docker run -d --name my-mongodb mongo
```
Zwróc uwagę że ten obraz ma nadaną własną nazwę "my-mongodb".
Jest też uruchomiony jako deamon (flaga: -d).

4. Następnie linkujemy dwa utworzone przed chwilą kontenery dokerowe za pomocą polecenia:
```
docker run -d -p 3000:3000 --link my-mongodb:mongodb dwr/node
```

Polecenie to uruchamia kontener "dwr/node" jako deamon,  eksponuje port 3000, następnie linkuje kontener o nazwie "my-mongodb" ustawiając mu jednocześnie alias "mongodb" (tego aliasu możemy używać wewnątrz apilkacji jako nazyw hosta).
Rozwijając nieco temat aliasu. Jeśli mamy w naszej aplikacji connection string za pomocą którego łączymy się z bazą, to do tej pory np. używaliśmy tam HOST="localhost", ustawiając alias na mongo, możemy zamiast "localhost", czy np. zamiast podawać IP, użyjemy aliasu HOST="mongodb".


### Łaczenie kontenerów dockerowych za pomocą metody Container Network / Brigde Network - metoda polecna do stosowania na STAGE lub PROD.

1. Zakładamy Container Network, nazywany także Brigde Network
```
docker network create --driver bridge isolated_network
```
Powyższa komenda tworzy sieć używając bridge (bridge network) a następnie ustawia tej sieci nazwę "isolated_network"

2. Następnie w obrębie stworzonej "wyizolowanej" sieci uruchamiamy kontenery dokerowe
```
docker run -d --new=isolated_network --name mongodb mongo
docker run -d --net=isolated_network --name nodeapp -p 3000:3000 dwr/node
```

Jak wygląda nasza sieć z przypisanymi do niej kontenerami dokerowymi możemy sprawdzić za pomocą polecenia:
```
docker network inspect isolated_network
```
Tam też zobaczymy jakie ma nazwy oraz adresy IP.


Polecenia związane z sieciami dokerowymi
```
docker network ls //listuje dostepne sieci
docker network inspect [nazwa_sieci] //pokazuje szczegóły zwiazane z konkretną siecią - np jakie ma ona kontenery dołączone, patrz zmienna "Containers"
```

---

## Docker compose 
Docker compose służy do zarządzania kontenerami dokerowymi, szczególnie gdy mamy ich kilka wywoływanie powyższych koment np. do linkowania, może być czasochłonne, w takim przypadku z pomocą przychdzi nam własnie docker compose.

W skrócie, jak działa docker compose?
Konfiguracja dla docker compose trzymana jest w docker-compose.yml, następnie za pomoca docker-compose build, na podstawie pliku odocker-compose.yml budowane są obrazy dockerowe.

### Jak zbudowany jest docker-compose.yml

```
version: '2' // w zaleznosci od wersji bedziemy mieli możliwość uzywania róznynch opcji w pliku docker-compose.yml. Na tę chwile zasada jest taka że jeśli gdzieś (w sieci, na githubie) znajdziemy plik bez wersji to prawdopodobnie jest to plik z wersją 1, ponieważ wersjonowanie wprowadzono dopiero od wersji 2.
 
services: // node, mongodb itd. - w skrócie: jakie obrazy chcemy zbudować
    node:
      build:
        context: .
	dockerfile: Dockerfile_nodejs
      ports:
        - "3000:3000"
      networks:
	- nodeapp-network //Nazwa sieci w której będzie działał kontener
    mongodb:
      image: mongo
      networks:
	- nodeapp-network
networks: //założenie ieci bridge dla kontenerów
  nodeapp-network:
    driver: bridge
```

## Komendy

```
docker-compose build //buduje obrazy dokerowe w oparciu o docker-compose.yml
docker-compose up   //uruchamia kontenery dokerowe na podstawie wczesniej zbudowanych obrazów (z wywołania docker-compose build)
docker-compose up -d //uruchamia sie jako deamon - nie musimy trzymać otwartej konsoli

docker-compose down

docker-compose logs
docker-compose ps
docker-compose stop
docker-compose start
docker-compose rm
```

## Praca z docker compose

1. Mając już przygotowany docker-compose.yml odpalamy komendę:
```
docker-compose build
```
która na podstawie docker-compose.yml zbuduje nam obrazy dokerowe.

Jeśli chcielibyśmy przebudować tylko jeden obraz z tych wymienionych w docker-compose.yml to wtedy:
```
docker-compose build mongo
```

2. Gdy mamy już stworzone obrazy za pomocą komendy docker-compose build, następnym krokiem jest odpalenie komendy:
```
docker-compose up -d
```
która utworzy i uruchomi nam kontenery dokerowe na podstawie wcześniej utworzonych obrazów. Flaga -d inforuje ze chcemy aby proces był uruchomiony jako deamon, np aby można było wyłaczyc konsole a proces ma trwać nadal

Przydatną komenda może być także:
```
docker-compose up --no-deps node
```
--no-deps - informuje żeby komenda nie tworzyła na nowo usług zależnych od node (np. mongo), jedynie przebudowany ma zostać sam node.

3. Na koniec pracy z obrazami dokerowymi (np. koniec dnia pracy) możemy wykonać komendę:
```
docker-compose down
``` 
Zatrzyma ona wszystkie kontenery i je usunie.

Jeśli jednak nie chcemy usuwać kontenerów możemy uzyć komendy:
```
docker-compose stop
```

Jeśli samo zatrzymanie i usunięcie kontenerów nam nie wystarcza możemy także wykonac komende:
```
docker-compose down -- rmi all --volumes
```
usunie ona wszystkie zbudowane na podstawie docker-compose.yml obrazy oraz volumy























