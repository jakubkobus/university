package eu.jpereira.trainings.designpatterns.structural.decorator.channel.decorator;

import eu.jpereira.trainings.designpatterns.structural.decorator.channel.SocialChannel;

public class WordCensor extends SocialChannelDecorator {

    private String wordToCensor;

    public WordCensor(String wordToCensor) {
        this.wordToCensor = wordToCensor;
    }

    public WordCensor(String wordToCensor, SocialChannel delegate) {
        this.wordToCensor = wordToCensor;
        this.delegate = delegate;
    }

    @Override
    public void deliverMessage(String message) {
        if (message.contains(wordToCensor)) {
            message = message.replaceAll(wordToCensor, "###");
        }
        delegate.deliverMessage(message);
    }
}