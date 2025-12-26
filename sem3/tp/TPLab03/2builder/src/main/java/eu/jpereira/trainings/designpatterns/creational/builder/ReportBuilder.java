package eu.jpereira.trainings.designpatterns.creational.builder;

import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;

public interface ReportBuilder {
    void buildReportBody();
    Report getReport();
}