#!/usr/bin/env python3
"""
Script pour générer les graphiques de performance des algorithmes Knapsack
À utiliser après avoir exécuté les tests qui génèrent les fichiers CSV
"""

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def plot_tp1_fixed_n(csv_file="results_tp1_fixed_n.csv"):
    """TP1: Courbes de complexité avec n fixé, b variable"""
    if not os.path.exists(csv_file):
        print(f"Erreur: {csv_file} n'existe pas. Exécutez d'abord les tests TP1.")
        return
    
    df = pd.read_csv(csv_file)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))
    
    # Graphique 1: Temps d'exécution
    ax1.plot(df['b'], df['time_greedy_ms'], 'o-', label='Greedy', linewidth=2)
    ax1.plot(df['b'], df['time_lp_ms'], 's-', label='LP', linewidth=2)
    ax1.set_xlabel('Capacité b', fontsize=12)
    ax1.set_ylabel('Temps (ms)', fontsize=12)
    ax1.set_title('TP1: Complexité avec n fixé, b variable', fontsize=14)
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    # Graphique 2: Valeurs objectif
    ax2.plot(df['b'], df['value_greedy'], 'o-', label='Greedy', linewidth=2)
    ax2.plot(df['b'], df['value_lp'], 's-', label='LP', linewidth=2)
    ax2.set_xlabel('Capacité b', fontsize=12)
    ax2.set_ylabel('Valeur objectif', fontsize=12)
    ax2.set_title('TP1: Valeurs objectif', fontsize=14)
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('tp1_fixed_n_varying_b.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique sauvegardé: tp1_fixed_n_varying_b.png")
    plt.close()

def plot_tp1_fixed_b(csv_file="results_tp1_fixed_b.csv"):
    """TP1: Courbes de complexité avec b fixé, n variable"""
    if not os.path.exists(csv_file):
        print(f"Erreur: {csv_file} n'existe pas. Exécutez d'abord les tests TP1.")
        return
    
    df = pd.read_csv(csv_file)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))
    
    # Graphique 1: Temps d'exécution
    ax1.plot(df['n'], df['time_greedy_ms'], 'o-', label='Greedy', linewidth=2)
    ax1.plot(df['n'], df['time_lp_ms'], 's-', label='LP', linewidth=2)
    ax1.set_xlabel('Nombre d\'items n', fontsize=12)
    ax1.set_ylabel('Temps (ms)', fontsize=12)
    ax1.set_title('TP1: Complexité avec b fixé, n variable', fontsize=14)
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    # Graphique 2: Valeurs objectif
    ax2.plot(df['n'], df['value_greedy'], 'o-', label='Greedy', linewidth=2)
    ax2.plot(df['n'], df['value_lp'], 's-', label='LP', linewidth=2)
    ax2.set_xlabel('Nombre d\'items n', fontsize=12)
    ax2.set_ylabel('Valeur objectif', fontsize=12)
    ax2.set_title('TP1: Valeurs objectif', fontsize=14)
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('tp1_fixed_b_varying_n.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique sauvegardé: tp1_fixed_b_varying_n.png")
    plt.close()

def plot_tp2_fixed_n(csv_file="results_tp2_fixed_n.csv"):
    """TP2: Courbes de complexité DP avec n fixé, b variable"""
    if not os.path.exists(csv_file):
        print(f"Erreur: {csv_file} n'existe pas. Exécutez d'abord les tests TP2.")
        return
    
    df = pd.read_csv(csv_file)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))
    
    # Graphique 1: Temps d'exécution
    ax1.plot(df['b'], df['time_dp_ms'], 'o-', color='green', linewidth=2, label='Dynamic Programming')
    ax1.set_xlabel('Capacité b', fontsize=12)
    ax1.set_ylabel('Temps (ms)', fontsize=12)
    ax1.set_title('TP2: Complexité DP avec n fixé, b variable', fontsize=14)
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    # Graphique 2: Valeur vs b
    ax2.plot(df['b'], df['value_dp'], 'o-', color='green', linewidth=2, label='Valeur optimale')
    ax2.set_xlabel('Capacité b', fontsize=12)
    ax2.set_ylabel('Valeur objectif', fontsize=12)
    ax2.set_title('TP2: Valeur optimale vs capacité', fontsize=14)
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('tp2_fixed_n_varying_b.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique sauvegardé: tp2_fixed_n_varying_b.png")
    plt.close()

def plot_tp2_fixed_b(csv_file="results_tp2_fixed_b.csv"):
    """TP2: Courbes de complexité DP avec b fixé, n variable"""
    if not os.path.exists(csv_file):
        print(f"Erreur: {csv_file} n'existe pas. Exécutez d'abord les tests TP2.")
        return
    
    df = pd.read_csv(csv_file)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))
    
    # Graphique 1: Temps d'exécution
    ax1.plot(df['n'], df['time_dp_ms'], 'o-', color='green', linewidth=2, label='Dynamic Programming')
    ax1.set_xlabel('Nombre d\'items n', fontsize=12)
    ax1.set_ylabel('Temps (ms)', fontsize=12)
    ax1.set_title('TP2: Complexité DP avec b fixé, n variable', fontsize=14)
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    # Graphique 2: Valeur vs n
    ax2.plot(df['n'], df['value_dp'], 'o-', color='green', linewidth=2, label='Valeur optimale')
    ax2.set_xlabel('Nombre d\'items n', fontsize=12)
    ax2.set_ylabel('Valeur objectif', fontsize=12)
    ax2.set_title('TP2: Valeur optimale vs nombre d\'items', fontsize=14)
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('tp2_fixed_b_varying_n.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique sauvegardé: tp2_fixed_b_varying_n.png")
    plt.close()

def plot_tp3_preprocessing(csv_file="results_tp3_preprocessing.csv"):
    """TP3: Analyse du preprocessing"""
    if not os.path.exists(csv_file):
        print(f"Erreur: {csv_file} n'existe pas. Exécutez d'abord les tests TP3.")
        return
    
    df = pd.read_csv(csv_file)
    
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(14, 10))
    
    # Graphique 1: Comparaison des temps
    ax1.plot(df.index, df['time_without_preprocessing_ms'], 'o-', label='Sans preprocessing', linewidth=2)
    ax1.plot(df.index, df['time_with_preprocessing_ms'], 's-', label='Avec preprocessing', linewidth=2)
    ax1.set_xlabel('Test ID', fontsize=12)
    ax1.set_ylabel('Temps (ms)', fontsize=12)
    ax1.set_title('TP3: Comparaison temps d\'exécution', fontsize=14)
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    # Graphique 2: Speedup
    ax2.bar(df.index, df['speedup'], alpha=0.7, color='green')
    ax2.axhline(y=1.0, color='r', linestyle='--', label='Pas d\'amélioration')
    ax2.set_xlabel('Test ID', fontsize=12)
    ax2.set_ylabel('Speedup (x fois plus rapide)', fontsize=12)
    ax2.set_title('TP3: Speedup du preprocessing', fontsize=14)
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    # Graphique 3: Temps vs taille du problème (n)
    ax3.scatter(df['n'], df['time_without_preprocessing_ms'], alpha=0.6, label='Sans preprocessing', s=50)
    ax3.scatter(df['n'], df['time_with_preprocessing_ms'], alpha=0.6, label='Avec preprocessing', s=50)
    ax3.set_xlabel('Nombre d\'items n', fontsize=12)
    ax3.set_ylabel('Temps (ms)', fontsize=12)
    ax3.set_title('TP3: Temps vs taille du problème', fontsize=14)
    ax3.legend()
    ax3.grid(True, alpha=0.3)
    
    # Graphique 4: Temps vs capacité (b)
    ax4.scatter(df['b'], df['time_without_preprocessing_ms'], alpha=0.6, label='Sans preprocessing', s=50)
    ax4.scatter(df['b'], df['time_with_preprocessing_ms'], alpha=0.6, label='Avec preprocessing', s=50)
    ax4.set_xlabel('Capacité b', fontsize=12)
    ax4.set_ylabel('Temps (ms)', fontsize=12)
    ax4.set_title('TP3: Temps vs capacité', fontsize=14)
    ax4.legend()
    ax4.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('tp3_preprocessing_analysis.png', dpi=300, bbox_inches='tight')
    print("✓ Graphique sauvegardé: tp3_preprocessing_analysis.png")
    plt.close()
    
    # Statistiques
    print("\n=== STATISTIQUES TP3 ===")
    print(f"Speedup moyen: {df['speedup'].mean():.2f}x")
    print(f"Speedup médian: {df['speedup'].median():.2f}x")
    print(f"Speedup max: {df['speedup'].max():.2f}x")
    print(f"Speedup min: {df['speedup'].min():.2f}x")

def main():
    print("\n" + "="*60)
    print("  GÉNÉRATION DES GRAPHIQUES - KNAPSACK PROBLEM")
    print("="*60 + "\n")
    
    # Vérifier que les packages nécessaires sont installés
    try:
        import pandas
        import matplotlib
    except ImportError as e:
        print("Erreur: Packages manquants. Installez avec:")
        print("  pip install pandas matplotlib")
        return
    
    # Générer tous les graphiques
    plot_tp1_fixed_n()
    plot_tp1_fixed_b()
    plot_tp2_fixed_n()
    plot_tp2_fixed_b()
    plot_tp3_preprocessing()
    
    print("\n" + "="*60)
    print("  Tous les graphiques ont été générés avec succès!")
    print("="*60 + "\n")

if __name__ == "__main__":
    main()
