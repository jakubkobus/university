package eu.jpereira.trainings.designpatterns.creational.builder;

import static org.junit.Assert.assertEquals;
import org.junit.Test;

import eu.jpereira.trainings.designpatterns.creational.builder.json.JSONReportBuilder;
import eu.jpereira.trainings.designpatterns.creational.builder.xml.XMLReportBuilder;
import eu.jpereira.trainings.designpatterns.creational.builder.model.Customer;
import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SaleEntry;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SoldItem;

public class ReportAssemblerTest {

    @Test
    public void testAssembleJSONReportBody() {
        ReportAssembler assembler = new ReportAssembler();
        SaleEntry saleEntry = createDummySaleEntry();
        ReportBuilder builder = new JSONReportBuilder(saleEntry);
        
        Report report = assembler.assembleReport(builder);
        
        String expected = "sale:{customer:{name:\"Bob\",phone:\"1232232\"},items:[{name:\"Computer\",quantity:2,price:99.9},{name:\"Printer\",quantity:1,price:79.8}]}";
        assertEquals(expected, report.getAsString());
    }

    @Test
    public void testAssembleXMLReportBody() {
        ReportAssembler assembler = new ReportAssembler();
        SaleEntry saleEntry = createDummySaleEntry();
        ReportBuilder builder = new XMLReportBuilder(saleEntry);
        
        Report report = assembler.assembleReport(builder);
        
        String expected = "<sale><customer><name>Bob</name><phone>1232232</phone></customer><items><item><name>Computer</name><quantity>2</quantity><price>99.9</price></item><item><name>Printer</name><quantity>1</quantity><price>79.8</price></item></items></sale>";
        assertEquals(expected, report.getAsString());
    }
    
    @Test
    public void testAssembleHTMLReportBody() {
        ReportAssembler assembler = new ReportAssembler();
        SaleEntry saleEntry = createDummySaleEntry();
        ReportBuilder builder = new HTMLReportBuilder(saleEntry);
        
        Report report = assembler.assembleReport(builder);
        
        String expected = "<span class=\"customerName\">Bob</span><span class=\"customerPhone\">1232232</span><items><item><name>Computer</name><quantity>2</quantity><price>99.9</price></item><item><name>Printer</name><quantity>1</quantity><price>79.8</price></item></items>";
        assertEquals(expected, report.getAsString());
    }

    private SaleEntry createDummySaleEntry() {
        SaleEntry saleEntry = new SaleEntry();
        saleEntry.setCustomer(new Customer("Bob", "1232232"));
        saleEntry.addSoldItem(new SoldItem("Computer", 2, 99.9));
        saleEntry.addSoldItem(new SoldItem("Printer", 1, 79.8));
        return saleEntry;
    }
}