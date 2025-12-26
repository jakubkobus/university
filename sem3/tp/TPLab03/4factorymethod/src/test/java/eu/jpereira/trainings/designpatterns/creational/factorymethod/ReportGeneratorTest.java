package eu.jpereira.trainings.designpatterns.creational.factorymethod;

import static org.junit.Assert.*;
import org.junit.Test;

public class ReportGeneratorTest extends AbstractReportingTest {

	@Test
	public void testCreateJSONReport() {
		ReportData reportData = createDummyReportData();
		ReportGenerator generator = new JSONReportGenerator();
		Report generatedReport = generator.generateReport(reportData);
		assertEquals("JSON Report. Name: " + reportData.getName(), generatedReport.getReportContent());
	}

	@Test
	public void testCreateXMLReport() {
		ReportData reportData = createDummyReportData();
		ReportGenerator generator = new XMLReportGenerator();
		Report generatedReport = generator.generateReport(reportData);
		assertEquals("XML Report. Name: " + reportData.getName(), generatedReport.getReportContent());
	}

	@Test
	public void testCreateHTMLReport() {
		ReportData reportData = createDummyReportData();
		ReportGenerator generator = new HTMLReportGenerator();
		Report generatedReport = generator.generateReport(reportData);
		assertEquals("HTML Report. Name: " + reportData.getName(), generatedReport.getReportContent());
	}

	@Test
	public void testCreatePDFReport() {
		ReportData reportData = createDummyReportData();
		ReportGenerator generator = new PDFReportGenerator();
		Report generatedReport = generator.generateReport(reportData);
		assertEquals("PDF Report. Name: " + reportData.getName(), generatedReport.getReportContent());
	}
}