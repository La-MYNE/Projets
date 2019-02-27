//Ici on définit les constantes, ce sont des valeurs qui restent fixes tout le temps.


#define CAPTEUR A1
#define LUMIERE 3

#define SEUIL_DE_LUMIERE 180


//Cette partie sert à démarrer la carte il faut la laisser telle qu'elle est. //

void setup() {
  Serial.begin(9600); // Ouverture de la communication série, taux 9600 bps
  pinMode(CAPTEUR, INPUT);
  pinMode(LUMIERE, OUTPUT);
}

// Cette partie est le programme. On va mettre les instructions dont on a besoin pour surveiller l'humidité de la terre et s'il n'y a pas assez d'eau, arroser la plante //

void loop() {
  int lum = analogRead(CAPTEUR); //Lecture du capteur, on met la valeur dans la variable lum
  Serial.print(lum); //on envoie la valeur à l'ordinateur pour la lire
  Serial.print("\n"); //Retour à la ligne
  if(lum < SEUIL_DE_LUMIERE) //Si la lumière est inférieur au seuil....
  {
    digitalWrite(LUMIERE, LOW); //...on l'allume
  }
  else{digitalWrite(LUMIERE, HIGH);}
  delay(30); // On attend quelques millisecondes avant la mesure suivante
}
