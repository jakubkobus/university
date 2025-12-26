package eu.jpereira.trainings.designpatterns.structural.facade.facade;

import static org.mockito.Mockito.*;

import org.junit.Test;

import eu.jpereira.trainings.designpatterns.structural.facade.BookstoreFacade;
import eu.jpereira.trainings.designpatterns.structural.facade.DefaultBookStoreFacade;
import eu.jpereira.trainings.designpatterns.structural.facade.model.Book;
import eu.jpereira.trainings.designpatterns.structural.facade.model.Customer;
import eu.jpereira.trainings.designpatterns.structural.facade.model.DispatchReceipt;
import eu.jpereira.trainings.designpatterns.structural.facade.model.Order;

/**
 * @author windows
 * */
public class BookStoreFacadeTest extends AbstractClientTest {

	@Test
	public void testPlaceOrder() {
		// Dummy literals
		String isbn = "123";
		String customerId = "wall-e";
		Book dummyBook = new Book(isbn);
		Customer dummyCustomer = new Customer(customerId);
		Order dummyOrder = new Order();
		DispatchReceipt dummyDispatchReceipt = new DispatchReceipt();

		// prepate SUT
		BookstoreFacade facade = createFacade();

		// Prepare stubs
		when(bookService.findBookByISBN(isbn)).thenReturn(dummyBook);
		when(customerService.findCustomerById(customerId)).thenReturn(dummyCustomer);
		when(orderingService.createOrder(dummyCustomer, dummyBook)).thenReturn(dummyOrder);
		when(warehouseService.dispatch(dummyOrder)).thenReturn(dummyDispatchReceipt);

		// Exercise SUT
		facade.placeOrder(customerId, isbn);

		// Verify behavior
		verify(warehouseService).dispatch(dummyOrder);
		verify(customerNotificationService).notifyClient(dummyDispatchReceipt);

	}

	/**
	 * @return
	 */
	protected BookstoreFacade createFacade() {
		DefaultBookStoreFacade facade = new DefaultBookStoreFacade();
		
		facade.setBookService(this.bookService);
		facade.setCustomerService(this.customerService);
		facade.setOrderingService(this.orderingService);
		facade.setWarehouseService(this.warehouseService);
		facade.setCustomerNotificationService(this.customerNotificationService);
		
		return facade;
	}
}