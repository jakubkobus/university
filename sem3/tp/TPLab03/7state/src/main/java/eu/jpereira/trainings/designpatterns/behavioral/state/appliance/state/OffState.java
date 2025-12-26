package eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state;

public class OffState implements ApplianceStateBehavior {

	@Override
	public ApplianceState getState() {
		return ApplianceState.OFF;
	}

	@Override
	public ApplianceStateBehavior start() {
		return this;
	}

	@Override
	public ApplianceStateBehavior stop() {
		return this;
	}

	@Override
	public ApplianceStateBehavior turnOn() {
		return ApplianceState.ON.getStateBehavior();
	}

	@Override
	public ApplianceStateBehavior turnOff() {
		return this;
	}
}