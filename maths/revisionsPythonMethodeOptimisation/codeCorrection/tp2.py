# ============
# Exercice 1 :
# ============

# Définition de la fonction randomDico qui prend un graphe G en paramètre et crée un dictionnaire c associant à chaque sommet une valeur aléatoire entre 1 et 100.
def randomDico(G):
    c = {}
    for v in G.vertices():
        c[v] = randrange(1, 100)
    return c

# Définition de la fonction coutSolution qui calcule le coût total d'une solution S en utilisant le dictionnaire c.
def coutSolution(S, c):
    res = 0
    for x in S:
        res += c[x]
    return res

# Définition de la fonction CS_PLNE qui résout un problème de programmation linéaire en nombres entiers (PLNE) pour le problème de couverture de sommets.
def CS_PLNE(G, c):
    p = MixedIntegerLinearProgram(maximization=False)
    vars = p.new_variable(integer=True, nonnegative=True)
    
    # Contraintes : Chaque sommet a une valeur binaire (0 ou 1).
    for v in G.vertices():
        p.add_constraint(vars[v] <= 1)
    
    # Contraintes : Chaque arête a au moins un sommet sélectionné.
    for e in G.edges():
        p.add_constraint(vars[e[0]] + vars[e[1]] >= 1)
    
    # Fonction objectif : Maximiser la somme des valeurs des sommets sélectionnés multipliées par leur coût.
    p.set_objective(p.sum(vars[x] * c[x] for x in G.vertices()))
    
    # Résolution du PLNE.
    opt = p.solve()
    
    # Récupération de la solution.
    R = []
    for x in G.vertices():
        if p.get_values(vars[x]) == 1:
            R.append(x)
    
    return R

# Génération d'un graphe aléatoire avec 100 sommets et une densité de 1/5.
G = graphs.RandomGNP(100, 0.2)
c = randomDico(G)  # Création du dictionnaire de coûts aléatoires.
R1 = CS_PLNE(G, c)  # Résolution du problème de couverture de sommets avec PLNE.
print("PLNE:", len(R1), coutSolution(R1, c), R1)

# Remarque : Sur l'ordinateur personnel de l'auteur, le temps d'exécution est indiqué.
# À partir de 120 sommets environ, le temps d'attente devient significatif.

# ============
# Exercice 2 :
# ============

# Définition de la fonction CS_relaxPL qui résout la relaxation continue du problème de couverture de sommets.
def CS_relaxPL(G, c):
    p2 = MixedIntegerLinearProgram(maximization=False)
    vars = p2.new_variable(integer=False, nonnegative=True)
    
    # Contraintes : Chaque sommet a une valeur réelle entre 0 et 1.
    for v in G.vertices():
        p2.add_constraint(vars[v] <= 1)
    
    # Contraintes : Chaque arête a au moins un sommet sélectionné.
    for e in G.edges():
        p2.add_constraint(vars[e[0]] + vars[e[1]] >= 1)
    
    # Fonction objectif : Maximiser la somme des valeurs des sommets sélectionnés multipliées par leur coût.
    p2.set_objective(p2.sum(vars[x] * c[x] for x in G.vertices()))
    
    # Résolution de la relaxation continue.
    opt = p2.solve()
    
    # Récupération de la solution.
    R = []
    for x in G.vertices():
        if p2.get_values(vars[x]) >= 0.5:
            R.append(x)
    
    return R

R2 = CS_relaxPL(G, c)  # Résolution de la relaxation continue du problème de couverture de sommets.
print("relaxation:", len(R2), coutSolution(R2, c), R2)
