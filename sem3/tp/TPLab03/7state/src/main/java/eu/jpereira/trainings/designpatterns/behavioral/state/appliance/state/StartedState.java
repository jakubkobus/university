package eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state;

public class StartedState implements ApplianceStateBehavior {

	@Override
	public ApplianceState getState() {
		return ApplianceState.STARTED;
	}

	@Override
	public ApplianceStateBehavior start() {
		// Już działa
		return this;
	}

	@Override
	public ApplianceStateBehavior stop() {
		// Przejście STARTED -> STOPPED
		return ApplianceState.STOPPED.getStateBehavior();
	}

	@Override
	public ApplianceStateBehavior turnOn() {
		return this;
	}

	@Override
	public ApplianceStateBehavior turnOff() {
		// W tej logice nie pozwalamy wyłączyć wtyczki podczas pracy
		return this;
	}
}