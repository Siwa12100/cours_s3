# ============
# Exercice 1 :
# ============

# 1.) 
# Dans un jeu classique, il y a 28 Dominos. 

# 2.) 
# Il est possible que le jeu s'arrête sans avoir posé tous les dominos si
# aucun domino restant ne correspond aux extrêmités disponibles dans la chaîne posée. 
# Le jeu ne peut plus progresser, alors la partie se termine. 

# 3.)
# Il s'agit de variables aléatoires car elles dépendent du jeu, qui est lui même 
# dépendant d'évènements aléatoires, à savoir les valeurs qui contiendront les dominos 
# piochés à chaque fois. 
# A chaque partie, X et Y peuvent prendre des valeurs différentes, qu'il n'est pas 
# possible de prédire. 



# ============
# Exercice 2 :
# ============

import random

# Création d'un jeu de dominos, avec toutes les possibilités de mélanges entre 0 et 6 
# sans doublons. 
dominosOrdonnes = [(i, j) for i in range(7) for j in range(i, 7)]
# print(dominosOrdonnes)

# On créé un doublon du paquet de dominos pour pouvoir le mélanger 
dominosMelanges = dominosOrdonnes
# On mélange de manière aléatoire la nouvelle version du jeu
random.shuffle(dominosMelanges)
# print(dominosMelanges)

# On essaye de compter le nombre de dominos dans un jeu...
# Y va récupérer le nombre de points total dans le jeu de dominos 
y = 0
# On parcours le tableau et pour chaque ligne, on additionne la première et la deuxième valeur 
# avec la somme des valeurs précédentes, jusqu'à finir l'ensemble du jeu de dominos
for d in dominosOrdonnes : 
    y = y + d[0] + d[1]
# print(y)

# Fonction qui renvoie le nombre de points total dans un jeu de dominos donné en param. 
def compterNombrePoints(ListeDominos) :
    cpt = 0

    for d in ListeDominos :
        cpt = cpt + d[0]  + d[1]
    
    return cpt

# On vérifie qu'on trouve bien 168 (= le nombre total de pts dans un jeu de 28 pièces)
tmp1 = compterNombrePoints(dominosOrdonnes)
# print("La valeur de cpt avec le jeu en entier est de : ", tmp1)


# Cette fonction va comparer les valeurs entre les 2 bouts du domino, et les 2 extrêmités de la chaîne
# de domino. 
# Si aucune correspondance entre les valeurs n'existent, la fonction renvoie le code -1 
# Si une seule correspondance existe, la fonction renvoie une liste de deux valeurs, la position de la valeur 
# correspondante entre les 2 du domino, et la position de la valeur correspondance entre les 2 extrémités. 
# Si plusieurs correspondances existent, alors la fonction renvoie au hasard l'une des correspondances possible   
def MapDominos(d, extremites) :
    # On va stocker dans correspondances les paires [position du domino, position dans les extrémités]
    # où les valeurs sont égales 
    correspondances = []
    # On va aussi compter le nombre de correspondances 
    i = 0
    # Si la premiere valeur du dé est égale à la première extremité 
    if (d[0] == extremites[0]) : 
        correspondances[i] = [0,0]
        i = i + 1

    # Si la premiere valeur du dé est égale à la seconde extremité 
    if (d[0] == extremites[1]) :
        correspondances[i] = [0,1]
        i = i + 1

    # Si la seconde valeur du dé est égale à la première extremité 
    if (d[1] == extremites[0]) :
        correspondances[i] = [1,0]
        i = i + 1

    # Si la seconde valeur du dé est égale à la seconde extremité 
    if (d[1] ==  extremites[1]) :
        correspondances[i] = [1,1]
    # Si la premiere valeur du dé est égale à la première extremité 
    if (i == 0) return -1
    if (i == 1) return correspondances[0]
    return random.choice(correspondances)

    

x = 0
dominosOrdonnes1 = [(i, j) for i in range(7) for j in range(i, 7)]
total_pts = compterNombrePoints(dominosOrdonnes)
y = total_pts
dominos_poses = [0,0]
#print("initialisation des dominos posés : ", dominos_poses)
# print(dominosMelanges[0])
# print((dominosMelanges[0])[0], (dominosMelanges[0])[1])
dominosMelanges1 = dominosOrdonnes1
random.shuffle(dominosMelanges1)

dominos_poses[0] = dominosMelanges1[0][0]
dominos_poses[1] = dominosMelanges1[0][1]
#print(dominos_poses)

for d in dominosMelanges1 :
    












