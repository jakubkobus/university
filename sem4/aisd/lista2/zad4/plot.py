import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def saddleback(m, n):
    return m + n


def binary(m, n):
    return min(m, n) * np.log2(max(m, n))


if __name__ == "__main__":
    df = pd.read_csv("results.csv")

    unique_dims = df[["shape", "m", "n"]].drop_duplicates()

    df_rect = df[df["shape"] == "Rectangle"].copy()
    df_rect["Label"] = df_rect["m"].astype(str) + "x" + df_rect["n"].astype(str)

    labels = df_rect["Label"].unique()
    dims_rect = unique_dims[unique_dims["shape"] == "Rectangle"]

    t_sad_y = [saddleback(row["m"], row["n"]) for _, row in dims_rect.iterrows()]
    t_bin_y = [binary(row["m"], row["n"]) for _, row in dims_rect.iterrows()]

    plt.figure(figsize=(14, 7))

    for alg, color in zip(
        ["Binary", "Saddleback", "Hybrid"], ["#1f77b4", "#ff7f0e", "#2ca02c"]
    ):
        data = df_rect[df_rect["algo"] == alg]
        linewidth = 3.5 if alg == "Hybrid" else 2.5
        plt.plot(
            data["Label"],
            data["comparisons"],
            marker="o",
            linewidth=linewidth,
            color=color,
            label=f"{alg}",
        )

    plt.plot(
        labels,
        t_bin_y,
        linestyle=":",
        marker="x",
        linewidth=2,
        color="darkblue",
        alpha=0.7,
        label=r"Binary $O(\min(m, n) \cdot \log_2(\max(m, n)))$",
    )
    plt.plot(
        labels,
        t_sad_y,
        linestyle=":",
        marker="x",
        linewidth=2,
        color="saddlebrown",
        alpha=0.7,
        label=r"Saddleback $O(m + n)$",
    )

    plt.title(
        "Złożoność w zależności od proporcji macierzy",
        fontsize=15,
    )
    plt.xlabel("Wymiary macierzy (M x N)", fontsize=12)
    plt.ylabel("Liczba porównań", fontsize=12)
    plt.yscale("log")
    plt.xticks(rotation=45)
    plt.grid(True, which="both", ls="--", alpha=0.5)

    plt.legend(fontsize=11, loc="center left", bbox_to_anchor=(1, 0.5))
    plt.tight_layout()
    plt.savefig("plot_rect.png", dpi=300)

    df_sq = df[df["shape"] == "Square"].copy()
    dims_sq = unique_dims[unique_dims["shape"] == "Square"]

    t_sad_sq = [saddleback(row["m"], row["n"]) for _, row in dims_sq.iterrows()]
    t_bin_sq = [binary(row["m"], row["n"]) for _, row in dims_sq.iterrows()]

    plt.figure(figsize=(12, 7))

    for alg, color in zip(
        ["Binary", "Saddleback", "Hybrid"], ["#1f77b4", "#ff7f0e", "#2ca02c"]
    ):
        data = df_sq[df_sq["algo"] == alg]
        linewidth = 3.5 if alg == "Hybrid" else 2.5
        plt.plot(
            data["m"],
            data["comparisons"],
            marker="s",
            linewidth=linewidth,
            color=color,
            label=f"{alg}",
        )

    plt.plot(
        dims_sq["m"],
        t_bin_sq,
        linestyle=":",
        linewidth=2,
        color="darkblue",
        alpha=0.7,
        label=r"Binary $O(M \cdot \log_2(M))$",
    )
    plt.plot(
        dims_sq["m"],
        t_sad_sq,
        linestyle=":",
        linewidth=2,
        color="saddlebrown",
        alpha=0.7,
        label=r"Saddleback $O(2M)$",
    )

    plt.title("Złożoność dla macierzy kwadratowych", fontsize=15)
    plt.xlabel("Długość boku macierzy (M)", fontsize=12)
    plt.ylabel("Liczba porównań", fontsize=12)
    plt.grid(True, linestyle="--", alpha=0.7)
    plt.legend(fontsize=12)
    plt.tight_layout()
    plt.savefig("plot_square.png", dpi=300)
