import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

FILES = [
    './results/results1.csv',
    './results/results2.csv',
    './results/results3.csv'
]

OUT_DIR = './results/plots'

plt.style.use('seaborn-v0_8-whitegrid')

def savePlot(filename):
    full_path = os.path.join(OUT_DIR, filename)
    plt.tight_layout()
    plt.savefig(full_path, dpi=150)
    plt.close()
    print(f"Saved to '{full_path}'")

def plotTask1():
    df = pd.read_csv(FILES[0])
    
    dfAvg = df.groupby('n')[['aMaxLoad', 'bMaxLoad']].mean().reset_index()
    n = dfAvg['n']

    plt.figure(figsize=(10, 6))
    plt.plot(n, dfAvg['aMaxLoad'], label=r'$l_n^{(1)}$', color='blue',  linewidth=2)
    plt.plot(n, dfAvg['bMaxLoad'], label=r'$l_n^{(2)}$', color='green', linewidth=2)
    plt.title('Średnie maksymalne obciążenie urny', fontsize=14)
    plt.xlabel(r'Liczba kul/urn ($n$)', fontsize=12)
    plt.ylabel('Średnia liczba kul', fontsize=12)
    plt.legend(fontsize=12)
    savePlot('t1_maximum_load_comparison.png')
    
    plt.figure(figsize=(10, 6))
    plt.plot(n, dfAvg['aMaxLoad'] * np.log(np.log(n)) / np.log(n), color='blue', marker='o', markersize=3, label=r'$\frac{l_n^{(1)}}{f_1(n)}$')
    plt.title(r'Wykres ilorazu $\frac{l_n^{(1)}}{f_1(n)}$', fontsize=14)
    plt.xlabel(r'Liczba kul/urn ($n$)', fontsize=12)
    plt.ylabel('Stosunek', fontsize=12)
    plt.legend()
    savePlot('t1_plot_d1.png')

    plt.figure(figsize=(10, 6)) 
    plt.plot(n, dfAvg['bMaxLoad'] * np.log(2) / np.log(np.log(n)), color='red', linewidth=2, label=r'$\frac{l_n^{(2)}}{f_2(n)}$') 
    plt.title(r'Wykres ilorazu $\frac{l_n^{(2)}}{f_2(n)}$', fontsize=14)
    plt.xlabel(r'Liczba kul/urn ($n$)', fontsize=12)
    plt.ylabel('Stosunek', fontsize=12)
    plt.legend()
    savePlot('t1_plot_d2.png')

def plotTask2():
    df = pd.read_csv(FILES[1])

    dfAvg = df.groupby('n')[['comparisons', 'swaps']].mean().reset_index()
    n = dfAvg['n']

    plt.figure(figsize=(10, 6))
    plt.scatter(df['n'], df['comparisons'], alpha=0.1, s=5, color='salmon', label='Pojedyncze próby')
    plt.plot(n, dfAvg['comparisons'], color='red', linewidth=2, label=r'$cmp(n)$')
    plt.title('Liczba porównań', fontsize=14)
    plt.xlabel(r'Liczba elementów ($n$)', fontsize=12)
    plt.ylabel('Liczba operacji', fontsize=12)
    plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
    plt.legend()
    savePlot('t2_comparisons.png')

    plt.figure(figsize=(10, 6))
    plt.plot(n, dfAvg['comparisons'] / n, color='red', linewidth=2)
    plt.title(r'Iloraz $\frac{cmp(n)}{n}$', fontsize=14)
    plt.xlabel(r'Liczba elementów ($n$)', fontsize=12)
    plt.ylabel('Wartość', fontsize=12)
    savePlot('t2_comparisons_n.png')

    plt.figure(figsize=(10, 6))
    plt.plot(n, dfAvg['comparisons'] / (n**2), color='darkred', linewidth=2)
    plt.title(r'Iloraz $\frac{cmp(n)}{n^2}$', fontsize=14)
    plt.xlabel(r'Liczba elementów ($n$)', fontsize=12)
    plt.ylabel('Wartość', fontsize=12)
    savePlot('t2_comparisons_n2.png')

    plt.figure(figsize=(10, 6))
    plt.scatter(df['n'], df['swaps'], alpha=0.1, s=5, color='orange', label='Pojedyncze próby')
    plt.plot(n, dfAvg['swaps'], color='darkorange', linewidth=2, label=r'$s(n)$')
    plt.title('Liczba przestawień', fontsize=14)
    plt.xlabel(r'Liczba elementów ($n$)', fontsize=12)
    plt.ylabel('Liczba operacji', fontsize=12)
    plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
    plt.legend()
    savePlot('t2_swaps.png')

    plt.figure(figsize=(10, 6))
    plt.plot(n, dfAvg['swaps'] / n, color='orange', linewidth=2)
    plt.title(r'Iloraz $\frac{s(n)}{n}$', fontsize=14)
    plt.xlabel(r'Liczba elementów ($n$)', fontsize=12)
    plt.ylabel('Wartość', fontsize=12)
    savePlot('t2_swaps_n.png')

    plt.figure(figsize=(10, 6))
    plt.plot(n, dfAvg['swaps'] / (n**2), color='chocolate', linewidth=2)
    plt.title(r'Iloraz $\frac{s(n)}{n^2}$', fontsize=14)
    plt.xlabel(r'Liczba elementów ($n$)', fontsize=12)
    plt.ylabel('Wartość', fontsize=12)
    savePlot('t2_swaps_n2.png')

def plotTask3():
    df = pd.read_csv(FILES[2])
    
    pVals = [0.5, 0.1]
    colors = { pVals[0]: 'pink', pVals[1]: 'magenta' }
    
    for p in pVals:
        dfP = df[df['p'] == p]
        dfAvg = dfP.groupby('n')['Tn'].mean().reset_index()
        
        plt.figure(figsize=(10, 6))
        plt.scatter(dfP['n'], dfP['Tn'], alpha=0.2, s=5, color=colors[p], label='Liczba potrzebnych rund w pojedynczej próbie')
        plt.plot(dfAvg['n'], dfAvg['Tn'], color='black', linewidth=2, label=r'$t(n)$')
        plt.title(f'Ilość prób rozesłania wiadomości ($T_n$) dla $p={p}$', fontsize=14)
        plt.xlabel(r'Liczba stacji ($n$)', fontsize=12)
        plt.ylabel('Liczba rund', fontsize=12)
        plt.legend() 
        savePlot(f't3_Tn_p{str(p).replace('.', '')}.png')

if __name__ == "__main__":
    plotTask1()
    plotTask2()
    plotTask3()
    