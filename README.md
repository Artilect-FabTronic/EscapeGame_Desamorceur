# EscapeGame_Desamorceur Arduino

Jeu pour escape game "Le désamorceur" par Jean Roguin

Une minuterie allant de 999 à 0

Des fils apparents : la coupure de l’un d’eux arrête le mécanisme mais si l’on coupe le mauvais on peut soit accélérer le décompte soit passer directement à 0, soit…

Un « son » est émis à chaque décompte

Basé sur un Arduino, un afficheur 7 segments et quelques résistances


### Démonstration

![Maquette](/images/montage_du_jeu.jpg)

### Matériel

* 1 carte Arduino Uno
* 1 buzzer
* 1 afficheur 4 digits 7 segments (ici un TIL373, mais n'importe quel afficheur à cathode commune conviendra, [exemple](https://www.gotronic.fr/art-afficheur-7-segments-jaunes-4-digits-20371.htm))
* 2 dominos 4 contacts

### Dépendences

* [SevSeg Library](https://github.com/DeanIsMe/SevSeg)

### Remerciements

Merci à [Jean Roguin](mailto:) pour ce projet
