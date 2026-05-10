import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("task2_results.csv")

df = df.sort_values(by="n")

df["cmpPerN"] = df["avgComparisons"] / df["n"]
df["swpPerN"] = df["avgSwaps"] / df["n"]


def plot(metric_col, title, ylabel, filename):
    plt.figure(figsize=(12, 7))

    colors = {"min": "blue", "median": "red", "max": "green"}

    for algo in ["RandomSelect", "Select"]:
        for kType in ["min", "median", "max"]:
            subset = df[(df["algo"] == algo) & (df["kType"] == kType)]

            linestyle = "-" if algo == "Select" else "--"

            plt.plot(
                subset["n"],
                subset[metric_col],
                linestyle=linestyle,
                color=colors[kType],
                marker="",
                linewidth=2.5,
                label=f"{algo} ({kType})",
            )

    plt.title(title, fontsize=14, fontweight="bold")
    plt.xlabel("Rozmiar tablicy (n)", fontsize=12)
    plt.ylabel(ylabel, fontsize=12)

    plt.ylim(bottom=0)

    plt.legend(loc="upper left", bbox_to_anchor=(1, 1))

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
