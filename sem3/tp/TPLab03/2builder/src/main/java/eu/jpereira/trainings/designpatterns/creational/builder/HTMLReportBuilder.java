package eu.jpereira.trainings.designpatterns.creational.builder;

import java.util.Iterator;
import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SaleEntry;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SoldItem;

public class HTMLReportBuilder implements ReportBuilder {

    private HTMLReportBody reportBody;
    private Report report;
    private SaleEntry saleEntry;

    public HTMLReportBuilder(SaleEntry saleEntry) {
        this.saleEntry = saleEntry;
        this.report = new Report();
    }

    @Override
    public void buildReportBody() {
        reportBody = new HTMLReportBody();
        reportBody.putContent("<span class=\"customerName\">");
        reportBody.putContent(this.saleEntry.getCustomer().getName());
        reportBody.putContent("</span><span class=\"customerPhone\">");
        reportBody.putContent(this.saleEntry.getCustomer().getPhone());
        reportBody.putContent("</span>");
        
        reportBody.putContent("<items>");
        
        Iterator<SoldItem> it = saleEntry.getSoldItems().iterator();
        while (it.hasNext()) {
            SoldItem soldEntry = it.next();
            reportBody.putContent("<item><name>");
            reportBody.putContent(soldEntry.getName());
            reportBody.putContent("</name><quantity>");
            reportBody.putContent(soldEntry.getQuantity());
            reportBody.putContent("</quantity><price>");
            reportBody.putContent(soldEntry.getUnitPrice());
            reportBody.putContent("</price></item>");
        }
        reportBody.putContent("</items>");
        
        report.setReportBody(reportBody);
    }

    @Override
    public Report getReport() {
        return report;
    }
}