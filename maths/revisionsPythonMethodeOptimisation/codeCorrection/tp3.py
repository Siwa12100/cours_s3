# ============
# Exercice 1 :
# ============

# Définition de la fonction tournee_gloutonne qui prend une matrice M en paramètre et retourne une tournée gloutonne.
def tournee_gloutonne(M):
    n = len(M)
    T = [randrange(0, len(M))]  # Première ville au hasard

    while len(T) < n:
        meilleur_score = 1000000000
        meilleure_ville = 0
        derniere_ville = T[-1]

        for i in range(n):
            if i not in T:
                score = M[i][derniere_ville]
                if score < meilleur_score:
                    meilleur_score = score
                    meilleure_ville = i

        T.append(meilleure_ville)

    T.append(T[0])  # Revenir au début
    return T

# Exemple d'utilisation avec une matrice distances_20villes.
T20a = tournee_gloutonne(distances_20villes)
print(eval(T20a, distances_20villes), T20a)
afficher_tournee(T20a, coordonnees_20villes, noms_20villes, 8)

# Pour les 20 villes, on obtient entre 5295 et 6353 en fonction du départ.
# Pour les 48 villes, on obtient entre 37928 et 43778 en fonction du départ (optimum = 33523).

# ============
# Exercice 2 :
# ============

# Fonction d'évaluation d'une tournée T avec une matrice M.
def eval(T, M):
    cout = 0
    for i in range(len(T)-1):
        cout += M[T[i]][T[i+1]]
    return cout

# Fonction d'échange des villes i et j dans la tournée T.
def echange(T, i, j):
    nouv_tournee = []
    for k in range(len(T)-1):
        if k == i:
            nouv_tournee.append(T[j])
        elif k == j:
            nouv_tournee.append(T[i])
        else:
            nouv_tournee.append(T[k])
    nouv_tournee.append(nouv_tournee[0])  # Dernière ville = Première ville
    return nouv_tournee

# Fonction générant le voisinage d'une tournée T.
def voisinage(T):
    R = []
    for i in range(len(T)-1):
        for j in range(i+1, len(T)-1):
            R.append(echange(T, i, j))
    return R

# Fonction générant une tournée aléatoire.
def tournee_aleatoire(M):
    T = []
    while len(T) < len(M):
        next_city = randrange(0, len(M))
        if next_city not in T:
            T.append(next_city)
    T.append(T[0])
    return T

# Fonction de descente de gradient pour trouver une tournée optimale.
def descente_gradient(M):
    T = tournee_aleatoire(M)
    while True:
        N = voisinage(T)
        modif = False
        for tournee in N:
            if eval(tournee, M) < eval(T, M):
                T = tournee
                modif = True
        if not modif:
            break
    return T

# Exemple d'utilisation avec une matrice distances_20villes.
T20b = descente_gradient(distances_20villes)
print(eval(T20b, distances_20villes), T20b)
afficher_tournee(T20b, coordonnees_20villes, noms_20villes, 8)

# Pour les 20 villes, on obtient entre 4190 et 6597 (sur 500 exécutions).
# Pour les 48 villes, on obtient entre 42101 et 57495 (sur 50 exécutions). (optimum = 33523)
