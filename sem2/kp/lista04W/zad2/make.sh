# wget https://download2.gluonhq.com/openjfx/17.0.2/openjfx-17.0.2_linux-x64_bin-sdk.zip
# unzip openjfx-17.0.2_linux-x64_bin-sdk.zip
# sudo mv javafx-sdk-17.0.2 /opt/

javac -d bin --module-path /opt/javafx-sdk-17.0.2/lib --add-modules javafx.controls TrojkatPascalaFX.java
java -cp bin --module-path /opt/javafx-sdk-17.0.2/lib --add-modules javafx.controls TrojkatPascalaFX