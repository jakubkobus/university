from pathlib import Path

import matplotlib.pyplot as plt


def plotRoute(input_filepath: Path, output_filepath: Path) -> None:
    route: dict[str, list[float]] = {"x": [], "y": []}

    with open(input_filepath, "r") as f:
        for line in f:
            coordinates = line.strip().split()
            if len(coordinates) >= 2:
                route["x"].append(float(coordinates[0]))
                route["y"].append(float(coordinates[1]))

    plt.figure(figsize=(10, 8))
    plt.plot(
        route["x"],
        route["y"],
        linestyle="-",
        marker="o",
        color="b",
        markersize=0,
        alpha=0.4,
    )

    if route["x"]:
        plt.plot(
            route["x"][0],
            route["y"][0],
            marker="s",
            color="r",
            markersize=5,
            label="Start",
        )

    plt.title("Best route")
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.legend()

    plt.savefig(output_filepath, dpi=300)
    plt.close()


if __name__ == "__main__":
    script_dir = Path(__file__).parent
    txt_dir = script_dir / "results" / "txt"
    plots_dir = script_dir / "results" / "plots"

    plots_dir.mkdir(parents=True, exist_ok=True)

    for txt_file in txt_dir.glob("*.txt"):
        print(f"Plotting for: {txt_file.name}")
        output_file = plots_dir / txt_file.with_suffix(".png").name
        plotRoute(txt_file, output_file)
