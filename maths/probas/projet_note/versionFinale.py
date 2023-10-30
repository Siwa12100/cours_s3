import random
import numpy as np
import matplotlib.pyplot as plt
from collections import Counter

# ============
# Exercice 1 :
# ============

# Q.1)
# ---
# Dans un jeu classique, il y a 28 Dominos. 

# Q.2)
# ---
# Il est possible que le jeu s'arrête sans avoir posé tous les dominos si aucun domino 
# restant ne correspond aux extrêmités disponibles dans la chaîne posée. 
# Le jeu ne peut plus progresser, alors la partie se termine. 


# Q.3)
# ---
# Il s'agit de variables aléatoires car elles dépendent du jeu, qui est lui même 
# dépendant d'évènements aléatoires, à savoir les valeurs qui contiendront les dominos 
# piochés à chaque fois. 
# A chaque partie, X et Y peuvent prendre des valeurs différentes, qu'il n'est pas 
# possible de prédire. 



# ============
# Exercice 2 :
# ============

# Fonction pour simuler une réalisation du jeu et renvoyer X et Y
def une_chaine_domino():

    pioche = [[i, j] for i in range(7) for j in range(i, 7)]
    chaine = []

    while pioche:
        domino = random.choice(pioche)
        pioche.remove(domino)

    X = len(chaine)
    Y = sum(sum(domino) for domino in pioche)

    return X, Y


X, Y = une_chaine_domino()

# print(f"X = {X}, Y = {Y}\n")


# ============
# Exercice 3 :
# ============

nBrealisations = 10_000
Valeurs_X = []
Valeurs_Y = []

for cpt in range(nBrealisations):
    X, Y = une_chaine_domino()
    Valeurs_X.append(X)
    Valeurs_Y.append(Y)

# Q.1)
# ---
plt.grid(axis='y', alpha=0.75)
plt.hist(Valeurs_X, bins=range(0, 30), density=True, alpha=0.75, color='blue')
plt.xlabel('X (Nb dominos posés)')
plt.ylabel('Proba')
plt.title('Distribution probas de X')
plt.show()

# Q.2)
# ---
ValeursTrieesDeX = np.sort(Valeurs_X)
Cumul = np.arange(1, len(ValeursTrieesDeX) + 1) / len(ValeursTrieesDeX)
plt.grid(axis='y', alpha=0.75)
plt.plot(ValeursTrieesDeX, Cumul, color='green')
plt.xlabel('X (Nb dominos posés)')
plt.ylabel('Proba Cumulative')
plt.title('Fct de répartition cumulative de X')
plt.show()

# Q.3)
# ---
EsperanceDeX = np.mean(Valeurs_X)
# print(f"Espérance de X : {EsperanceDeX}\n")

# Q.4)
# ---
VarianceDeX = np.var(Valeurs_X)
# print(f"Variance de X : {VarianceDeX}\n")

# Q.5)
# ---
plt.grid(axis='y', alpha=0.75)
plt.hist(Valeurs_Y, bins=range(0, 169), density=True, alpha=0.75, color='blue')
plt.xlabel('Y (Points toujours en pioche)')
plt.ylabel('Proba')
plt.title('Distribution de proba de Y')
plt.show()

ValeursTrieesDeY = np.sort(Valeurs_Y)
Cumul = np.arange(1, len(ValeursTrieesDeY) + 1) / len(ValeursTrieesDeY)
plt.grid(axis='y', alpha=0.75)
plt.plot(ValeursTrieesDeY, Cumul, color='green')
plt.xlabel('Y (Points toujours en pioche)')
plt.ylabel('Proba Cumulative')
plt.title('Fct de répartition cumulative de Y')
plt.show()

EsperanceDeY = np.mean(Valeurs_Y)
# print(f"Espérance de Y : {EsperanceDeY}")

VarianceDeY = np.var(Valeurs_Y)
print(f"Variance de Y : {VarianceDeY}\n")

# Q.6)
# ---
cpt = Counter(Valeurs_X)
chancesSucces = cpt[28] / len(Valeurs_X) * 100
#print(f"Probabilité de succes : {chancesSucces}%\n")

# Q.7)
# ----
NbMediansY = np.median(Valeurs_Y)
# print(f"Nombre médian : {NbMediansY}\n\n")


# ============
# Exercice 4 :
# ============

nBrealisations = 200
Valeurs_X = []
Valeurs_Y = []


# Q.1)
# ---
for cpt in range(nBrealisations):
    X, Y = une_chaine_domino()
    Valeurs_X.append(X)
    Valeurs_Y.append(Y)

# Nuage de points X par rapport à Y
plt.grid(alpha=0.5)
plt.scatter(Valeurs_X, Valeurs_Y, alpha=0.5)
plt.xlabel('X (Nb dominos posés)')
plt.ylabel('Y (Nb points restants dans la pioche)')
plt.title('Nuage de points X | Y')
plt.show()

# Q.2)
# ---
EsperanceDeX = np.mean(Valeurs_X)
EsperanceDeY = np.mean(Valeurs_Y)
EsperanceDeZ = np.mean(np.array(Valeurs_X) * np.array(Valeurs_Y))

# print(f"Espérance de X : {EsperanceDeX}")
# print(f"Espérance de Y : {EsperanceDeY}")
# print(f"Espérance de Z : {EsperanceDeZ}\n")

# Q.3)
# ---
CovXY = np.cov(Valeurs_X, Valeurs_Y)[0, 1]
CorrXY = np.corrcoef(Valeurs_X, Valeurs_Y)[0, 1]
print(f"Covariance entre X & Y : {CovXY}")
print(f"Coefficient de corrélation entre X & Y : {CorrXY}")


