//Initialiserer globale variabler som vil kunne bli brukt av alle funksjonene

int antLED = 5;
int antLED2 = 5;

//Lage 2 array med de pins som blir brukt
//En array er for en breadboard og den andre array er for en anna breadboard
int alleLED[] = { 3, 4, 5, 6, 7 };
int alleLED2[] = { 8, 9, 10, 11, 12 };

int chk = 0;
int chk2 = 0;

int check = 0;
int check2 = 0;

void setup() {

  /* Lager en for-loop for å intialisere alle LED'er som blir brukt på første breadboardet
     Det samme med andre for-loopen men med LED'er til den andre breadboardet
  */
  for (int n = 0; n < antLED; n++) {

    pinMode(alleLED[n], OUTPUT);
  }

  for (int y = 0; y < antLED2; y++) {

    pinMode(alleLED2[y], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  Carbon();
  Carbon2();
}

//Funksjonen for å bytte rekkefølgen av LED'er i arrayet alleLED
void Shuffle() {

  for (int a = 0; a < antLED; a++) {

    int rand = random(a, 4);

    int temp = alleLED[a];

    alleLED[a] = alleLED[rand];

    alleLED[rand] = temp;
  }
}
//Funksjonen for å bytte rekkefølgen av LED'er i arrayet alleLED2
void Shuffle_2() {

  for (int b = 0; b < antLED; b++) {

    int rand = random(b, 4);

    int temp = alleLED2[b];

    alleLED2[b] = alleLED2[rand];

    alleLED2[rand] = temp;
  }
}

/*
  Funksjon som vil skru på LED'er når terskelen er over en viss verdi
  Funksjonen vil også printe ut til hvor mye karbonmonoksid
  er i de 2 sensorene som er på første breadbordet til Serial monitoren
*/
void Carbon() {

  //leser dataen og deretter lagrer den i variabler car0 og car1
  int car0 = analogRead(A2);
  int car1 = analogRead(A3);

  /*If statement som vi sjekke hvis begge sensorers karbondioxid er under en terksel
    Den vil då sette check til 1 slik at så lenge LED'er er på vil den ikke gå i denne if statement
    Den vil også sette en anna variabel "chk" som vil då gjøre det mulig å gå i en anna if statement senere i programmen
    Dermed er det en for-loop som vil skru på alle LED'er
  */
  if ((car0 < 130 && car1 < 130) && check != 1) {
    check = 1;
    chk = 0;
    for (int i = 0; i < antLED; i++) {
      digitalWrite(alleLED[i], HIGH);
      delay(250);  //Delay for 0.25 sec.
    }
  }
  //Bruk av funksjonene Shuffle for å bytte verdier til arrayet alleLED
  Shuffle();

  //Printer Karbonmonoksid verdier til Serial monitoren
  Serial.println("Første lunge");

  Serial.print("Carbon Monoxide (3 sensor): ");

  Serial.println(car0);

  Serial.print("Carbon Monoxide (4 sensor): ");

  Serial.println(car1);

  delay(300);  //Delay for 0.3 sec.


  //Kaller på funksjonen CarLED
  CarLED();
}
/*Funksjonen vil sjekke hvis karbonmonoksid til en av de 2 sensorene 
  som er på samme breadboardet er over et viss terskel
  Hvis den er vil alle LED'er på den breadboardet skru seg av
*/
void CarLED() {

  //Bruk av Shuffle funksjonen for å bytte verdier til arrayet
  Shuffle();

  /*If statement som sjekker hvis en av de 2 sensorene er over et viss terskel
        Hvis ja, Setter "chk til 1" slik at programmet går ikke inn i if statement for å unngå unødvendig venting
        Setter "check til 0" til å gjøre det mulig for LED'er å skru seg på igjen etter at denne koden er feridg
      */
  if ((car0 > 130 || car1 > 130) && chk != 1) {
    chk = 1;
    check = 0;
    for (int i = 0; i < antLED; i++) {

      //Dette får lyset til å falme saktig ved å sette styrken til lyset lavare og lavare

      analogWrite(alleLED[i], 270);

      delay(100);  //Delay for 0.1 sec.

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

  //Bytter på verdi rekkefølgjen av arrayet
  Shuffle();
}

/* Fra dette tidspunkten vil koden være den samme som i funksjonene Carbon og CarLED
  Eneste som blir forskjellig er terskelen for at LED'er skal skru seg på og av blir høyere eller lavare
  I tillegg til at print setninga sier andre lungen istedenfor første lungen
  og at variabel navn og navn til funksjoner blir forandret 
  */

/*
  Funksjon som vil skru på LED'er når terskelen er over en viss verdi
  Funksjonen vil også printe ut til hvor mye karbonmonoksid
  er i de 2 sensorene som er på første breadbordet til Serial monitoren
*/
void Carbon2() {

  //leser dataen og deretter lagrer den i variabler car2 og car3
  int car2 = analogRead(A0);
  int car3 = analogRead(A1);

  /*If statement som vi sjekke hvis begge sensorers karbondioxid er under en terksel
    Den vil då sette check2 til 1 slik at så lenge LED'er er på vil den ikke gå i denne if statement
    Den vil også sette en anna variabel, chk2 til 0, 
    som vil då gjøre det mulig å gå i en anna if statement senere i programmen
    etter at verdien til begge snesorer er under en terksel
    Dermed er det en for-loop som vil skru på alle LED'er
  */
  if ((car2 < 140 || car3 < 210) && check2 != 1) {
    check2 = 1;
    chk2 = 0;
    for (int i = 0; i < antLED2; i++) {
      digitalWrite(alleLED2[i], HIGH);
      delay(250);  //Delay for 0.25 sec.
    }
  }

  //Bruk av funksjonene Shuffle_2 for å bytte rekkefølgjen av verdier i arrayet alleLED2
  Shuffle_2();

  //Printer Karbonmonoksid verdier til Serial monitoren
  Serial.println("Andre lunge");

  Serial.print("Carbon Monoxide (1 sensor): ");

  Serial.println(car2);

  Serial.print("Carbon Monoxide (2 sensor)");

  Serial.println(car3);

  delay(300);  //Delay for 0.3 sec.


  //Kaller på funksjonen CarLED2
  CarLED2();
}

/*Funksjonen vil sjekke hvis karbonmonoksid til en av de 2 sensorene 
  som er på samme breadboardet er over et viss terskel
  Hvis den er vil alle LED'er på den breadboardet skru seg av
*/
void CarLED2() {

  //Bruk av Shuffle funksjonen for å bytte verdier til arrayet
  Shuffle_2();

  /*If statement som sjekker hvis verdien til en av de to sensorer overskrides
        Hvis ja, Setter "chk2 til 1" slik at programmet går ikke inn i if statement for å unngå unødvendig venting
        Setter "check2 til 0" til å gjøre det mulig for LED'er å skru seg på igjen etter at denne koden er feridg
      */
  if ((car2 > 140 || car3 > 210) && chk2 != 1) {

    chk2 = 1;
    check2 = 0;

    for (int i = 0; i < antLED2; i++) {

      //Dette får lyset til å falme saktig ved å sette styrken til lyset lavare og lavare
      analogWrite(alleLED[i], 270);

      delay(100);  //Delay for 0.1 sec.

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
  Shuffle_2();
}
