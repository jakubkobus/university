# wget https://download2.gluonhq.com/openjfx/17.0.2/openjfx-17.0.2_linux-x64_bin-sdk.zip
# unzip openjfx-17.0.2_linux-x64_bin-sdk.zip
# sudo mv javafx-sdk-17.0.2 /opt/

javac --module-path /opt/javafx-sdk-22.0.1/lib --add-modules javafx.controls -d bin-client Client.java
javac -d bin-client BinaryTree.java
java --module-path /opt/javafx-sdk-22.0.1/lib --add-modules javafx.controls -cp bin-client Client