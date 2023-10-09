/**
   \file reseau.h
   \author C. SIMON
   \date 03/07/2022
   \brief un réseau informatique : la structure de donnée et ses primitives de 
     gestion. 
     Un réseau est une liste chaînée de noeuds. Chaque noeud représente un 
     ordinateur et connait la liste des orditeurs avec lesquells il est 
     connecté.
 */


#include "codeRetour.h"

#ifndef RESEAU_H
#define RESEAU_H

/**
   \brief structure de noeud. Un noeud représentera un ordinateur du 
   réseau. 
*/
typedef struct CellNoeud{
  int num; /**< numero identifiant l'ordinateur */
  int marque;  /**< marque permettant de savoir si le noeud a déjà été 
		  parcouru pendant le parcours en profondeur par exemple */
  struct CellNoeud *suiv; /**< adresse du noeud suivant dans la liste des noeuds*/
  struct CellArc *listeArc; /**< une liste d'arcs représentant la liste des 
			       ordinateurs avec lesquels il est connecté*/
}Noeud;

/**
   \brief la structure d'arc permet de représenter une connection vers un 
   ordinateur. Pour que les arcs puissent être chainés les uns aux autres, 
   chaque arc connait un suivant dans une telle liste.
 */
typedef struct CellArc{
  struct CellNoeud *extremite; /**< extrémité de l'arc*/
  struct CellArc *suivant; /**< arc suivant dans la liste d'arcs */
}Arc;

/**
   \brief structure de réseau : un réseau est une liste des noeuds qui le composent.
*/
typedef Noeud * Reseau;




/*------------------------------------------------------*/
/* primitives de gestion de réseau :                    */
/*------------------------------------------------------*/

/**
   \brief crée et initialise du réseau à vide 
*/
Reseau initialiser();

/**
   \brief vérifie si le réseau est vide
   \param r le réseau
   \return OUI si il est vide, NON sinon 
 */
CodeRetour estVide(Reseau r);

/**
   \brief affiche le réseau. 
   \param r le réseau à afficher
*/
void affiche(Reseau r);

/**
   \brief recherche dans le réseau le noeud correspondant au numero donné.  
   \param r le réseau 
   \param num le numéro que l'on cherche
   \return l'adresse du noeud si trouvé ou NULL sinon
*/
Noeud * rechercheNoeud(Reseau r, int num);


/**
   \brief ajoute un noeud donné par son numéro dans le réseau donné
   \param pr adresse du réseau à modifier
   \param num numéro du noeud à ajouter
   \return un code indiquant si l'opération a été faite ou pas 
   (et pour quelle raison):  
      - OK si l'ajout a été fait
      - PB_NOEUD_DEJA_EXISTANT si le noeud existe déjà (ajout non fait)
      - PB_MEMOIRE si problème allocation mémoire
*/
CodeRetour ajoutNoeud(Reseau *pr, int num);


/**
   \brief Fonction indiquant si une connexion/un arc entre les deux noeuds 
   donnés par leur numéro existe ou non.
   \param r le réseau
   \param dep le numéro du noeud de départ de l'arc
   \param arr le numéro du noeud d'arrivée de l'arc
   \return un code :
	    PB_NOEUD_DEP_NON_EXISTANT si le noeud de départ n'existe pas
	    PB_NOEUD_ARR_NON_EXISTANT si le noeud d'arrivée n'existe pas
	    NON si l'arc n'existe pas (les neouds extrémité existant)
            OUI s'il existe                                  
*/
CodeRetour existenceConnexion(Reseau r, int dep, int arr);


/**
   \brief ajoute un arc donné par ses extrémités dans le réseau.
   En cas de problème l'arc n'est pas ajouté.
   \param r le réseau
   \param dep le numéro du noeud de départ de l'arc
   \param arr le numéro du noeud d'arrivée de l'arc
   \return un code :
       OK si l'arc allant de dep à arr a bien été ajouté
       PB_NOEUD_DEP_NON_EXISTANT si dep n'existe pas
       PB_NOEUD_ARR_NON_EXISTANT si arr n'existe pas
       PB_ARC_DEJA_EXISTANT si l'arc existe déjà
       PB_MEMOIRE si problème allocation mémoire   
 */
CodeRetour ajoutArc(Reseau r, int dep, int arr);



/**
   \brief détruit un arc donné par les numéros de ses extrémités. 
   \param r le réseau
   \param dep le numéro du noeud de départ de l'arc à supprimer
   \param arr le numéro du noeud d'arrivée de l'arc à supprimer
   \return un code : 
       OK si destruction effectuée
       PB_NOEUD_DEP_NON_EXISTANT si dep n'existe pas
       PB_NOEUD_ARR_NON_EXISTANT si arr n'existe pas
       PB_ARC_NON_EXISTANT si l'arc n'existe pas  
*/
CodeRetour destructionArc(Reseau r, int dep, int arr);



/**
   \brief détruit un noeud(donné par son numéro) 
   dans un réseau donné. La destruction du noeud implique la 
   destruction des connections entrantes et sortantes de ce noeud
   \param pr l'adresse du réseau à modifier
   \param num le numéro du noeud à supprimer
   \return un code : 
            OK si destruction effectuée
            PB_NOEUD_NON_EXISTANT si numéro ne désigne pas un noeud du réseau
*/
CodeRetour destructionNoeud(Reseau *pr, int num);



/**
   \brief compte le nombre de noeuds d'un réseau.
   \param r le réseau
   \return le nombre de noeuds composant le réseau
*/
int compteNoeud(Reseau r);

/**
   \brief compte et le nombre de connexions/d'arcs d'un réseau donné. 
   \param r le réseau
   \return le nombre d'arcs composant le réseau
*/
int compteArc(Reseau r);


/*Fonction qui détruit le réseau passé en paramètre. */
void destructionReseau(Reseau *pr);



/**
   \brief détermine si une machine/noeud donnée peut communiquer avec 
           une autre également donnée.
   \param r le réseau
   \param dep le numéro de la machine de départ de la communication
   \param arr le numéro de la machine d'arrivée de la communication
   \return un code : 
            PB_NOEUD_DEP_NON_EXISTANT
	    PB_NOEUD_ARR_NON_EXISTANT
	    OUI si dep peut communiquer avec arr
	    NON si dep ne peut pas communiquer avec arr (dep et arr existent)
*/
CodeRetour peutCommuniquer(Reseau r, int dep, int arr);

/**
   \brief détermine et affiche l'ensemble des noeuds avec 
         lesquels un noeud donné peut communiquer
   \param r le réseau
   \param dep le numéro du noeud donné
*/
void afficheAvecQuiCommuniquer(Reseau r, int dep);


//   du plus : seulement si il reste du temps (ne tombera pas en exam

/*------------------------------------------------------*/
/* primitives de sauvegarde et de chargement            */
/*------------------------------------------------------*/
/**
   \brief charge le réseau en mémoire.
   En cas de problème le réseau reste vide.
   \param nomFichier le nom du fichier texte contenant le réseau
   \param pr l'adresse du réseau qui est chargé
   \return un code
       OK si chargement effectué
       PB_OUVERTURE_FICHIER si pb d'ouverture de fichier
       PB_RESEAU_ERRONNE si reseau erroné :
           noeud déjà existant, 
	   connexion entre deux noeuds non existants (un au moins), 
	   ou si connexion déjà existante
       PB_MEMOIRE si problème allocation mémoire
*/
CodeRetour chargement(char * nomFichier, Reseau * pr);


/**
   \brief sauvegarde le réseau dans un fichier texte.
   \param nomFichier le nom du fichier texte
   \param r le réseau à sauvegarder
   \return un code
            OK si sauvegarde effectuée
            PB_OUVERTURE_FICHIER si pb ouverture fichier
*/
CodeRetour sauvegarde(char * nomFichier, Reseau r);


/**
   \brief exporte le réseau dans un fichier dot 
   \param nomFichier le nom du fichier texte de format dot
   \param r le réseau à exporter
   \return un code
            OK si export effectué
            PB_OUVERTURE_FICHIER si pb ouverture fichier
*/
CodeRetour exporte(char * nomFichier, Reseau r);

#endif // RESEAU_H
