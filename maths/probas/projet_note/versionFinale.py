import random
import numpy as np
import matplotlib.pyplot as plt
from collections import Counter

# ==========
# Exercice 1
# ========== 
print("Exercice 1\n")

# Q1. Combien y a-t-il de dominos dans un jeu classique?
print("Q1.")
print("Il y a 28 dominos dans un jeu classique.\n")

# Q2. Pourquoi est-il possible que le jeu s'arrête sans avoir posé tous les dominos?
print("Q2.")
print(
    "Le jeu peut s'arrêter sans avoir posé tous les dominos lorsque plus aucun domino de la pioche ne peut être posé dans la chaîne. Cela se produit lorsque les côtés d'un domino ne correspondent pas aux côtés des dominos déjà posés dans la chaîne, forçant ainsi l'arrêt du jeu.\n")

# Q3. Pourquoi X et Y sont des variables aléatoires?
print("Q3.")
print(
    "X et Y sont des variables aléatoires car leurs valeurs dépendent du hasard et des tirages aléatoires lors du jeu. La façon dont les dominos sont tirés et placés dans la chaîne dépend de résultats aléatoires, ce qui signifie que X (nombre de dominos posés dans la chaîne) et Y (nombre de points restants dans la pioche) varient d'une partie à l'autre en fonction de ces résultats aléatoires. Par conséquent, X et Y sont des variables aléatoires, et l'objectif de ce TP est d'étudier empiriquement leur distribution de probabilité.\n")

# Exercice 2
print("Exercice 2\n")


# Fonction pour simuler une réalisation du jeu et renvoyer X et Y
def une_chaine_domino():
    """
    Simule une réalisation du jeu de chaîne de dominos et renvoie les valeurs de X et Y.

    Returns:
        X (int): Le nombre de dominos posés dans la chaîne.
        Y (int): Le nombre de points restants dans la pioche.
    """
    # Initialisation de la pioche de dominos et de la chaîne
    pioche = [[i, j] for i in range(7) for j in range(i, 7)]
    chaine = []

    while pioche:
        # Tirage aléatoire d'un domino depuis la pioche
        domino = random.choice(pioche)
        pioche.remove(domino)  # Retirer le domino de la pioche

        # Logique pour placer le domino dans la chaîne ou le remettre à la fin de la pioche
        # (à implémenter)

    # Calcul de X (nombre de dominos posés) et Y (nombre de points restants)
    X = len(chaine)
    Y = sum(sum(domino) for domino in pioche)

    return X, Y


# Appel de la fonction pour simuler une réalisation du jeu
X, Y = une_chaine_domino()
print(f"X = {X}, Y = {Y}\n")

# Exercice 3
print("Exercice 3\n")

# Simuler un grand nombre de réalisations du jeu (au moins 10,000)
num_realisations = 10_000
result_X = []
result_Y = []

for _ in range(num_realisations):
    X, Y = une_chaine_domino()
    result_X.append(X)
    result_Y.append(Y)

# 1. Estimer et représenter la loi de probabilité de la variable X
plt.grid(axis='y', alpha=0.75)
plt.hist(result_X, bins=range(0, 30), density=True, alpha=0.75, color='blue')
plt.xlabel('X (Nombre de dominos posés)')
plt.ylabel('Probabilité')
plt.title('Distribution de probabilité de X')
plt.show()

# 2. Calculer et tracer la fonction de répartition de X
X_sorted = np.sort(result_X)
cdf = np.arange(1, len(X_sorted) + 1) / len(X_sorted)
plt.grid(axis='y', alpha=0.75)
plt.plot(X_sorted, cdf, color='green')
plt.xlabel('X (Nombre de dominos posés)')
plt.ylabel('Probabilité Cumulative')
plt.title('Fonction de répartition cumulative de X')
plt.show()

# 3. Estimer l'espérance de X
expectation_X = np.mean(result_X)
print("Q3.")
print(f"Espérance de X : {expectation_X}\n")

# 4. Estimer la variance de X
print("Q4.")
variance_X = np.var(result_X)
print(f"Variance de X : {variance_X}\n")

# 5. Répéter les étapes 1 à 4 pour la variable Y (nombre de points restants dans la pioche)
plt.grid(axis='y', alpha=0.75)
plt.hist(result_Y, bins=range(0, 169), density=True, alpha=0.75, color='blue')
plt.xlabel('Y (Nombre de points restants dans la pioche)')
plt.ylabel('Probabilité')
plt.title('Distribution de probabilité de Y')
plt.show()

print("Q5.")
Y_sorted = np.sort(result_Y)
cdf = np.arange(1, len(Y_sorted) + 1) / len(Y_sorted)
plt.grid(axis='y', alpha=0.75)
plt.plot(Y_sorted, cdf, color='green')
plt.xlabel('Y (Nombre de points restants dans la pioche)')
plt.ylabel('Probabilité Cumulative')
plt.title('Fonction de répartition cumulative de Y')
plt.show()

expectation_Y = np.mean(result_Y)
print(f"Espérance de Y : {expectation_Y}")

variance_Y = np.var(result_Y)
print(f"Variance de Y : {variance_Y}\n")

# 6. Estimer la probabilité de succès au jeu (tous les dominos placés)
print("Q6.")
n = Counter(result_X)

probability_success = n[28] / len(result_X) * 100

print(f"Probabilité de réussite dans le jeu : {probability_success}%\n")

# 7. Estimer le nombre médian de points restants dans la pioche
print("Q7.")
median_Y = np.median(result_Y)
print(f"Nombre médian de points restants dans la pioche : {median_Y}\n\n")

# Exercice 4
print("Exercice 4\n")

# Répéter 200 réalisations du jeu et représenter X par rapport à Y sous la forme d'un nuage de points
num_realisations = 200
result_X = []
result_Y = []

for _ in range(num_realisations):
    X, Y = une_chaine_domino()
    result_X.append(X)
    result_Y.append(Y)

# Nuage de points X par rapport à Y
plt.grid(alpha=0.5)
plt.scatter(result_X, result_Y, alpha=0.5)
plt.xlabel('X (Nombre de dominos posés)')
plt.ylabel('Y (Nombre de points restants dans la pioche)')
plt.title('Nuage de points X vs. Y')
plt.show()

# Calcul de l'espérance de X, Y et Z (Z = X * Y)
print("Q2.")
expectation_X = np.mean(result_X)
expectation_Y = np.mean(result_Y)
expectation_Z = np.mean(np.array(result_X) * np.array(result_Y))
print(f"Espérance de X : {expectation_X}")
print(f"Espérance de Y : {expectation_Y}")
print(f"Espérance de Z : {expectation_Z}\n")

# Vérifier si X et Y sont indépendants en calculant la covariance et le coefficient de corrélation
print("Q3.")
covariance_XY = np.cov(result_X, result_Y)[0, 1]
correlation_XY = np.corrcoef(result_X, result_Y)[0, 1]
print(f"Covariance entre X et Y : {covariance_XY}")
print(f"Coefficient de corrélation entre X et Y : {correlation_XY}")