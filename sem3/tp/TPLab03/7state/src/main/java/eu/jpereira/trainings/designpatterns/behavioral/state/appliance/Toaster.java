package eu.jpereira.trainings.designpatterns.behavioral.state.appliance;

import eu.jpereira.trainings.designpatterns.behavioral.state.appliance.snapshot.Snapshot;
import eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state.ApplianceState;

public class Toaster extends AbstractAppliance {

	public Toaster(ApplianceState initialState) {
		super(initialState);
	}

	@Override
	public Snapshot takeSnapshot() {
		return null;
	}

	@Override
	public void restoreFromSnapshot(Snapshot snapshot) {
	}

	@Override
	public void turnOn() throws ApplianceCommunicationException {
		this.applianceStateBehavior = this.applianceStateBehavior.turnOn();
	}

	@Override
	public void turnOff() throws ApplianceCommunicationException {
		this.applianceStateBehavior = this.applianceStateBehavior.turnOff();
	}

	@Override
	public void start() throws ApplianceCommunicationException {
		this.applianceStateBehavior = this.applianceStateBehavior.start();
	}

	@Override
	public void stop() throws ApplianceCommunicationException {
		this.applianceStateBehavior = this.applianceStateBehavior.stop();
	}
}