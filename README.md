# Knapsack Problem - TPs 1, 2 et 3

Projet de résolution du problème du sac à dos (Knapsack Problem) avec différentes approches algorithmiques.

## 📋 Contenu

### TP1 - Relaxation Linéaire et Heuristique Gloutonne
- **Algorithme Glouton (Greedy)** : O(n log n)
- **Relaxation Linéaire (LP)** : O(n log n)
- Tests de complexité en fonction de n et b

### TP2 - Programmation Dynamique
- **Programmation Dynamique** : O(nb)
- Tests de complexité en fonction de n et b

### TP3 - Preprocessing / Réduction
- **Algorithme de préprocessing** pour réduire la taille du problème
- Analyse de l'efficacité du preprocessing
- Comparaison avec/sans preprocessing

## 🚀 Compilation

```bash
make clean
make
```

## 🎯 Utilisation

### Mode interactif (avec menu)
```bash
./TP1
```

Menu disponible :
1. Tester une instance spécifique
2. Tests TP1 (Greedy & LP)
3. Tests TP2 (Dynamic Programming)
4. Tests TP3 (Preprocessing)
5. Générer instances de test
0. Quitter

### Mode ligne de commande
```bash
# Tester avec une instance spécifique
./TP1 -F instance3.csv

# Afficher l'aide
./TP1 -h
```

## 📊 Génération des courbes de complexité

### Étape 1 : Exécuter les tests

#### Option A : Via le menu interactif
```bash
./TP1
# Puis choisir :
# - Option 2 pour TP1
# - Option 3 pour TP2
# - Option 4 pour TP3
```

#### Option B : Via un script bash
```bash
# Créer un script pour automatiser tous les tests
cat > run_all_tests.sh << 'EOF'
#!/bin/bash
echo "1" | ./TP1  # Tests TP1
echo "2" | ./TP1  # Tests TP2
echo "3" | ./TP1  # Tests TP3
EOF

chmod +x run_all_tests.sh
./run_all_tests.sh
```

### Étape 2 : Générer les graphiques

```bash
# Installer les dépendances Python (si nécessaire)
pip install pandas matplotlib

# Générer tous les graphiques
python3 plot_results.py
```

Fichiers CSV générés :
- `results_tp1_fixed_n.csv` : TP1 avec n fixé, b variable
- `results_tp1_fixed_b.csv` : TP1 avec b fixé, n variable
- `results_tp2_fixed_n.csv` : TP2 avec n fixé, b variable
- `results_tp2_fixed_b.csv` : TP2 avec b fixé, n variable
- `results_tp3_preprocessing.csv` : TP3 analyse du preprocessing

Graphiques générés :
- `tp1_fixed_n_varying_b.png`
- `tp1_fixed_b_varying_n.png`
- `tp2_fixed_n_varying_b.png`
- `tp2_fixed_b_varying_n.png`
- `tp3_preprocessing_analysis.png`

## 📁 Structure des fichiers

```
.
├── Makefile                 # Fichier de compilation
├── TP1.c                    # Programme principal
├── TP1Functions.c           # Implémentation des algorithmes
├── TP1Functions.h           # Déclarations
├── Tests.c                  # Fonctions de tests et mesures
├── Tests.h                  # Déclarations des tests
├── plot_results.py          # Script Python pour les graphiques
├── instance1.csv            # Instance exemple (TP2)
├── instance3.csv            # Instance exemple (TP3)
└── README.md                # Ce fichier
```

## 📝 Format des fichiers CSV d'instances

```
n,b
valeur1,poids1
valeur2,poids2
...
valeurn,poidsn
```

Exemple (instance1.csv) :
```
4,11
12,5
8,4
2,1
5,3
```

## 🔬 Détails des algorithmes

### TP1 - Algorithmes Gloutons

#### Greedy (Algorithme Glouton)
1. Trier les items par ratio décroissant c[i]/a[i]
2. Prendre les items dans l'ordre jusqu'à remplir le sac
3. **Complexité** : O(n log n) pour le tri

#### LP (Relaxation Linéaire)
1. Trier les items par ratio décroissant c[i]/a[i]
2. Prendre les items dans l'ordre, autorisant les fractions
3. **Complexité** : O(n log n) pour le tri

### TP2 - Programmation Dynamique

**Formule de récurrence** :
```
Z[y] = max { Z[y], Z[y - a[k]] + c[k] }
```

**Complexité** : O(nb)
- n : nombre d'items
- b : capacité du sac

### TP3 - Preprocessing

**Principe** :
1. Calculer solution gloutonne z_tilde
2. Calculer relaxation linéaire z_bar
3. Déterminer indice critique p
4. Fixer variables selon condition : c_bar[j] >= (z_bar - z_tilde)

**Avantages** :
- Réduit le nombre de variables
- Accélère la résolution du problème réduit
- Garantit l'optimalité

## 📈 Résultats attendus

### TP1
- **Complexité Greedy/LP** : Linéaire en n (après tri)
- **Qualité** : LP >= Greedy (borne supérieure)

### TP2
- **Complexité DP** : 
  - Linéaire en n pour b fixé
  - Linéaire en b pour n fixé
  - Quadratique O(nb) en général

### TP3
- **Speedup** : Variable selon les instances (1x à 10x+)
- **Variables fixées** : Typiquement 20-50% selon les instances
- **Qualité** : Identique au TP2 (solution optimale garantie)

## 🧪 Exemple de test complet

```bash
# 1. Compiler
make clean && make

# 2. Tester l'instance du TP3
./TP1 -F instance3.csv

# 3. Résultat attendu :
# - Greedy : 78
# - LP : 80.5
# - DP : 78
# - Preprocessing : 78 (avec 3 variables fixées)
```

## 🐛 Debugging

Si vous rencontrez des problèmes :

1. **Erreur de compilation** : Vérifiez que gcc est installé
2. **Erreur CSV** : Vérifiez le format (n,b en première ligne)
3. **Graphiques Python** : Installez pandas et matplotlib
4. **Résultats incorrects** : Vérifiez que les instances sont bien triées

## 📚 Références

- Algorithmes de sac à dos (Knapsack Problem)
- Programmation dynamique
- Algorithmes gloutons
- Techniques de preprocessing en optimisation combinatoire

## 👥 Auteurs

R. Chicoisne, R. Colares, D. Perdigao - 2025-26
Projet M1 Informatique - Modélisation et Optimisation
