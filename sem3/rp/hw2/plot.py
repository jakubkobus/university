import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import sys

inputFile = './results/results.csv'
outDirectory = './results'

try:
    df = pd.read_csv(inputFile)
except Exception as e:
    print(f"Error while reading CSV: {e}")
    sys.exit(1)

df['D-C'] = df['D'] - df['C']
dfAvgs = df.groupby('n').mean().reset_index()

nValues = dfAvgs['n'].values
Ln_n = np.log(nValues)
Ln_Ln_n = np.log(Ln_n)

plt.style.use('seaborn-v0_8-whitegrid')

def savePlot(filename: str) -> None:
    fullPath = os.path.join(outDirectory, filename)
    plt.tight_layout()
    plt.savefig(fullPath, dpi=150)
    plt.close()
    print(f"Saved to '{fullPath}'")

def plotVariable(columnName: str, title: str, yLabel: str, filename: str) -> None:
    plt.figure(figsize=(10, 6))
    plt.scatter(df['n'], df[columnName], alpha=0.1, s=2, color='navy', label='Pojedyncze próby')
    plt.plot(dfAvgs['n'], dfAvgs[columnName], color='red', linewidth=2, label='Średnia')
    plt.title(title, fontsize=14)
    plt.xlabel('n', fontsize=12)
    plt.ylabel(yLabel, fontsize=12)
    plt.legend()
    plt.grid(True, alpha=0.3)
    savePlot(filename)

def plotQuotient(title: str, plotFunction: callable, filename: str) -> None:
    plt.figure(figsize=(10, 6))
    plotFunction()
    plt.title(title, fontsize=14)
    plt.xlabel('n', fontsize=12)
    plt.legend(fontsize=11)
    plt.grid(True, alpha=0.3)
    savePlot(filename)
    
def drawA():
    plt.plot(nValues, dfAvgs['B'] / nValues, label=r'$\frac{b(n)}{n}$', linestyle='--')
    plt.plot(nValues, dfAvgs['B'] / np.sqrt(nValues), label=r'$\frac{b(n)}{\sqrt{n}}$', color='red', linewidth=2)

def drawB():
    plt.plot(nValues, dfAvgs['U'] / nValues, label=r'$\frac{u(n)}{n}$', color='purple')
    plt.axhline(1/np.e, color='gray', linestyle='--', label=r'$\frac{1}{e} \approx 0.368$')

def drawC():
    plt.plot(nValues, dfAvgs['C'] / nValues, label=r'$\frac{c(n)}{n}$', linestyle=':')
    plt.plot(nValues, dfAvgs['C'] / (nValues * Ln_n), label=r'$\frac{c(n)}{n \ln n}$', color='red', linewidth=2)
    plt.plot(nValues, dfAvgs['C'] / (nValues**2), label=r'$\frac{c(n)}{n^2}$', linestyle='-.')

def drawD():
    plt.plot(nValues, dfAvgs['D'] / nValues, label=r'$\frac{d(n)}{n}$', linestyle=':')
    plt.plot(nValues, dfAvgs['D'] / (nValues * Ln_n), label=r'$\frac{d(n)}{n \ln n}$', color='red', linewidth=2)
    plt.plot(nValues, dfAvgs['D'] / (nValues**2), label=r'$\frac{d(n)}{n^2}$', linestyle='-.')

def drawE():
    diff = dfAvgs['D-C']
    plt.plot(nValues, diff / nValues, label=r'$\frac{d-c}{n}$', linestyle=':')
    plt.plot(nValues, diff / (nValues * Ln_n), label=r'$\frac{d-c}{n \ln n}$', linestyle='--')
    plt.plot(nValues, diff / (nValues * Ln_Ln_n), label=r'$\frac{d-c}{n \ln \ln n}$', color='red', linewidth=2)

plotVariable('B',   r'Wykres $B_n$',       'Liczba rzutów',      '1_Bn.png'   )
plotVariable('U',   r'Wykres $U_n$',       'Liczba pustych urn', '1_Un.png'   )
plotVariable('C',   r'Wykres $C_n$',       'Liczba rzutów',      '1_Cn.png'   )
plotVariable('D',   r'Wykres $D_n$',       'Liczba rzutów',      '1_Dn.png'   )
plotVariable('D-C', r'Wykres $D_n - C_n$', 'Liczba rzutów',      '1_Dn-Cn.png')

plotQuotient(r'Podpunkt $a$', drawA, '2_a.png')
plotQuotient(r'Podpunkt $b$', drawB, '2_b.png')
plotQuotient(r'Podpunkt $c$', drawC, '2_c.png')
plotQuotient(r'Podpunkt $d$', drawD, '2_d.png')
plotQuotient(r'Podpunkt $e$', drawE, '2_e.png')