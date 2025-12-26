package eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state;

public class OnState implements ApplianceStateBehavior {

	@Override
	public ApplianceState getState() {
		return ApplianceState.ON;
	}

	@Override
	public ApplianceStateBehavior start() {
		return ApplianceState.STARTED.getStateBehavior();
	}

	@Override
	public ApplianceStateBehavior stop() {
		return this;
	}

	@Override
	public ApplianceStateBehavior turnOn() {
		return this;
	}

	@Override
	public ApplianceStateBehavior turnOff() {
		return ApplianceState.OFF.getStateBehavior();
	}
}