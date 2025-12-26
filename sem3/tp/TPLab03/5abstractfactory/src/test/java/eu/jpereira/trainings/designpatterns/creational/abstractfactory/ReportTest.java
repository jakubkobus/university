package eu.jpereira.trainings.designpatterns.creational.abstractfactory;

import org.junit.Test;
import static org.junit.Assert.*;

import eu.jpereira.trainings.designpatterns.creational.abstractfactory.json.JSONReportFactory;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml.XMLReportFactory;

public class ReportTest {

	@Test
	public void testCreateJSONReport() {
		// Używamy fabryki JSON
		Report report = new Report(new JSONReportFactory());
		assertEquals("JSON", report.getBody().getType());
		assertEquals("JSON", report.getHeader().getType());
		assertEquals("JSON", report.getFooter().getType());
	}

	@Test
	public void testCreateXMLReport() {
		// Używamy fabryki XML
		Report report = new Report(new XMLReportFactory());
		assertEquals("XML", report.getBody().getType());
		assertEquals("XML", report.getHeader().getType());
		assertEquals("XML", report.getFooter().getType());
	}
}