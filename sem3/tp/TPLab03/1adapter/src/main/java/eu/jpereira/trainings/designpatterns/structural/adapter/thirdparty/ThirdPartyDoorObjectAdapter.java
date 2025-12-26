package eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty;

import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.CodeMismatchException;
import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.IncorrectDoorCodeException;
import eu.jpereira.trainings.designpatterns.structural.adapter.model.Door;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotChangeCodeForUnlockedDoor;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotChangeStateOfLockedDoor;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotUnlockDoorException;

public class ThirdPartyDoorObjectAdapter implements Door {

    private ThirdPartyDoor delegate = new ThirdPartyDoor();

    @Override
    public void open(String code) throws IncorrectDoorCodeException {
        try {
            delegate.unlock(code);
            delegate.setState(ThirdPartyDoor.DoorState.OPEN);
        } catch (CannotUnlockDoorException e) {
            throw new IncorrectDoorCodeException();
        } catch (CannotChangeStateOfLockedDoor e) {
            throw new IncorrectDoorCodeException();
        }
    }

    @Override
    public void close() {
        try {
            delegate.setState(ThirdPartyDoor.DoorState.CLOSED);
            delegate.lock();
        } catch (CannotChangeStateOfLockedDoor e) {}
    }

    @Override
    public boolean isOpen() {
        return delegate.getState().equals(ThirdPartyDoor.DoorState.OPEN);
    }

    @Override
    public void changeCode(String oldCode, String newCode, String newCodeConfirmation)
            throws IncorrectDoorCodeException, CodeMismatchException {
        
        if (!newCode.equals(newCodeConfirmation)) {
            throw new CodeMismatchException();
        }

        try {
            delegate.unlock(oldCode);
            delegate.setNewLockCode(newCode);
            delegate.lock();
        } catch (CannotUnlockDoorException e) {
            throw new IncorrectDoorCodeException();
        } catch (CannotChangeCodeForUnlockedDoor e) {
            throw new IncorrectDoorCodeException();
        }
    }

    @Override
    public boolean testCode(String code) {
        try {
            delegate.unlock(code);
            delegate.lock();
            return true;
        } catch (CannotUnlockDoorException e) {
            return false;
        }
    }
}