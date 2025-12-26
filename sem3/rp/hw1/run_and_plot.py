import numpy as np
import matplotlib.pyplot as plot

def monteCarloIntegration(
        function: callable,
        a: float,
        b: float,
        M: float,
        n: int
    ) -> float:
    x_rand = np.random.uniform(a, b, n)
    y_rand = np.random.uniform(0, M, n)
    
    C = np.sum(y_rand <= function(x_rand))
    return (C / n) * (b - a) * M

def runAndPlot(
        function: callable,
        a: float,
        b: float,
        M: float,
        exactValue: float,
        kValues: list[int],
        nValues: list[int],
        title: str,
        filename: str,
        multiplier: float = 1.0
    ) -> None:
    for k in kValues:
        allResults = []
        avgResults = []
        
        for n in nValues:
            nResults = [
                multiplier * monteCarloIntegration(
                    function=function,
                    a=a,
                    b=b,
                    M=M,
                    n=n,
                )
                for _ in range(k)
            ]
            allResults.append(nResults)
            avgResults.append(np.mean(nResults))
        
        fig, ax = plot.subplots(figsize=(12, 7))

        for i, n in enumerate(nValues):
            ax.plot(
                [n] * k, 
                allResults[i], 
                'bo', 
                markersize=3, 
                alpha=0.1 if k == 50 else 0.3
            )
            
            ax.plot(
                n, 
                avgResults[i], 
                'ro', 
                markersize=6
            )

        ax.axhline(
            y=exactValue,
            color='green', 
            linestyle='-', 
            linewidth=3, 
            label=f'Prawdziwa wartość = {exactValue:.4f}'
        )

        ax.plot(
            [], 
            [], 
            'bo', 
            markersize=3, 
            label='Wyniki poszczególnych powtórzeń'
        )

        ax.plot(
            [], 
            [], 
            'ro', 
            markersize=6, 
            label='Średnia wartość dla każdego $n$'
        )

        ax.set_xlabel('Liczba punktów ($n$)')
        ax.set_ylabel('Aproksymowana wartość')
        ax.set_title(f'{title} (k = {k})')
        ax.legend()
        ax.grid(True)

        _filename = f'{filename}_k{k}.png'
        plot.savefig(_filename)
        print(f"[+] {_filename}")
        plot.close(fig)

if __name__ == "__main__":
    nValues = [50 * i for i in range(1, 101)]
    kValues = [5, 50]

    a1 = lambda x: np.cbrt(x)
    a2 = lambda x: np.sin(x)
    a3 = lambda x: 4 * x * pow((1 - x), 3)
    b  = lambda x: np.sqrt(1 - pow(x, 2))

    runAndPlot( # punkt a, podpunkt pierwszy
        function=a1,
        a=0, 
        b=8, 
        M=2,
        exactValue=12.0,
        kValues=kValues,
        nValues=nValues,
        title=r'Aproksymacja $\int_{0}^{8} \sqrt[3]{x} dx$',
        filename='a1'
    )

    runAndPlot( # punkt a, podpunkt drugi
        function=a2,
        a=0,
        b=np.pi,
        M=1,
        exactValue=2.0,
        kValues=kValues,
        nValues=nValues,
        title=r'Aproksymacja $\int_{0}^{\pi} \sin(x) dx$',
        filename='a2'
    )

    runAndPlot( # punkt a, podpunkt trzeci
        function=a3,
        a=0,
        b=1,
        M=0.5,
        exactValue=0.2,
        kValues=kValues,
        nValues=nValues,
        title=r'Aproksymacja $\int_{0}^{1} 4x(1-x)^3 dx$',
        filename='a3'
    )

    runAndPlot( # punkt b
        function=b,
        a=0,
        b=1,
        M=1,
        exactValue=np.pi,
        kValues=kValues,
        nValues=nValues,
        title=r'Aproksymacja $\pi$ - $4 \cdot \int_{0}^{1} \sqrt{1 - x^2} dx$',
        filename='b',
        multiplier=4.0
    )