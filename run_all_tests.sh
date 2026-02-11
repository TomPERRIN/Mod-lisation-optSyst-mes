#!/bin/bash

# Script pour exécuter tous les tests des TPs 1, 2 et 3
# et générer les graphiques

echo "=============================================="
echo "  KNAPSACK PROBLEM - TESTS AUTOMATIQUES"
echo "=============================================="
echo ""

# Vérifier que l'exécutable existe
if [ ! -f "./TP1" ]; then
    echo "Erreur: L'exécutable TP1 n'existe pas."
    echo "Compilez d'abord avec: make"
    exit 1
fi

# Créer un dossier pour les résultats
mkdir -p results
cd results

echo "1. Exécution des tests TP1 (Greedy & LP)..."
echo "   - n fixé, b variable"
echo "   - b fixé, n variable"
echo ""

# Créer un fichier temporaire avec les commandes
cat > commands.txt << 'EOF'
2

EOF

../TP1 < commands.txt > /dev/null 2>&1

echo "   ✓ Tests TP1 terminés"
echo ""

echo "2. Exécution des tests TP2 (Dynamic Programming)..."
echo "   - n fixé, b variable"
echo "   - b fixé, n variable"
echo ""

cat > commands.txt << 'EOF'
3

EOF

../TP1 < commands.txt > /dev/null 2>&1

echo "   ✓ Tests TP2 terminés"
echo ""

echo "3. Exécution des tests TP3 (Preprocessing)..."
echo ""

cat > commands.txt << 'EOF'
4

EOF

../TP1 < commands.txt > /dev/null 2>&1

echo "   ✓ Tests TP3 terminés"
echo ""

# Nettoyer
rm -f commands.txt

# Vérifier que les fichiers CSV ont été générés
if [ -f "results_tp1_fixed_n.csv" ] && [ -f "results_tp1_fixed_b.csv" ] && \
   [ -f "results_tp2_fixed_n.csv" ] && [ -f "results_tp2_fixed_b.csv" ] && \
   [ -f "results_tp3_preprocessing.csv" ]; then
    echo "✓ Tous les fichiers CSV ont été générés avec succès"
    echo ""
    
    # Lister les fichiers générés
    echo "Fichiers CSV générés:"
    ls -lh *.csv | awk '{print "  - " $9 " (" $5 ")"}'
    echo ""
    
    # Générer les graphiques avec Python
    if command -v python3 &> /dev/null; then
        echo "4. Génération des graphiques..."
        
        # Copier le script Python
        cp ../plot_results.py .
        
        # Vérifier si pandas et matplotlib sont installés
        python3 -c "import pandas, matplotlib" 2>/dev/null
        if [ $? -eq 0 ]; then
            python3 plot_results.py
            echo ""
            
            if [ -f "tp1_fixed_n_varying_b.png" ]; then
                echo "✓ Graphiques générés avec succès"
                echo ""
                echo "Graphiques PNG disponibles:"
                ls -lh *.png | awk '{print "  - " $9 " (" $5 ")"}'
            else
                echo "⚠ Erreur lors de la génération des graphiques"
            fi
        else
            echo "⚠ pandas et/ou matplotlib non installés"
            echo "  Installez avec: pip install pandas matplotlib"
            echo "  Puis exécutez: python3 plot_results.py"
        fi
    else
        echo "⚠ Python3 non trouvé. Installez Python3 pour générer les graphiques."
        echo "  Fichiers CSV disponibles dans results/"
    fi
else
    echo "⚠ Certains fichiers CSV sont manquants"
    echo "  Vérifiez les erreurs ci-dessus"
fi

cd ..

echo ""
echo "=============================================="
echo "  TESTS TERMINÉS"
echo "=============================================="
echo ""
echo "Les résultats se trouvent dans le dossier results/"
echo ""
