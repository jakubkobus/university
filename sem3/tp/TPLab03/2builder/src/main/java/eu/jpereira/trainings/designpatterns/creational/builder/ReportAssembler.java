package eu.jpereira.trainings.designpatterns.creational.builder;

import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;

public class ReportAssembler {

    public Report assembleReport(ReportBuilder builder) {
        builder.buildReportBody();
        return builder.getReport();
    }
}