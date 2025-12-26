CREATE DATABASE IF NOT EXISTS tplab_faktura CHARACTER
SET
  utf8mb4 COLLATE utf8mb4_polish_ci;

CREATE USER IF NOT EXISTS 'fv_admin'@'localhost' IDENTIFIED BY 'fv_password';
GRANT ALL PRIVILEGES ON tplab_faktura.* TO 'fv_admin'@'localhost';
FLUSH PRIVILEGES;

USE tplab_faktura;

CREATE TABLE
  IF NOT EXISTS customers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    nip VARCHAR(50)
  ) ENGINE = InnoDB;

CREATE TABLE
  IF NOT EXISTS items (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL UNIQUE
  ) ENGINE = InnoDB;

CREATE TABLE
  IF NOT EXISTS invoices (
    id INT AUTO_INCREMENT PRIMARY KEY,
    number VARCHAR(100) NOT NULL UNIQUE,
    total DECIMAL(10, 2) NOT NULL,
    customer_id INT NOT NULL,
    CONSTRAINT fk_invoice_customer FOREIGN KEY (customer_id) REFERENCES customers (id) ON DELETE RESTRICT ON UPDATE CASCADE
  ) ENGINE = InnoDB;

CREATE TABLE
  IF NOT EXISTS invoice_lines (
    id INT AUTO_INCREMENT PRIMARY KEY,
    invoice_id INT NOT NULL,
    item_id INT NOT NULL,
    quantity INT NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    CONSTRAINT fk_line_invoice FOREIGN KEY (invoice_id) REFERENCES invoices (id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_line_item FOREIGN KEY (item_id) REFERENCES items (id) ON DELETE RESTRICT ON UPDATE CASCADE
  ) ENGINE = InnoDB;

INSERT INTO
  customers (name, nip)
VALUES
  ('Firma A', '111-222-33-44'),
  ('Firma B', '555-666-77-88'),
  ('Firma C', '999-000-11-22'),
  ('Firma D', '333-444-55-66'),
  ('Firma E', '777-888-99-00');

INSERT INTO
  items (name)
VALUES
  ('Komputer'),
  ('Monitor'),
  ('Klawiatura'),
  ('Myszka'),
  ('Drukarka'),
  ('Router'),
  ('Smartfon'),
  ('Tablet'),
  ('Słuchawki'),
  ('Głośniki');