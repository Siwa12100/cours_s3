# =========
# Rappels :
# =========

# Création d'une liste L avec 3 éléments.
L = [1, 4, "toto"]

# Ajout de l'élément 2 en fin de L.
L.append(2)

# Insertion de "x" en 4e position de L.
L.insert(3, "x")

# Affichage de la longueur de L.
print(len(L))

# Affichage du deuxième élément de L.
print(L[1])

# Affichage du dernier élément de L.
print(L[-1])

# Test si 3 est dans L.
if 3 in L:
    # Boucle sur les éléments de L.
    for a in L:
        pass

# Suppression de toutes les occurrences de "y" dans L.
L.remove("y")

# Suppression de L[2].
L.pop(2)

# Suppression de tous les éléments de L.
L.clear()

# Création d'un dictionnaire.
dico = {2: "toto", 5: "titi", "x": "tata"}

# Création d'un dictionnaire vide.
dico = {}

# Mise à jour de l'élément de clé 5.
dico[5] = "tutu"

# Ajout d'un élément de clé 1.
dico[1] = "tete"

# Liste des clés.
dico.keys()

# Liste des valeurs.
dico.values()

# Suppression du couple clé/valeur de clé 2.
dico.pop(2)

# =======
# Exo 1 :
# =======

# a.)
# ---
p = MixedIntegerLinearProgram(maximization=False)
V = p.new_variable(real=True, nonnegative=True)
a, b, c, d, e = V[0], V[1], V[2], V[3], V[4]

# Contraintes : Protéines, vitamine C, fer.
p.add_constraint(5 * a + 10 * b + 7.8 * c + 25 * d + 13 * e >= 56)
p.add_constraint(478 * a + 70 * b + 20 * c + 4 * d + 65 * e >= 110)
p.add_constraint(3 * a + 12 * b + 2.4 * c + 10 * d + 8 * e >= 2)

# Fonction objectif.
p.set_objective(3.1 * a + 2.1 * b + 1.6 * c + 8.7 * d + 3.8 * e)

p.show()
opt = p.solve()
print(opt, p.get_values(V))

# b.)
# ---
# La solution est de manger 7.18 kg de carottes pour 11.49 euros.
# Ce n’est pas très varié ! C’est dû au fait que les carottes contiennent assez des trois nutriments.
# Si on augmente le prix des carottes à 1.7 euros, on obtient une autre solution uniquement à base de... bananes.
# On peut aussi baisser les taux de nutriments des carottes/bananes pour favoriser les autres aliments.
# On remarque que la contrainte sur le fer est très facile à satisfaire puisque tous les aliments en contiennent assez.
# On peut aussi limiter les quantités d’aliments à 0.5 kg, par exemple, pour obtenir des solutions plus intéressantes.

# ============
# Exercice 2 :
# ============

# Création d'un graphe orienté.
G = DiGraph()

# Ajout de sommets et d'arcs au graphe.
G.add_vertex(name="toto")
G.add_vertex(name="a")
G.add_vertex(name="b")
G.add_edge("a", "b", 6)

# Boucle sur la liste des arcs de G.
for e in G.edges():
    print(e[0], e[1], e[2])

# Boucle sur la liste des sommets de G.
for v in G.vertices():
    print(G.neighbors_out(v))  # Affiche la liste des voisins sortants de v.
    print(G.neighbors_in(v))   # Affiche la liste des voisins entrants de v.
    print(G.neighbors(v))      # Affiche la liste de tous les voisins de v.
    print(G.incoming_edges(v))  # Affiche la liste des arcs entrant dans v.
    print(G.outgoing_edges(v))  # Affiche la liste des arcs sortant de v.

# Dessine le graphe en affichant les étiquettes.
G.show(edge_labels=True)

# a.)
# ---
G = DiGraph()
G.add_edge("s", "x", label="3")
G.add_edge("s", "y", label="2")
G.add_edge("x", "y", label="1")
G.add_edge("x", "d", label="1")
G.add_edge("y", "d", label="3")

# b.)
# ---
p = MixedIntegerLinearProgram(maximization=True)
V = p.new_variable(real=True, nonnegative=True)

# Fonction objectif : Par exemple, la valeur des arcs qui sortent de s.
p.set_objective(V["sx"] + V["sy"])

# Contraintes de capacités des arcs.
p.add_constraint(V["sx"] <= 3)
p.add_constraint(V["sy"] <= 2)
p.add_constraint(V["xy"] <= 1)
p.add_constraint(V["xd"] <= 1)
p.add_constraint(V["yd"] <= 3)

# Contraintes d'égalité de flot sur chaque sommet.
p.add_constraint(V["sx"] == V["xy"] + V["xd"])  # Sommet x
p.add_constraint(V["sy"] + V["xy"] == V["yd"])  # Sommet y

p.show()
opt = p.solve()
print("flot optimal: " + str(opt), " --- valeurs du flot: ", p.get_values(V))

# c.)
# ---
# Le PL est similaire à (b), mais avec 16 contraintes pour les capacités des arcs, et 7 contraintes
# pour l'égalité du flot sur les sommets. Le flot optimal a une valeur de 20.

# d.)
# ---
def flot(G, s, t):
    p = MixedIntegerLinearProgram(maximization=True)
    V = p.new_variable(real=True, nonnegative=True)
    p.set_objective(p.sum(V[e] for e in G.outgoing_edges(s)))

    for e in G.edges():
        p.add_constraint(V[e] <= e[2])

    for x in G.vertices():
        if x != s and x != t:
            p.add_constraint(p.sum(V[e] for e in G.incoming_edges(x)) ==
                             p.sum(V[e] for e in G.outgoing_edges(x)))

    p.show()
    opt = p.solve()
    print("flot optimal: " + str(opt), "--- valeurs du flot: ", p.get_values(V))
    return opt