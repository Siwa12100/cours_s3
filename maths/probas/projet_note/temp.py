# ============
# Exercice 1 : 
# ============

# 1. Il y a 28 dominos dans un jeu classique de dominos. 
# Chaque domino a deux parties, et il y a 7 valeurs différentes
#  pour chaque partie (0 à 6), ce qui donne un total de 7x7 = 49 dominos. 
#  Cependant, certains jeux classiques de dominos n'incluent pas les 
#  dominos en double (0-0, 1-1, 2-2, 3-3, 4-4, 5-5, 6-6), ce qui réduit 
#  le nombre de dominos à 28.

# 2. Le jeu peut s'arrêter sans avoir posé tous les dominos en raison 
# de l'exigence de correspondance entre les extrémités des dominos déjà
#  posés et les dominos restants dans la pioche. Si, à un moment donné,
#   aucun des dominos restants ne correspond aux extrémités disponibles
#    de la chaîne de dominos, le jeu ne peut plus progresser, et la partie
#     se termine.

# 3. X et Y sont des variables aléatoires parce qu'elles dépendent 
# du déroulement du jeu, qui est sujet à des événements aléatoires. 
# Chaque fois qu'un domino est pioché et placé dans la chaîne,
#  les valeurs de X et Y changent en conséquence. 
#  Les dominos sont tirés au hasard de la pioche, et la manière dont ils 
#  sont placés dans la chaîne dépend des choix aléatoires.
#   Par conséquent, X (nombre de dominos posés) et
#    Y (nombre de points restants dans la pioche) sont des variables
#  aléatoires qui peuvent prendre différentes valeurs à chaque partie 
#  du jeu en raison de l'aspect aléatoire du processus.


# ============
# Exercice 2 :
# ============

# Pour simuler une partie du jeu, vous pouvez utiliser une approche orientée
#  objet pour représenter la pioche, la chaîne de dominos et le déroulement
#   du jeu. Voici une possible implémentation :

import random

class DominoGame:
    def __init__(self):
        # Créer un jeu complet de dominos
        self.dominos = [(i, j) for i in range(7) for j in range(i, 7)]
        self.shuffle_dominos()

        # Initialiser la chaîne et les variables X et Y
        self.chain = []
        self.X = 0
        self.Y = sum(i + j for i, j in self.dominos)

    def shuffle_dominos(self):
        # Mélanger les dominos
        random.shuffle(self.dominos)

    def play_domino_game(self):
        # Tant qu'il reste des dominos dans la pioche
        while self.dominos:
            domino = self.dominos.pop(0)  # Prendre le premier domino de la pioche

            # Vérifier s'il peut être ajouté à l'un des bouts de la chaîne
            if self.chain and (domino[0] == self.chain[0][0] or domino[1] == self.chain[0][0]):
                self.chain.insert(0, domino)
            elif self.chain and (domino[0] == self.chain[-1][1] or domino[1] == self.chain[-1][1]):
                self.chain.append(domino)
            else:
                self.dominos.append(domino)  # Remettre le domino à la fin de la pioche

            self.X += 1
            self.Y -= domino[0] + domino[1]

        return self.X, self.Y

# Exemple d'utilisation de la classe DominoGame pour simuler une partie
def une_chaine_domino():
    game = DominoGame()
    X, Y = game.play_domino_game()
    return X, Y

# Appel de la fonction pour simuler une partie
X, Y = une_chaine_domino()
print(f"X = {X}, Y = {Y}")


# Dans cette implémentation, la classe `DominoGame` représente le jeu, 
# avec des méthodes pour mélanger les dominos et jouer une partie.
#  La méthode `play_domino_game` simule une partie du jeu et met à
#   jour les valeurs de X et Y en fonction du déroulement du jeu.

# Vous pouvez appeler la fonction `une_chaine_domino` pour simuler 
# une partie et obtenir les valeurs de X et Y. Vous pouvez également 
# répéter cette simulation autant de fois que nécessaire pour collecter
#  des statistiques empiriques.



# ============
# Exercice 3 : 
# ============

# Pour répondre à ces questions, vous pouvez utiliser les résultats de 
# vos simulations précédentes pour estimer les lois de probabilité, 
# les fonctions de répartition, les espérances, les variances,
#  les probabilités de succès et les médianes. Voici comment vous 
#  pourriez faire :

# Estimer et représenter la loi de probabilité de la variable X :

import matplotlib.pyplot as plt

# Récupérer les résultats de X à partir des simulations
X_values = [une_chaine_domino()[0] for _ in range(10000)]

# Estimer la loi de probabilité de X
plt.hist(X_values, bins=range(max(X_values) + 2), density=True, rwidth=0.8)
plt.title("Loi de probabilité de X")
plt.xlabel("X")
plt.ylabel("Probabilité")
plt.show()


# Calculer et tracer la fonction de répartition de X :
# Calculer la fonction de répartition de X
X_sorted = sorted(X_values)
X_cdf = [sum(1 for x in X_sorted if x <= xi) / len(X_sorted) for xi in X_sorted]

# Tracer la fonction de répartition de X
plt.plot(X_sorted, X_cdf)
plt.title("Fonction de répartition de X")
plt.xlabel("X")
plt.ylabel("Probabilité")
plt.show()


#  Estimer l'espérance de X :
# Estimer l'espérance de X
esp_X = sum(X_values) / len(X_values)
print(f"Espérance de X : {esp_X}")

# Estimer la variance de X :
# Estimer la variance de X
variance_X = sum((x - esp_X) ** 2 for x in X_values) / (len(X_values) - 1)
print(f"Variance de X : {variance_X}")


# Estimer et représenter la loi de probabilité de la variable Y (de la même manière que pour X).

# Estimer la probabilité de succès au jeu (parvenir à placer tous les dominos dans la chaîne) :
# Estimer la probabilité de succès au jeu
success_count = sum(1 for x, y in results if y == 0)
prob_success = success_count / len(results)
print(f"Probabilité de succès au jeu : {prob_success}")


# Estimer le nombre médian de points restants dans la pioche :

# Estimer le nombre médian de points restants dans la pioche
median_Y = sorted([y for x, y in results])[len(results) // 2]
print(f"Nombre médian de points restants dans la pioche : {median_Y}")

# En utilisant ces étapes, vous pouvez analyser les lois de probabilité 
# de X et Y, calculer des statistiques comme l'espérance et la variance,
#  et estimer la probabilité de succès et le nombre médian de points 
#  restants dans la pioche.



# ============
# Exercice 4 :
# ============

# Pour répondre à ces questions, nous allons effectuer des simulations 
# pour obtenir des données sur X, Y et Z, puis effectuer des calculs pour
#  estimer l'espérance, la covariance et le coefficient de corrélation. 
#  Voici comment vous pouvez procéder :

# 1. Effectuer 200 réalisations du jeu et représenter les valeurs correspondantes de X et Y sous la forme d'un nuage de points :

import matplotlib.pyplot as plt

# Effectuer 200 réalisations du jeu
num_simulations = 200
results = [une_chaine_domino() for _ in range(num_simulations)]

# Récupérer les valeurs de X et Y
X_values = [x for x, _ in results]
Y_values = [y for _, y in results]

# Nuage de points X vs Y
plt.scatter(X_values, Y_values, alpha=0.5)
plt.title("Nuage de points X vs Y")
plt.xlabel("X")
plt.ylabel("Y")
plt.show()


#Interprétation : Le nuage de points montre comment les valeurs de X et Y se répartissent dans les différentes réalisations du jeu. Il peut aider à identifier s'il y a une corrélation entre X et Y.

#2. Le nombre Z = X * Y est une variable aléatoire parce qu'il dépend des variables aléatoires X et Y, qui, à leur tour, dépendent du déroulement aléatoire du jeu.

#3. Estimer l'espérance de X, Y et Z et vérifier l'indépendance de X et Y :

# Espérance de X
esp_X = sum(X_values) / num_simulations

# Espérance de Y
esp_Y = sum(Y_values) / num_simulations

# Espérance de Z
Z_values = [x * y for x, y in results]
esp_Z = sum(Z_values) / num_simulations

print(f"Espérance de X : {esp_X}")
print(f"Espérance de Y : {esp_Y}")
print(f"Espérance de Z : {esp_Z}")

# Vérifier l'indépendance de X et Y
cov_XY = sum((x - esp_X) * (y - esp_Y) for x, y in zip(X_values, Y_values)) / (num_simulations - 1)
print(f"Covariance de X et Y : {cov_XY}")


# Si X et Y sont indépendants, la covariance devrait être proche de zéro.

# 4. Estimer la covariance des variables X et Y, puis leur coefficient de corrélation :

# Covariance de X et Y
cov_XY = sum((x - esp_X) * (y - esp_Y) for x, y in zip(X_values, Y_values)) / (num_simulations - 1)

# Coefficient de corrélation
corr_XY = cov_XY / (variance_X * variance_Y) ** 0.5

print(f"Covariance de X et Y : {cov_XY}")
print(f"Coefficient de corrélation de X et Y : {corr_XY}")

# Interprétation : La covariance de X et Y mesure comment les deux 
# variables varient ensemble. Si la covariance est positive, elles 
# augmentent ensemble, si elle est négative, elles varient en sens inverse,
#  et si elle est proche de zéro, elles sont faiblement corrélées.
#   Le coefficient de corrélation normalise la covariance et donne une 
#   mesure standardisée de la corrélation. Si le coefficient de corrélation
#    est proche de -1 ou 1, cela signifie une forte corrélation, tandis 
#    qu'un coefficient proche de 0 indique une faible corrélation.

# En analysant la covariance et le coefficient de corrélation, vous
#  pouvez déterminer la nature de la relation entre X et Y dans 
#  le contexte du jeu de dominos.