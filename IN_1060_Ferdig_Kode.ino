/*
  Når det refereres til forskjellige lunger, vil det si at hver lunge i prototypen
  har en egen breadboard med 5 lamper og 2 sensorer hver.
  De to lungene handler uavhengig av hverandre og kodes derfor hver for seg

  Prototypen skal fungere slik: bruker skal røyke på lungene, og sensorene
  skal lese karbonmonoksid verdiene, og om det bikker en terskel skal 
  lysene i den lungen skru av stegvis for å visualisere at lungene dør

  (terskelen er en terskel vi prøvde oss frem med for å finne hvilken verdi 
  som ikke er så høy at man må røyke masse for at prototypen skal reagere, men 
  ikke så lav at prototypen reagerer uten interaksjon. Vi testet med sigarettrøyk 
  hva terskelen måtte være for at den plukket opp ett pust med røyk på lungene.)
*/

//Initialiserer globale variabler som vil kunne bli brukt av alle funksjonene

int antLED = 5;
int antLED2 = 5;

//Lage 2 array med de pins som blir brukt til lampene
int alleLED[] = { 3, 4, 5, 6, 7 }; //lampene i lunge 1
int alleLED2[] = { 8, 9, 10, 11, 12 }; //lampene i lunge 2

//sjekkverdier
int chk = 0;
int chk2 = 0;

int check = 0;
int check2 = 0;

//initaliserer led lampene som blir brukt og starter serial monitor til å skrive ut
void setup() {

  //går igjennom og lager liste av pins til hver LEDlampe i lunge 1
  for (int n = 0; n < antLED; n++) {

    pinMode(alleLED[n], OUTPUT);
  }

  //går igjennom og lager liste av pins til hver LEDlampe i lunge 2
  for (int y = 0; y < antLED2; y++) {

    pinMode(alleLED2[y], OUTPUT);
  }

  // gjør klart til å skrive ut i Serial monitor
  Serial.begin(9600);
}

void loop() {
  // kjører så lenge prototypen er koblet til
  // leser hver lunge for å sjekke om karbonmonoksid-verdien bikker en terskel

  ReadLunge1(); //sender til Lunge1LED som styrer lysene i lunge 1
  ReadLunge2(); //sender til Lunge1LED som styrer lysene i lunge 2
}


// shuffle tilfeldig rekkefølge i lunge 1 lampene, for at de skal skrus av/på i tifleldig rekkefølge
void Shuffle1() {

  for (int a = 0; a < antLED; a++) {

    int rand = random(a, 4);

    int temp = alleLED[a];

    alleLED[a] = alleLED[rand];

    alleLED[rand] = temp;
  }
}


// shuffle tilfeldig rekkefølge i lunge 2 lampene  for at de skal skrus av/på i tifleldig rekkefølge
void Shuffle2() {

  for (int b = 0; b < antLED; b++) {

    int rand = random(b, 4);

    int temp = alleLED2[b];

    alleLED2[b] = alleLED2[rand];

    alleLED2[rand] = temp;
  }
}

/*
  Funksjon som leser sensor verdier og sender til funksjon som styrer LEDlamper i samme lunge
  Funksjonen vil også printe ut hvor mye karbonmonoksid som leses
  i de 2 sensorene som er i lunge 1 til Serial monitoren så vi kan lese
*/
void ReadLunge1() {

  //leser dataen (karbononoksid-verdiene) og deretter lagrer det i variabler car0 og car1
  int car0 = analogRead(A2);
  int car1 = analogRead(A3);

  /*If statement som vil sjekke om begge sensorene leser verdier under en terskel
    koden vil da sette check til 1 som sier at så lenge LEDlampene allerede er på vil den ikke gå i denne kodesnutten
    Den vil også sette en annen variabel "chk" som vil gjøre det mulig å gå i en annen if statement senere i programmet
    Derretter er det en for løkke som vil skru på alle LEDlampene (om de ikke allerede er på)
  */

  if((car0 < 20 && car1 < 46) && check != 1) {
    check = 1;
    chk = 0;
    for (int i = 0; i < antLED; i++) {
      digitalWrite(alleLED[i], HIGH);
      delay(250);  //Delay for 0.25 sec.
    }
  }

  //Bruk av funksjonene Shuffle1 for å bytte verdier til arrayet alleLED, altså gi listen tilfeldig rekkefølge
  Shuffle1();

  //Printer Karbonmonoksid verdier til Serial monitoren
  Serial.println("Første lunge");

  Serial.print("Carbon Monoxide (3 sensor): ");

  Serial.println(car0);

  Serial.print("Carbon Monoxide (4 sensor): ");

  Serial.println(car1);

  delay(300);  //Delay for 0.3 sec før verdiene leses igjen


  //Kaller på funksjonen som styrer lys i lunge 1
  Lunge1LED();
}


/*Funksjonen vil sjekke om karbonmonoksid-verdiene i en av de 2 sensorene 
  som er på samme breadboardet (altså i samme lunge) er over en viss terskel
  Hvis terskelen er nådd vil alle LED'er på den breadboardet skru seg av gradvis og stegvis
  Hvis ikke vil lysene forbli på
*/
void Lunge1LED() {

  //Bruk av Shuffle funksjonen for å bytte verdier til arrayet, og gi lampene tilfeldig rekkefølge for å skrus av/på
  Shuffle1();

  /*If statement som sjekker hvis en av de 2 sensorene er over et viss terskel
        Hvis ja, Setter "chk til 1" slik at programmet ikke går inn i if statement for å unngå unødvendig venting
        Setter "check til 0" til å gjøre det mulig for LED'er å skru seg på igjen etter at denne koden er feridg
      */

  if((car0 < 20 && car1 < 46) && chk != 1) {
    chk = 1;
    check = 0;
    for (int i = 0; i < antLED; i++) {

      //Dette får lyset til å falme sakte ved å sette lysstyrken lavere og lavere

      analogWrite(alleLED[i], 270);

      delay(100);  //Delay for 0.1 sec. //mellomrom mellom hver nedstigning i lysstyrke

      analogWrite(alleLED[i], 180);

      delay(100);  //Delay for 0.1 sec.

      analogWrite(alleLED[i], 90);

      delay(100);  //Delay for 0.1 sec.

      analogWrite(alleLED[i], 45);

      delay(100);  //Delay for 0.1 sec.

      analogWrite(alleLED[i], 0);

      delay(450);  //Delay for 0.45 sec.
    }
  }

  //Bytter på verdi rekkefølgjen av LED-arrayet i lunge 1
  Shuffle1();
}


/* Fra dette tidspunktet vil koden gjøre det samme som i funksjonene ReadLunge1 og Lunge1LED
  bare for lunge 2.
  Eneste som blir forskjellig er terskelen for at LED'er skal skru seg på og av blir høyere eller lavere fordi
  terskelen i sensorene måtte tilpasses hver enkelte sensor,og at noen variabelnavn endres

  Altså tidligere kode er for Lunge 1, og kommende kode er for Lunge 2.
  */



/*
  Funksjon som leser sensor verdier og sender til funksjon som styrer LEDlamper i samme lunge
  Funksjonen vil også printe ut hvor mye karbonmonoksid som leses
  i de 2 sensorene som er i lunge 2 til Serial monitoren så vi kan lese
*/
void ReadLunge2() {

  //leser dataen og deretter lagrer den i variabler car2 og car3
  int car2 = analogRead(A0);
  int car3 = analogRead(A1);

  /*If statement som vil sjekke om begge sensorene leser verdier under en terskel
    koden vil da sette check til 1 som sier at så lenge LEDlampene allerede er på vil den ikke gå i denne kodesnutten
    Den vil også sette en annen variabel "chk" som vil gjøre det mulig å gå i en annen if statement senere i programmet
    Derretter er det en for løkke som vil skru på alle LEDlampene (om de ikke allerede er på)
  */

  if((car2 < 15 && car3 < 129) && check2 != 1) {
    check2 = 1;
    chk2 = 0;
    for (int i = 0; i < antLED2; i++) {
      digitalWrite(alleLED2[i], HIGH);
      delay(250);  //Delay for 0.25 sec.
    }
  }

  //Bruk av funksjonene Shuffle2 for å bytte rekkefølgen av verdier i arrayet alleLED2
  Shuffle2();

  //Printer Karbonmonoksid verdier til Serial monitoren
  Serial.println("Andre lunge");

  Serial.print("Carbon Monoxide (1 sensor): ");

  Serial.println(car2);

  Serial.print("Carbon Monoxide (2 sensor)");

  Serial.println(car3);

  delay(300);  //Delay for 0.3 sec. før det leses og printes igjen


  //Kaller på funksjonen som styrer lys i lunge 2
  Lunge2LED();
}


/*Funksjonen vil sjekke om karbonmonoksid-verdiene i en av de 2 sensorene 
  som er på samme breadboardet (altså i samme lunge) er over en viss terskel
  Hvis terskelen er nådd vil alle LED'er på den breadboardet skru seg av gradvis og stegvis
  Hvis ikke vil lysene forbli på
*/
void Lunge2LED() {

  //Bruk av Shuffle funksjonen for å bytte verdier til arrayet
  Shuffle2();

  /*If statement som sjekker hvis en av de 2 sensorene er over et viss terskel
        Hvis ja, Setter "chk til 1" slik at programmet ikke går inn i if statement for å unngå unødvendig venting
        Setter "check til 0" til å gjøre det mulig for LED'er å skru seg på igjen etter at denne koden er feridg
      */

  if((car2 < 15 && car3 < 129) && check2 != 1) {

    chk2 = 1;
    check2 = 0;

    for (int i = 0; i < antLED2; i++) {

      //Dette får lyset til å falme sakte ved å sette lysstyrken lavere og lavere
      analogWrite(alleLED[i], 270);

      delay(100);  //Delay for 0.1 sec. mellomrom mellom hver nedstigning i lysstyrke

      analogWrite(alleLED[i], 180);

      delay(100);  //Delay for 0.1 sec.

      analogWrite(alleLED2[i], 90);

      delay(100);  //Delay for 0.1 sec.

      analogWrite(alleLED2[i], 45);

      delay(100);  //Delay for 0.1 sec.

      analogWrite(alleLED2[i], 0);

      delay(450);  //Delay for 0.45 sec.
    }
  }

  //Bytter på verdi rekkefølgjen av arrayet
  Shuffle2();
}
