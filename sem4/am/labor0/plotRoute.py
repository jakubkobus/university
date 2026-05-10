import matplotlib.pyplot as plt


def plotRoute(filepath: str) -> None:
    route: dict[str, list[float]] = {"x": [], "y": []}

    with open(filepath, "r") as f:
        for line in f:
            coordinates = line.strip().split()
            route["x"].append(float(coordinates[0]))
            route["y"].append(float(coordinates[1]))

    plt.figure(figsize=(10, 8))
    plt.plot(
        route["x"],
        route["y"],
        linestyle="-",
        marker="o",
        color="b",
        markersize=4,
        alpha=0.7,
    )

    plt.plot(
        route["x"][0], route["y"][0], marker="s", color="r", markersize=8, label="Start"
    )

    plt.title("Najlepsza wylosowana trasa")
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.legend()

    plt.savefig("best.png", dpi=300)


if __name__ == "__main__":
    plotRoute("best.txt")
