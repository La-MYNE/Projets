//Ici on définit les constantes, ce sont des valeurs qui restent fixes tout le temps.

#define CAPTEUR ??? //Quelle est le pin sur lequel on va brancher le capteur de lumière ? 
#define LUMIERE ??? //Sur quel sortie de l'Arduino allons nous brancher le fil pour allumer la lumière ? 

#define SEUIL_DE_LUMIERE 500 //On peut modifier ce chiffre pour changer à quel moment s'allume la lumière


//Cette partie sert à démarrer la carte il faut la laisser telle qu'elle est. //

void setup() {
  Serial.begin(9600); // Ouverture de la communication série, taux 9600 bps
  pinMode(CAPTEUR, INPUT);
  pinMode(LUMIERE, OUTPUT);
}

// Cette partie est le programme. On va mettre les instructions dont on a besoin pour surveiller la luminosité et allumer la lumière si besoin //

void loop() {
  int lum = analogRead(CAPTEUR); //Lecture du capteur, on met la valeur dans la variable lum
  Serial.print(lum); //on envoie la valeur à l'ordinateur pour la lire
  Serial.print("\n"); //Retour à la ligne
  if(??? < SEUIL_DE_LUMIERE) //Comment écrire la condition "Si la lumière est inférieur au seuil...."
  {
    digitalWrite(LUMIERE, LOW); //...on l'allume
  }
  else{digitalWrite(LUMIERE, ???);} // Et sinon on l'éteint, on doit donc changer l'état de l'interrupteur par ??? 
  delay(30); // On attend quelques millisecondes avant la mesure suivante
}
