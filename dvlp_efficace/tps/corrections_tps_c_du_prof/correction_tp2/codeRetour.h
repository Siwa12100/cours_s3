/**
   \file codeRetour.h
   \author C. SIMON
   \date 03/07/2022
   \brief gestion des codes de retour qui peuvent être retournés par les 
         primitives de gestion des réseaux
 */


#ifndef CODERETOUR_H
#define CODERETOUR_H


/**
 *  énumération de constantes pour gérer différents retour de fonctions 
 *     concernant les réseaux 
 */
typedef enum{
	     NON,
	     OUI,
	     OK,
	     PB_MEMOIRE,
	     PB_NOEUD_DEJA_EXISTANT,
	     PB_NOEUD_DEP_NON_EXISTANT,
	     PB_NOEUD_ARR_NON_EXISTANT,
	     PB_NOEUD_NON_EXISTANT,
	     PB_ARC_DEJA_EXISTANT,
	     PB_ARC_NON_EXISTANT,
	     PB_OUVERTURE_FICHIER,
	     PB_RESEAU_ERRONNE
} CodeRetour;


/**
   \brief gère l'affichage de chaque code de retour par un message 
               explicite à l'écran
   \param code le code à afficher
 */
void afficheMessageCodeRetour(CodeRetour code);

#endif // CODERETOUR_H