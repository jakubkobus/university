import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("task3_results.csv")

df["cmpPerN"] = df["avgComparisons"] / df["n"]
df["swpPerN"] = df["avgSwaps"] / df["n"]

groups = sorted(df["divSize"].unique())


def plot(metric_col, title, ylabel, filename):
    plt.figure(figsize=(12, 8))

    colors = {3: "red", 5: "blue", 7: "green", 9: "purple", 19: "orange", 21: "brown"}

    for divSize in groups:
        subset = df[df["divSize"] == divSize].sort_values(by="n")

        plt.plot(
            subset["n"],
            subset[metric_col],
            label=f"d = {divSize}",
            color=colors.get(divSize, "black"),
            linewidth=2.5,
        )

    plt.title(title, fontsize=15, fontweight="bold")
    plt.xlabel("Rozmiar tablicy (n)", fontsize=13)
    plt.ylabel(ylabel, fontsize=13)

    plt.legend(
        title="Rozmiar podziału", loc="upper left", bbox_to_anchor=(1, 1), fontsize=11
    )

    plt.ylim(bottom=0)
    plt.grid(True, linestyle=":", alpha=0.7)
    plt.tight_layout()

    plt.savefig(filename, dpi=300)
    print(f"Plot saved to '{filename}'")


if __name__ == "__main__":
    plot(
        "cmpPerN",
        "Porównania",
        r"Iloraz $\frac{C(n)}{n}$",
        "plot_comparisons.png",
    )

    plot(
        "swpPerN",
        "Przestawienia",
        r"Iloraz $\frac{S(n)}{n}$",
        "plot_swaps.png",
    )
