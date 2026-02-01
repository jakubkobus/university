import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as stats
import os

RESULTS_DIRECTORY = "results"
OUTPUT_DIRECTORY = "plots"

plt.style.use('seaborn-v0_8-whitegrid')
plt.rcParams['figure.figsize'] = (10, 6)
plt.rcParams['font.size'] = 12

def plotTask2():
    nValues = [5, 10, 15, 20, 25, 30, 100]

    for n in nValues:
        filePath = os.path.join(RESULTS_DIRECTORY, f"task2_n{n}.csv")
        if not os.path.exists(filePath):
            print(f"File '{filePath}' not found")
            continue
        
        df = pd.read_csv(filePath)
        data = df['Sn'].sort_values()
        
        nSamples = len(data)
        y = np.arange(1, nSamples + 1) / nSamples
        
        plt.figure()
        plt.step(data, y, label=rf'Dystrybuanta empiryczna $(N={n})$', where='post', color='blue')
        
        mu = 0
        sigma = np.sqrt(n)
        xTheory = np.linspace(mu - 4 * sigma, mu + 4 * sigma, 1000)
        yTheory = stats.norm.cdf(xTheory, mu, sigma)
        
        plt.plot(xTheory, yTheory, 'r--', label=rf'Rozkład normalny $N(0, \sqrt{{{n}}})$', linewidth=2)
        
        plt.xlabel('$S_N$')
        plt.ylabel('Dystrybuanta')
        plt.title(rf'Dystrybuanta empiryczna i teoretyczna dla $N={n}$')
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.savefig(f"{OUTPUT_DIRECTORY}/zad2_n{n}.png")
        plt.close()

def plotTask3():
    nValues = [100, 1000, 10000]
    
    xArc = np.linspace(0.01, 0.99, 500)
    yArc = 1 / (np.pi * np.sqrt(xArc * (1 - xArc)))

    for n in nValues:
        filePath = os.path.join(RESULTS_DIRECTORY, f"task3_n{n}.csv")
        if not os.path.exists(filePath):
            print(f"File '{filePath}' not found")
            continue
            
        df = pd.read_csv(filePath)
        data = df['Pn']
        
        plt.figure()
        
        plt.hist(data, bins=20, density=True, range=(0, 1), 
                 color='skyblue', edgecolor='black', alpha=0.6, label='Symulacja')
        
        plt.plot(xArc, yArc, 'r-', linewidth=2.5, label='Gęstość arcus sinus')
        
        plt.title(rf'Rozkład czasu nad osią dla $N={n}$')
        plt.xlabel(r'Frakcja czasu nad osią $\frac{L_N}{N}$')
        plt.ylabel('Gęstość prawdopodobieństwa')
        plt.legend()
        plt.xlim(0, 1)
        plt.ylim(0, 4)
        plt.grid(True, alpha=0.3)
        plt.savefig(f"{OUTPUT_DIRECTORY}/zad3_n{n}.png")
        plt.close()

if __name__ == "__main__":
    plotTask2()
    plotTask3()