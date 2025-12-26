import java.util.Random;

/**
 * @file Animal.java
 * @brief Abstrakcyjna klasa bazowa dla zwierząt (Wilk i Królik).
 *
 * Klasa Animal definiuje wspólne właściwości i metody dla wszystkich zwierząt występujących na planszy.
 * Przechowuje pozycję zwierzęcia, referencję do planszy, parametr k oraz generator liczb losowych.
 * Umożliwia zarządzanie stanem zawieszenia oraz pozycją zwierzęcia.
 *
 * @author Jakub Kobus 283969
 */
abstract class Animal extends Thread {
    protected int x, y;
    protected final Board board;
    protected final int k;
    protected final Random random;
    protected volatile boolean suspended = false;
    protected volatile int restCycles = 0;

    /**
     * Konstruktor klasy Animal.
     *
     * @param x Początkowa współrzędna wiersza.
     * @param y Początkowa współrzędna kolumny.
     * @param board Referencja do planszy.
     * @param k Parametr sterujący (np. czas życia, opóźnienie).
     * @param random Generator liczb losowych.
     */
    public Animal(int x, int y, Board board, int k, Random random) {
        this.x = x;
        this.y = y;
        this.board = board;
        this.k = k;
        this.random = random;
    }

    /**
     * Zwraca bieżącą współrzędną wiersza zwierzęcia.
     *
     * @return Wiersz (x).
     */
    public int getX() {
        return x;
    }

    /**
     * Zwraca bieżącą współrzędną kolumny zwierzęcia.
     *
     * @return Kolumna (y).
     */
    public int getY() {
        return y;
    }

    /**
     * Ustawia nową pozycję zwierzęcia na planszy.
     *
     * @param x Nowa współrzędna wiersza.
     * @param y Nowa współrzędna kolumny.
     */
    public void setPosition(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Ustawia stan zawieszenia zwierzęcia.
     *
     * @param suspended true jeśli zwierzę ma być zawieszone, false w przeciwnym razie.
     */
    public void setSuspended(boolean suspended) {
        this.suspended = suspended;
    }

    /**
     * Sprawdza, czy zwierzę jest zawieszone.
     *
     * @return true jeśli zwierzę jest zawieszone, false w przeciwnym razie.
     */
    public boolean isSuspended() {
        return suspended;
    }

    /**
     * Zwraca opóźnienie (czas odpoczynku) dla zwierzęcia na podstawie parametru k i losowości.
     *
     * @return Opóźnienie w milisekundach.
     */
    protected int getDelay() {
        return (int)(k * (0.5 + random.nextFloat()));
    }
}