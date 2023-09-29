import numpy as np
from scipy.special import factorial, binom
rng = np.random.default_rng()

#print(factorial(5))
#print(binom(5,6))

import matplotlib.pyplot as plt


# ============
# Exercice 1 : 
# ============

# 1.)
# --
# La bille peut atteindre k + 1 ou bien k à l'étage suivant. 


# 2.)
# --
# Y suit la loi de probabilité de Bernouilli (n fois). 

#p = 0.5

def bernouilli(p) :
    a = rng.random(1) < p
    return a

# print(bernouilli(0.5))
# print()

# Simulation d'une loi de bernouilli pour les valeurs 0 ou 1 : 
#rng = np.random.default_rng(12444)
# vals = rng.integers(low = 0, high = 2, size = 10)
# print()
# print(vals)
# print()

# 3.)
# --
def simul_planche(n,p) :
    tab = rng.random(n) < p
    return np.sum(tab)

#print(simul_planche(100, 0.5))

# 4.) 
# --

def simul_10000_billes(n, p) :
    tab = []
    for i in range(0, 10000) :
        val = simul_planche(n, p)
        tab.append(val)
    
    return tab

#print(simul_10000_billes(12, 0.5))


# 5.)
# --
tab = simul_10000_billes(12, 0.5)
plt.hist(tab, range =(0, 12 + 1), bins = 12)
#plt.show()


# 6.)
# --

tab = simul_10000_billes(12, 0.1)
plt.hist(tab, range =(0, 12 + 1), bins = 12)
#plt.show()

tab = simul_10000_billes(12, 0.9)
plt.hist(tab, range =(0, 12 + 1), bins = 12)
#plt.show()

tab = simul_10000_billes(12, 0.3)
plt.hist(tab, range =(0, 12 + 1), bins = 12)
#plt.show()

# Si la probabilité augmente, la moyenne des valeurs sera plus élevée. 
# A l'inverse, si la proba baisse (comme p = 0.3), alors l'endroit où la 
# majorité des billes arrive est plus prêt de 0 




# ============
# Exercice 2 :
# ============binom(5,6)

# 1.)
# --
# Il s'agit d'une loi binomiale. En effet, tous les mouvements d'une bille
# sont indépendants les un des autres, et il n'y a que 2 possibilités, aller 
# à gauche ou à droite. 

# 2.)
# --
p = 0.5
n = 12 
binTab = []
for k in range (0, n) :
    binTab.append(binom(n, k) * p ** k * (1 - p)**(n - k))
    #print(binom(n, k) * p ** k * (1 - p)**(n - k))

#plt.show()
#print(binTab)




# ============
# Exercice 3 : 
# ============

# 1.)
# --
# Il s'agirait d'une planche penchée vers la gauche, pour que les 
# billes aient plus de chances d'aller vers la gauche.


# 2.)
# --
# V[x] = n * p ( 1 - p)
var = 1000 * 0.004 * ( 1 - 0.004)
print(var)


# 3.)
# -- 
