package eu.jpereira.trainings.designpatterns.creational.factorymethod;

public abstract class ReportGenerator {

	public Report generateReport(ReportData data) {
		Report generatedReport = createReport();
		
		if (generatedReport != null) {
			generatedReport.generateReport(data);
		}

		return generatedReport;
	}


	protected abstract Report createReport();
}