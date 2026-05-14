import re

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

SA_FILE = "analysis/sa_bruteforce_test.csv"
SA_OUT_FILE = "analysis/sa_params_analysis.png"

TS_FILE = "analysis/ts_bruteforce_test.csv"
TS_OUT_FILE = "analysis/ts_params_analysis.png"


def getN(filename):
    match = re.search(r"\d+", filename)
    return int(match.group()) if match else 1


def snap(value, allowedValues):
    return min(allowedValues, key=lambda x: abs(x - value))


if __name__ == "__main__":
    df_sa = pd.read_csv(SA_FILE)
    df_ts = pd.read_csv(TS_FILE)

    df_sa["N"] = df_sa["file"].apply(getN)
    df_ts["N"] = df_ts["file"].apply(getN)

    sa_steps_mults = [0.25, 0.5, 1.0, 2.0]
    ts_tabu_mults = [0.025, 0.05, 0.1, 0.2, 0.5]
    ts_samples_mults = [0.25, 0.5, 1.0, 2.0]

    df_sa["steps_mult"] = (df_sa["stepsPerEpoch"] / df_sa["N"]).apply(
        lambda x: snap(x, sa_steps_mults)
    )
    df_ts["tabusize_mult"] = (df_ts["tabuSize"] / df_ts["N"]).apply(
        lambda x: snap(x, ts_tabu_mults)
    )
    df_ts["sample_mult"] = (df_ts["sampleSize"] / df_ts["N"]).apply(
        lambda x: snap(x, ts_samples_mults)
    )

    best_sa = df_sa.groupby("file")["bestLength"].min()
    best_ts = df_ts.groupby("file")["bestLength"].min()
    overall_best = pd.concat([best_sa, best_ts], axis=1).min(axis=1)

    df_sa["rel_error"] = (
        (df_sa["avgLength"] - df_sa["file"].map(overall_best))
        / df_sa["file"].map(overall_best)
        * 100
    )
    df_ts["rel_error"] = (
        (df_ts["avgLength"] - df_ts["file"].map(overall_best))
        / df_ts["file"].map(overall_best)
        * 100
    )

    df_sa = df_sa.sort_values("N")
    df_ts = df_ts.sort_values("N")

    sns.set_theme(style="whitegrid")

    # Simulated Annealing
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    fig.suptitle(
        "Symulowane wyżarzanie",
        fontsize=16,
    )

    sns.boxplot(
        data=df_sa,
        x="initialTemperature",
        y="rel_error",
        hue="N",
        ax=axes[0, 0],
        palette="Set2",
    )
    axes[0, 0].set_title("Temperatura początkowa")

    sns.boxplot(
        data=df_sa, x="alpha", y="rel_error", hue="N", ax=axes[0, 1], palette="Set2"
    )
    axes[0, 1].set_title("Współczynnik chłodzenia")

    sns.boxplot(
        data=df_sa, x="epochs", y="rel_error", hue="N", ax=axes[1, 0], palette="Set2"
    )
    axes[1, 0].set_title("Liczba epok")

    sns.boxplot(
        data=df_sa,
        x="steps_mult",
        y="rel_error",
        hue="N",
        ax=axes[1, 1],
        palette="Set2",
    )
    axes[1, 1].set_title(r"Kroki na epokę $C \cdot N$")

    for ax in axes.flat:
        ax.set_xlabel("")
        ax.set_ylabel("")

    plt.tight_layout()
    plt.savefig(SA_OUT_FILE)

    # Tabu Search
    fig2, axes2 = plt.subplots(1, 3, figsize=(20, 7))
    fig2.suptitle(
        "Tabu Search",
        fontsize=16,
    )

    sns.boxplot(
        data=df_ts,
        x="tabusize_mult",
        y="rel_error",
        hue="N",
        ax=axes2[0],
        palette="Set2",
    )
    axes2[0].set_title(r"Wielkość tablicy tabu $C \cdot N$")

    sns.boxplot(
        data=df_ts,
        x="maxIterations",
        y="rel_error",
        hue="N",
        ax=axes2[1],
        palette="Set2",
    )
    axes2[1].set_title("Liczba iteracji")

    sns.boxplot(
        data=df_ts, x="sample_mult", y="rel_error", hue="N", ax=axes2[2], palette="Set2"
    )
    axes2[2].set_title(r"Wielkość próbki $C \cdot N$")

    for ax in axes2.flat:
        ax.set_xlabel("")
        ax.set_ylabel("")

    plt.tight_layout()
    plt.savefig(TS_OUT_FILE)
