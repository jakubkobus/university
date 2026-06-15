import matplotlib.pyplot as plt
import pandas as pd


def generate_plots():
    try:
        df_A = pd.read_csv("results/resultA.csv")
        df_B = pd.read_csv("results/resultB.csv")
    except FileNotFoundError:
        print("[ERROR] Could not open the file/files")
        return

    N = df_A["N"]

    def plot_metric(metric_code, title, filename, ylabel, use_log_y=False):
        fig, axs = plt.subplots(2, 2, figsize=(14, 10))
        fig.suptitle(title, fontsize=16, fontweight="bold")

        axs[0, 0].plot(
            N,
            df_A[f"Avg_{metric_code}_Ins"],
            marker="o",
            label="Scenariusz A (Zdegenerowane)",
        )
        axs[0, 0].plot(
            N,
            df_B[f"Avg_{metric_code}_Ins"],
            marker="s",
            label="Scenariusz B (Zrównoważone)",
        )
        axs[0, 0].set_title("Wstawianie - Średni koszt")
        axs[0, 0].set_ylabel(ylabel)

        axs[0, 1].plot(
            N, df_A[f"Max_{metric_code}_Ins"], marker="o", label="Scenariusz A"
        )
        axs[0, 1].plot(
            N, df_B[f"Max_{metric_code}_Ins"], marker="s", label="Scenariusz B"
        )
        axs[0, 1].set_title("Wstawianie - Maksymalny koszt pojedynczej operacji")

        axs[1, 0].plot(
            N, df_A[f"Avg_{metric_code}_Del"], marker="o", label="Scenariusz A"
        )
        axs[1, 0].plot(
            N, df_B[f"Avg_{metric_code}_Del"], marker="s", label="Scenariusz B"
        )
        axs[1, 0].set_title("Usuwanie - Średni koszt")
        axs[1, 0].set_xlabel("Liczba elementów (N)")
        axs[1, 0].set_ylabel(ylabel)

        axs[1, 1].plot(
            N, df_A[f"Max_{metric_code}_Del"], marker="o", label="Scenariusz A"
        )
        axs[1, 1].plot(
            N, df_B[f"Max_{metric_code}_Del"], marker="s", label="Scenariusz B"
        )
        axs[1, 1].set_title("Usuwanie - Maksymalny koszt pojedynczej operacji")
        axs[1, 1].set_xlabel("Liczba elementów (N)")

        for ax in axs.flat:
            ax.grid(True, linestyle="--", alpha=0.7)
            ax.legend()
            if use_log_y:
                ax.set_yscale("log")

        plt.tight_layout(rect=[0, 0.03, 1, 0.95])
        plt.savefig(filename, dpi=300)
        print(f"Saved to '{filename}'")
        plt.close()

    plot_metric(
        "Cmp",
        "Liczba porównań kluczy w zależności od N",
        "plots/plot_comparisons.png",
        "Liczba porównań",
        # use_log_y=True,
    )

    plot_metric(
        "Ptr",
        "Liczba operacji na wskaźnikach w zależności od N",
        "plots/plot_pointers.png",
        "Odczyty / Zapisy",
        # use_log_y=True,
    )

    plot_metric(
        "H",
        "Wysokość BST po operacjach",
        "plots/plot_height.png",
        "Wysokość",
        # use_log_y=True,
    )


if __name__ == "__main__":
    generate_plots()
