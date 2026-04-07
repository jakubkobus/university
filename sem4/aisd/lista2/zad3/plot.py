import matplotlib.pyplot as plt
import pandas as pd

try:
    df = pd.read_csv("results.csv")
except FileNotFoundError:
    print("Could not find the file")
    exit()

k_values = df["k"].unique()

plot_configs = [
    ("c", "Średnia liczba porównań (c)"),
    ("s", "Średnia liczba przypisań (s)"),
    ("c_n", "Iloraz c / n"),
    ("s_n", "Iloraz s / n"),
]

for k in k_values:
    df_k = df[df["k"] == k]

    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    fig.suptitle(
        f"Porównanie dla k = {k}",
        fontsize=16,
        fontweight="bold",
    )

    axes = axes.flatten()

    for i, (y_col, ylabel) in enumerate(plot_configs):
        ax = axes[i]

        for algo in df_k["algo"].unique():
            df_algo = df_k[df_k["algo"] == algo]
            df_algo = df_algo.sort_values(by="n")

            ax.plot(df_algo["n"], df_algo[y_col], marker="o", linewidth=2, label=algo)

        ax.set_xlabel("Rozmiar tablicy (n)", fontsize=11)
        ax.set_ylabel(ylabel, fontsize=11)
        ax.grid(True, linestyle="--", alpha=0.7)
        ax.legend(fontsize=10)

    plt.tight_layout()
    plt.subplots_adjust(top=0.92)

    nazwa_pliku = f"plot_k{k}.png"
    plt.savefig(nazwa_pliku, dpi=300)
