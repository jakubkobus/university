import glob

import matplotlib.pyplot as plt
import pandas as pd

COLORS = {"insertion": "red", "quick": "blue", "hybrid": "green"}


def plot():
    for k in [1, 10, 100]:
        pattern = f"results/result_*_*_{k}.csv"
        k_files = glob.glob(pattern)

        if not k_files:
            print(f"No files for k={k}...")
            continue

        print(f"Processing k={k}...")

        data = []
        for file in k_files:
            try:
                df = pd.read_csv(file)
                if df.empty:
                    continue

                algo = df["algo"].iloc[0]
                n = df["size"].iloc[0]

                mean_c = df["comparisons"].mean()
                mean_s = df["swaps"].mean()

                data.append({"algo": algo, "n": n, "c": mean_c, "s": mean_s})
            except Exception as e:
                print(f"Could not read file {file}: {e}")

        if not data:
            continue

        df_all = pd.DataFrame(data)
        df_all["c/n"] = df_all["c"] / df_all["n"]
        df_all["s/n"] = df_all["s"] / df_all["n"]

        fig, axes = plt.subplots(2, 2, figsize=(16, 10))
        fig.suptitle(f"Porównanie dla k = {k}", fontsize=16)

        metrics = [
            ("c", "Średnia liczba porównań (c)"),
            ("s", "Średnia liczba przestawień (s)"),
            ("c/n", "Iloraz c/n"),
            ("s/n", "Iloraz s/n"),
        ]

        for i, (col, ylabel) in enumerate(metrics):
            ax = axes[i // 2, i % 2]

            for algo in ["insertion", "quick", "hybrid"]:
                subset = df_all[df_all["algo"] == algo].sort_values(by="n")

                if subset.empty:
                    continue

                ax.plot(
                    subset["n"],
                    subset[col],
                    marker="o",
                    linestyle="-",
                    color=COLORS.get(algo, "black"),
                    label=algo,
                )

            ax.set_xlabel("Rozmiar tablicy (n)")
            ax.set_ylabel(ylabel)
            ax.legend()
            ax.grid(True, linestyle="--", alpha=0.7)

        plt.tight_layout()

        output_filename = f"results/plots/plot_k{k}.png"
        plt.savefig(output_filename, dpi=300)
        print(f"Saved to file '{output_filename}'")
        plt.close()


if __name__ == "__main__":
    plot()
