#ifndef RESEAU_H
#define RESEAU_H
#include "codeRetour.h"


/**
 * \file abr.h
 * \brief Header contenant les structures et les prototypes de fonctions pour la gestion d'un réseau.
 * \author Votre Nom
 * \date Date de création
 *
 * Ce fichier contient les définitions des structures et les prototypes des fonctions
 * nécessaires à la gestion d'un réseau, y compris la création de réseau, la recherche d'ordinateurs,
 * la gestion des connexions, etc.
 */

typedef struct CellSommet{
    int id; /**< ID de l'ordinateur. */
    struct CellSommet * suiv; /**< Pointeur vers l'ordinateur suivant dans le réseau. */
    struct CellArc * listeConnexions; /**< Liste des connexions de cet ordinateur. */
} Ordi;

typedef struct CellArc{
    Ordi * extremite; /**< Pointeur vers l'ordinateur d'extrémité de la connexion. */
    struct CellArc * suivant; /**< Pointeur vers la connexion suivante. */
} Connexion;

/**
 * \enum Booleen
 * \brief Énumération représentant des valeurs booléennes.
 */
typedef enum booleen {
    FAUX, /**< Valeur représentant faux. */
    VRAI /**< Valeur représentant vrai. */
} Booleen;

/**
 * \typedef Reseau
 * \brief Type de données représentant un réseau.
 */
typedef Ordi * Reseau;

/**
 * \brief Crée un réseau vide.
 * \return Un pointeur vers le réseau vide (NULL).
 */
Reseau creerReseauVide();

/**
 * \brief Vérifie si un réseau est vide ou non.
 * \param r Le réseau à vérifier.
 * \return VRAI si le réseau est vide, FAUX sinon.
 */
Booleen estReseauVide(Reseau r);

/**
 * \brief Affiche les détails du réseau, y compris les ordinateurs et les connexions.
 * \param r Le réseau à afficher.
 */
void affichageReseau(Reseau r);

/**
 * \brief Recherche un ordinateur dans le réseau par son ID.
 * \param r Le réseau dans lequel rechercher.
 * \param id L'ID de l'ordinateur à rechercher.
 * \return Un pointeur vers l'ordinateur trouvé, sinon NULL s'il n'est pas trouvé.
 */
Ordi * rechercherOrdiPt(Reseau r, int id);

/**
 * \brief Ajoute un nouvel ordinateur au réseau.
 * \param r Un pointeur vers le réseau.
 * \param id L'ID de l'ordinateur à ajouter.
 * \return Un code de retour indiquant le résultat de l'opération.
 */
CodeRetour ajouterOrdi(Reseau * r, int id);

/**
 * \brief Recherche une connexion entre deux ordinateurs par leurs IDs.
 * \param r Le réseau dans lequel rechercher la connexion.
 * \param dep L'ID de l'ordinateur de départ.
 * \param arr L'ID de l'ordinateur d'arrivée.
 * \return Un code de retour indiquant le résultat de la recherche.
 */
CodeRetour rechercherConnexion(Reseau r, int dep, int arr);

/**
 * \brief Ajoute une connexion entre deux ordinateurs au réseau.
 * \param ptr Un pointeur vers le réseau.
 * \param idDep L'ID de l'ordinateur de départ.
 * \param idArr L'ID de l'ordinateur d'arrivée.
 * \return Un code de retour indiquant le résultat de l'opération.
 */
CodeRetour ajouterConnexion(Reseau * ptr, int idDep, int idArr);




// ===================

CodeRetour destructionConnexion(Reseau * ptr, int idDep, int idArr);

#endif
