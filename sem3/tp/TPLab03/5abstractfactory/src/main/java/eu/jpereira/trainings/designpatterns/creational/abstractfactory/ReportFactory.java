package eu.jpereira.trainings.designpatterns.creational.abstractfactory;

public interface ReportFactory {
	ReportBody createBody();
	ReportHeader createHeader();
	ReportFooter createFooter();
}