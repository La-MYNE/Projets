//Ici on définit les constantes, ce sont des valeurs qui restent fixes tout le temps.

#define POMPE  <nombre ?> //Sur quel sortie de l'Arduino allons nous brancher le fil pour actionner la pompe ? 
#define SEUIL_DE_SECHERESSE <nombre ?> //Trouver à quel seuil il faudra arroser.
#define CAPTEUR <nombre ?> //Quelle est le pin sur lequel on va brancher le capteur d'hygrométrie

//Cette partie sert à démarrer la carte il faut la laisser telle qu'elle est. //

void setup() {
  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
  pinMode(POMPE,OUTPUT);
}


// Cette partie est le programme. On va mettre les instructions dont on a besoin pour surveiller l'humidité de la terre et s'il n'y a pas assez d'eau, arroser la plante //

void loop() {
  
  int secheresse;  //déclaration de la variable secheresse
  secheresse = analogRead(CAPTEUR); //On lit la valeur du capteur d'humidité
  Serial.print(secheresse); //on envoie la valeur
  Serial.print("\n"); // On fait un retour à la ligne


  if (secheresse > SEUIL_DE_SECHERESSE)
  {
    //quelle fonction va-t-on utiliser ?
  }
  delay(10000); //On attend jusqu'à la nouvelle mesure

}

// Définition des fonctions 

void arroser(int temps){
  digitalWrite(POMPE,LOW);
  delay(temps);
  digitalWrite(POMPE,HIGH);
  }

