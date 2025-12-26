#!/bin/bash
javadoc --module-path /opt/javafx-sdk-22.0.1/lib --add-modules javafx.controls,javafx.fxml -d javadoc -encoding UTF-8 -docencoding UTF-8 -charset UTF-8 *.java
doxygen Doxyfile