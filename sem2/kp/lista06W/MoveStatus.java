/**
 * @file MoveStatus.java
 * @brief Enum opisujący status ruchu zwierzęcia na planszy.
 *
 * Enum MoveStatus określa możliwe rezultaty wykonania ruchu przez zwierzę na planszy:
 * - INVALID: ruch jest niepoprawny (np. poza planszę lub na zajęte pole),
 * - MOVED: ruch został wykonany poprawnie,
 * - CAUGHT_RABBIT: wilk złapał (zjadł) królika.
 *
 * @author Jakub Kobus 283969
 */
public enum MoveStatus {
  INVALID, MOVED, CAUGHT_RABBIT
}