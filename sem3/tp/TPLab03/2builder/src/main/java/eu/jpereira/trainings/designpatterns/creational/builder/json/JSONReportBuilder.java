package eu.jpereira.trainings.designpatterns.creational.builder.json;

import java.util.Iterator;
import eu.jpereira.trainings.designpatterns.creational.builder.ReportBuilder;
import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SaleEntry;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SoldItem;

public class JSONReportBuilder implements ReportBuilder {

    private JSONReportBody reportBody;
    private Report report;
    private SaleEntry saleEntry;

    public JSONReportBuilder(SaleEntry saleEntry) {
        this.saleEntry = saleEntry;
        this.report = new Report();
    }

    @Override
    public void buildReportBody() {
        reportBody = new JSONReportBody();
        reportBody.addContent("sale:{customer:{");
        reportBody.addContent("name:\"");
        reportBody.addContent(saleEntry.getCustomer().getName());
        reportBody.addContent("\",phone:\"");
        reportBody.addContent(saleEntry.getCustomer().getPhone());
        reportBody.addContent("\"}");
        
        reportBody.addContent(",items:[");
        Iterator<SoldItem> it = saleEntry.getSoldItems().iterator();
        while (it.hasNext()) {
            SoldItem item = it.next();
            reportBody.addContent("{name:\"");
            reportBody.addContent(item.getName());
            reportBody.addContent("\",quantity:");
            reportBody.addContent(String.valueOf(item.getQuantity()));
            reportBody.addContent(",price:");
            reportBody.addContent(String.valueOf(item.getUnitPrice()));
            reportBody.addContent("}");
            if (it.hasNext()) {
                reportBody.addContent(",");
            }
        }
        reportBody.addContent("]}");
        
        report.setReportBody(reportBody);
    }

    @Override
    public Report getReport() {
        return report;
    }
}