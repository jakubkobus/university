import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":
    # Zadanie 5
    try:
        df5 = pd.read_csv("results/task5.csv")
        plt.figure(figsize=(10, 6))
        plt.plot(
            df5["n"],
            df5["primTime_ms"],
            label="Prim",
            color="blue",
            marker="o",
        )
        plt.plot(
            df5["n"],
            df5["kruskalTime_ms"],
            label="Kruskal",
            color="red",
            marker="s",
        )

        plt.title("Zadanie 5: Czas działania algorytmów MST na pełnym grafie losowym")
        plt.xlabel("Liczba wierzchołków (n)")
        plt.ylabel("Czas wykonania [ms]")
        plt.grid(True, linestyle=":", alpha=0.7)
        plt.legend()
        plt.tight_layout()
        plt.savefig("plots/task5.png")
        print("Saved to 'plots/task5.png'")
    except FileNotFoundError:
        print("Could not open the file 'results/task5.csv'")

    # Zadanie 6
    try:
        df6 = pd.read_csv("results/task6.csv")
        plt.figure(figsize=(10, 6))
        plt.plot(
            df6["n"],
            df6["avgRounds"],
            label="Średnia liczba rund",
            color="green",
            marker="o",
        )
        plt.plot(
            df6["n"],
            df6["maxRounds"],
            label="Max",
            color="orange",
            linestyle="--",
            marker="^",
        )
        plt.plot(
            df6["n"],
            df6["minRounds"],
            label="Min",
            color="purple",
            linestyle="--",
            marker="v",
        )

        plt.fill_between(
            df6["n"], df6["minRounds"], df6["maxRounds"], color="gray", alpha=0.2
        )

        plt.title("Zadanie 6: Liczba rund propagacji w losowym drzewie MST")
        plt.xlabel("Liczba wierzchołków (n)")
        plt.ylabel("Liczba rund")
        plt.grid(True, linestyle=":", alpha=0.7)
        plt.legend()
        plt.tight_layout()
        plt.savefig("plots/task6.png")
        print("Saved to 'plots/task6.png'")
    except FileNotFoundError:
        print("Could not open the file 'results/task6.csv'")
