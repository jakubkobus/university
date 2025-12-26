package eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state;

public enum ApplianceState {

	OFF {
		@Override
		public ApplianceStateBehavior getStateBehavior() {
			return new OffState();
		}
	},
	ON {
		@Override
		public ApplianceStateBehavior getStateBehavior() {
			return new OnState();
		}
	},
	STOPPED {
		@Override
		public ApplianceStateBehavior getStateBehavior() {
			return new StoppedState();
		}
	},
	STARTED {
		@Override
		public ApplianceStateBehavior getStateBehavior() {
			return new StartedState();
		}
	},
	UNKNOW {
		@Override
		public ApplianceStateBehavior getStateBehavior() {
			return new UnknowState();
		}
	};

	/**
	 * Default method meant to be overridden by enum constants
	 * @return
	 */
	public ApplianceStateBehavior getStateBehavior() {
		return null;
	}
}