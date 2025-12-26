package pt.trainings.maven.scratch;

import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.Test;

public class GreetingsTest {

    @Test
    public void testNullNameShouldPrintDefaultName() {
        Greetings objectUnderTest = new Greetings();
        String expectedString = "Hello John Doe";
        assertEquals(expectedString, objectUnderTest.sayHello(null));
    }

    @Test
    public void testShouldPrintCorrectGreeting() {
        Greetings objectUnderTest = new Greetings();
        String expectedString = "Hello Bob";
        assertEquals(expectedString, objectUnderTest.sayHello("Bob"));
    }
}