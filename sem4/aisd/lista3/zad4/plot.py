import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("task4_results.csv")

fig, axes = plt.subplots(1, 2, figsize=(15, 6))

df_f1 = df[df["fun"] == "f1"]
axes[0].plot(
    df_f1["n"],
    df_f1["binarySearch"],
    label="Binary Search",
    color="red",
    linewidth=2,
)
axes[0].plot(
    df_f1["n"],
    df_f1["mySearch"],
    label="My Search",
    color="green",
    linewidth=2.5,
)

axes[0].set_title(r"$f(x) = (\log_2(x+1))^3$, $\delta = 10$", fontsize=13)
axes[0].set_xlabel("Rozmiar tablicy (n)", fontsize=11)
axes[0].set_ylabel("Liczba porównań", fontsize=11)
axes[0].legend()
axes[0].grid(True, linestyle=":", alpha=0.7)
axes[0].set_ylim(bottom=0)

df_f2 = df[df["fun"] == "f2"]
axes[1].plot(
    df_f2["n"],
    df_f2["binarySearch"],
    label="Binary Search",
    color="red",
    linewidth=2,
)
axes[1].plot(
    df_f2["n"],
    df_f2["mySearch"],
    label="My Search",
    color="green",
    linewidth=2.5,
)

axes[1].set_title(r"$f(x) = \sqrt{x} + \log_2(x + 1)$, $\delta = 50$", fontsize=13)
axes[1].set_xlabel("Rozmiar tablicy (n)", fontsize=11)
axes[1].set_ylabel("Liczba porównań", fontsize=11)
axes[1].legend()
axes[1].grid(True, linestyle=":", alpha=0.7)
axes[1].set_ylim(bottom=0)

plt.suptitle(
    "Koszt wyszukiwania (liczba odczytów z tablicy)",
    fontsize=16,
    fontweight="bold",
)
plt.tight_layout()
plt.savefig("task4_plot.png", dpi=300)
print("Plot saved to 'task4_plot.png'")
