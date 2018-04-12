
Komendy

docker images - obrazy dockerowe
docker ps - uruchomione kontenery
docker ps -a - wszytskie kontenery

docker run [image_name] - tworzy kontener z obrazu i uruchamia
docker run -p 80:80 [image_name] - to samo co wyżej z tym że mapuje port z locala na port dockerowy

docker-machine env default ?
docker-machine ls
docker-machine status
docker-machine start
docker-machine stop


docker rmi - usuwa obraz dockerowy (remove images)

---

Tworzenie Data Volume

docker run -p 8080:3000 -v $(pwd):/var/www node 

-v - tworzy volume,
$(pwd):/var/www - host location - nasz obezny folder w którym sie znajdujemy mapujemy do folder /var/www w kontenerze,
node - to nazwa obrazu dokerowego


docker inspect [container_id/name] - pokazuje jak mapowany jest volume

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

!!!
Odpalenie dokera wraz z wystarowaniem node

docker run -p 8080:3000 -v $(pwd):/var/www -w"/var/www" node npm start

-w"/var/www" - wskazuje w jakim folderze mamy sie znajdowac na kontenerze, chodzi o to że jeśli nie wskazalibyśmy -w"/var/www" a uruchomilibyśmy "npm start" to komenda ta odpaliła by się w innym folderze niż oczekujemy

---

Budowanie własnego obrazu dokerowego

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
docker build -t <your username>/node .
```

Kropka na końcu wskazuje kontekst wywołania - więc np. miejsce w którym docker będzie szukał Dockerfile'a

