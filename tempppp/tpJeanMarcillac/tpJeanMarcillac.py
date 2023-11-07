import random
import numpy as np
import matplotlib.pyplot as plt
from collections import Counter

# ============
# Exercice 1 :
# ============

# cf. réponses sur rapport.


# ============
# Exercice 2 :
# ============

def initialisation(pioche, chaine):
    val=0

    for i in range(7):
        while(val!=7):
            pioche.append([i, val])
            val+=1
        val=i+1
    
    random.shuffle(pioche)
    domino = pioche[0]
    #domino = pioche.pop(0)
    chaine.append(domino)


def VerifPoser(domino, chaine, pioche):

    if(domino[0] == chaine[0][0] or domino[0] == chaine[-1][-1] or domino[1] == chaine[0][0] or domino[1] == chaine[-1][-1]):

        if(domino[0] == chaine[-1][-1] or domino[1] == chaine[-1][-1]):
            if(domino[0] == chaine[-1][-1]):
                chaine.append(domino)
            else:
                domino.reverse()
                chaine.append(domino)

        else:
            if(domino[1] == chaine[0][0]):
                chaine.insert(0, domino)
            else:
                domino.reverse()
                chaine.insert(0,domino)
        return True

    else:
        pioche.append(domino)
    return False


def DominosRestants(pioche, chaine):
    cpt=0

    for element in pioche:
        if(element[0] == chaine[0][0] or element[0] == chaine[-1][-1] or
            element[1] == chaine[0][0] or element[1] == chaine[-1][-1]):
            cpt += 1

    if(cpt == 0):
        return False

    else:
        return True


def une_chaine_domino():

    chaine=[]
    pioche = []

    initialisation(pioche, chaine)

    while(pioche):
        random.shuffle(pioche)
        domino = pioche.pop(0)

        if (VerifPoser(domino, chaine, pioche)):
            continue
        else:
            if not (DominosRestants(pioche, chaine)):
                break

    X = len(chaine)
    Y = sum(sum(domino) for domino in pioche)

    return X,Y

#print(une_chaine_domino())


# ============
# Exercice 3 :
# ============

print("exo 3 ")
nBrealisations = 10000
Valeurs_X = []
Valeurs_Y = []

for cpt in range(nBrealisations):
    #print(cpt)
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
print(f"Espérance de X : {EsperanceDeX}\n")

# Q.4)
# ---
VarianceDeX = np.var(Valeurs_X)
print(f"Variance de X : {VarianceDeX}\n")

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
print(f"Espérance de Y : {EsperanceDeY}")

VarianceDeY = np.var(Valeurs_Y)
print(f"Variance de Y : {VarianceDeY}\n")

# Q.6)
# ---
cpt = Counter(Valeurs_X)
chancesSucces = cpt[28] / len(Valeurs_X) * 100
print(f"Proba de succes : {chancesSucces}%\n")

# Q.7)
# ----
NbMediansY = np.median(Valeurs_Y)
print(f"Nb médian : {NbMediansY}\n\n")



# ============
# Exercice 4 :
# ============
print("exo 4 ")
nBrealisations = 200
Valeurs_X = []
Valeurs_Y = []


# Q.1)
# ---
for cpt in range(nBrealisations):
    X, Y = une_chaine_domino()
    Valeurs_X.append(X)
    Valeurs_Y.append(Y)

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

print(f"Espérance de X : {EsperanceDeX}")
print(f"Espérance de Y : {EsperanceDeY}")
print(f"Espérance de Z : {EsperanceDeZ}\n")

# Q.3)
# ---
CovXY = np.cov(Valeurs_X, Valeurs_Y)[0, 1]
CorrXY = np.corrcoef(Valeurs_X, Valeurs_Y)[0, 1]
print(f"Covariance entre X & Y : {CovXY}")
print(f"Coefficient de corrélation entre X & Y : {CorrXY}")