package eu.jpereira.trainings.designpatterns.structural.decorator.channel.decorator;

import static org.junit.Assert.assertEquals;
import org.junit.Test;

import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannel;
import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannelBuilder;
import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannelProperties;
import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannelPropertyKey;
import eu.jpereira.trainings.designpatterns.structural.decorator.channel.spy.TestSpySocialChannel;

public class ChainCensorDecoratorTest extends AbstractSocialChanneldDecoratorTest {

    @Test
    public void testChainCensorAndTruncator() {
        // Tworzymy buildera
        SocialChannelBuilder builder = createTestSpySocialChannelBuilder();

        // Właściwości
        SocialChannelProperties props = new SocialChannelProperties().putProperty(SocialChannelPropertyKey.NAME,
                TestSpySocialChannel.NAME);

        // Łańcuch: Najpierw Cenzor, potem Przycinanie (Truncator)
        // UWAGA: Builder używa stosu.
        // 1. push(Censor)
        // 2. push(Truncator)
        // Pop(Truncator) -> wrapuje kanał bazowy
        // Pop(Censor) -> wrapuje Truncator
        // Wynikowy łańcuch wywołań (od zewnątrz): Censor -> Truncator -> Kanał
        SocialChannel channel = builder
                .with(new WordCensor("Microsoft"))
                .with(new MessageTruncator(20))
                .getDecoratedChannel(props);

        // Wiadomość: "Microsoft Windows is great!!" (28 znaków)
        // 1. Cenzor zamieni "Microsoft" -> "### Windows is great!!" (22 znaki)
        // 2. Truncator (limit 20) przytnie do 17 znaków + "..." -> "### Windows is
        // gr..."
        channel.deliverMessage("Microsoft Windows is great!!");

        TestSpySocialChannel spyChannel = (TestSpySocialChannel) builder.buildChannel(props);

        // POPRAWIONA OCZEKIWANA WARTOŚĆ
        assertEquals("### Windows is gr...", spyChannel.lastMessagePublished());
    }

    @Test
    public void testChainCensorAndURLAppender() {
        SocialChannelBuilder builder = createTestSpySocialChannelBuilder();
        SocialChannelProperties props = new SocialChannelProperties().putProperty(SocialChannelPropertyKey.NAME,
                TestSpySocialChannel.NAME);

        // Łańcuch: Cenzor + URL Appender
        SocialChannel channel = builder
                .with(new URLAppender("http://jpereira.eu"))
                .with(new WordCensor("Microsoft"))
                .getDecoratedChannel(props);

        channel.deliverMessage("I like Microsoft");

        TestSpySocialChannel spyChannel = (TestSpySocialChannel) builder.buildChannel(props);

        // Oczekiwany efekt: Cenzura + Doklejenie URL
        assertEquals("I like ### http://jpereira.eu", spyChannel.lastMessagePublished());
    }
}