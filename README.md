# ese_td_adxl345
TD ESE écriture de driver pour l'ADXL345

## Démarrage
1. Téléchargez le projet https://github.com/lfiack/ese_td_adxl345.
2. Importez le projet, compilez et programmez la carte.
3. Listez les problèmes et les améliorations possibles.

## Scénario d'utilisation du driver
L'objectif est d'écrire un driver permettant de :

* Configurer la fréquence de mesure du capteur et la range
* Démarrer et arrêter la mesure
* Réagir aux interruptions
* Indiquer si une mesure est terminée
* Renvoyer l'accélération sur les axes x, y et z en **float**

L'application d'exemple devra réaliser une moyenne et afficher le résultat 10 fois par seconde.
1. Écrire le squelette de la fonction **main()** permettant de récupérer les valeurs et de les afficher.
La fonction permettant de réaliser la moyenne et de faire l'affichage est déjà écrite, son prototype est le suivant :
```c
void process_acceleration(float acc_x, float acc_y, float acc_z);
```
2. Quels sont les éléments à rajouter à la structure **h_adxl345_t**?

## Écriture du driver
1. Quelles valeurs peuvent prendre les paramètres **Rate** et **Range**?
2. Ouvrez les fichiers **drv_adxl345.c** et **drv_adxl345.h**
3. Comment sont codés les paramètres **Rate** et **Range**?
4. Complétez la structure.
5. Écrivez le contenu des fonctions dans le fichier **drv_adxl345.c**.

## Utilisation du driver
1. Dans **main.c**, ajoutez et écrivez le code des fonctions suivantes:
```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
int spi_transmit(uint8_t address, uint8_t *p_data, uint16_t size);
int spi_receive(uint8_t address, uint8_t *p_data, uint16_t size);
```
2. Réécrivez le **main()** en vous inspirant du squelette écrit précédemment.
