/*M!999999\- enable the sandbox mode */ 
-- MariaDB dump 10.19-12.1.2-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: dblab3
-- ------------------------------------------------------
-- Server version	12.1.2-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `Ludzie`
--

DROP TABLE IF EXISTS `Ludzie`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Ludzie` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `PESEL` char(11) NOT NULL,
  `imie` varchar(30) NOT NULL,
  `nazwisko` varchar(30) NOT NULL,
  `data_urodzenia` date NOT NULL,
  `plec` enum('K','M') NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `PESEL` (`PESEL`),
  KEY `index_ludzie_plec_imie` (`plec`,`imie`),
  CONSTRAINT `check_pesel_length` CHECK (octet_length(`PESEL`) = 11),
  CONSTRAINT `check_pesel_numeric` CHECK (`PESEL` regexp '^[0-9]+$')
) ENGINE=InnoDB AUTO_INCREMENT=56 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Ludzie`
--

LOCK TABLES `Ludzie` WRITE;
/*!40000 ALTER TABLE `Ludzie` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `Ludzie` VALUES
(1,'10250500123','Zofia','Kaczmarek','2010-05-05','K'),
(2,'12211200321','Kacper','Piotrowski','2012-01-12','M'),
(3,'09280800444','Maja','Wróblewska','2009-08-08','K'),
(4,'15220200555','Filip','Jaworski','2015-02-02','M'),
(5,'11260600666','Lena','Dudek','2011-06-06','K'),
(6,'80010111111','Jan','Kowalski','1980-01-01','M'),
(7,'85050522222','Anna','Nowak','1985-05-05','K'),
(8,'90121233333','Piotr','Wiśniewski','1990-12-12','M'),
(9,'95031544444','Maria','Wójcik','1995-03-15','K'),
(10,'75072055555','Paweł','Kamiński','1975-07-20','M'),
(11,'82080866666','Krzysztof','Lewandowski','1982-08-08','M'),
(12,'88090977777','Agnieszka','Zielińska','1988-09-09','K'),
(13,'92101088888','Tomasz','Szymański','1992-10-10','M'),
(14,'70111199999','Barbara','Woźniak','1970-11-11','K'),
(15,'78121200000','Marek','Dąbrowski','1978-12-12','M'),
(16,'83011311111','Ewa','Kozłowska','1983-01-13','K'),
(17,'91021422222','Adam','Jankowski','1991-02-14','M'),
(18,'96031533333','Magdalena','Mazur','1996-03-15','K'),
(19,'76041644444','Rafał','Kwiatkowski','1976-04-16','M'),
(20,'89051755555','Joanna','Krawczyk','1989-05-17','K'),
(21,'93061866666','Marcin','Piotrowski','1993-06-18','M'),
(22,'71071977777','Monika','Grabowska','1971-07-19','K'),
(23,'79082088888','Wojciech','Nowakowski','1979-08-20','M'),
(24,'84092199999','Katarzyna','Pawłowska','1984-09-21','K'),
(25,'90102200001','Łukasz','Michalski','1990-10-22','M'),
(26,'97112311112','Aleksandra','Król','1997-11-23','K'),
(27,'74122422223','Grzegorz','Wieczorek','1974-12-24','M'),
(28,'87012533334','Dorota','Jabłońska','1987-01-25','K'),
(29,'94022644445','Michał','Wróbel','1994-02-26','M'),
(30,'69032755556','Karolina','Majewska','1969-03-27','K'),
(31,'81042866667','Jakub','Olszewski','1981-04-28','M'),
(32,'86052977778','Natalia','Stępień','1986-05-29','K'),
(33,'98063088889','Szymon','Malinowski','1998-06-30','M'),
(34,'72070199990','Marta','Górska','1972-07-01','K'),
(35,'77080200001','Bartosz','Witkowski','1977-08-02','M'),
(36,'95090311112','Patrycja','Walczak','1995-09-03','K'),
(37,'99100422223','Sebastian','Baran','1999-10-04','M'),
(38,'68110533334','Alicja','Rutkowska','1968-11-05','K'),
(39,'82120644445','Mateusz','Michalak','1982-12-06','M'),
(40,'88010755556','Sylwia','Szewczyk','1988-01-07','K'),
(41,'92020866667','Daniel','Ostrowski','1992-02-08','M'),
(42,'75030977778','Kinga','Tomaszewska','1975-03-09','K'),
(43,'80041088889','Przemysław','Pietrzak','1980-04-10','M'),
(44,'85051199990','Beata','Duda','1985-05-11','K'),
(45,'91061200001','Artur','Zając','1991-06-12','M'),
(46,'76071311112','Iwona','Wróblewska','1976-07-13','K'),
(47,'83081422223','Robert','Jasiński','1983-08-14','M'),
(48,'96091533334','Paulina','Marciniak','1996-09-15','K'),
(49,'79101644445','Kamil','Sadowski','1979-10-16','M'),
(50,'71111755556','Elżbieta','Bąk','1971-11-17','K'),
(51,'50010199999','Stanisław','Górski','1950-01-01','M'),
(52,'48050588888','Krystyna','Pawlak','1948-05-05','K'),
(53,'55121277777','Jerzy','Sikora','1955-12-12','M'),
(54,'60031566666','Danuta','Baran','1960-03-15','K'),
(55,'62072055555','Tadeusz','Krajewski','1962-07-20','M');
/*!40000 ALTER TABLE `Ludzie` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `Pracownicy`
--

DROP TABLE IF EXISTS `Pracownicy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Pracownicy` (
  `pracownik_id` int(11) NOT NULL AUTO_INCREMENT,
  `osoba_id` int(11) NOT NULL,
  `zawod_id` int(11) NOT NULL,
  `pensja` float NOT NULL,
  PRIMARY KEY (`pracownik_id`),
  KEY `osoba_id` (`osoba_id`),
  KEY `zawod_id` (`zawod_id`),
  KEY `index_pracownicy_pensja` (`pensja`),
  CONSTRAINT `1` FOREIGN KEY (`osoba_id`) REFERENCES `Ludzie` (`id`),
  CONSTRAINT `2` FOREIGN KEY (`zawod_id`) REFERENCES `Zawody` (`zawod_id`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pracownicy`
--

LOCK TABLES `Pracownicy` WRITE;
/*!40000 ALTER TABLE `Pracownicy` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `Pracownicy` VALUES
(1,6,3,11158.8),
(2,7,3,23450.8),
(3,8,3,24135.6),
(4,9,1,27209.3),
(5,10,4,13566.5),
(6,11,2,6324.48),
(7,12,3,21070.8),
(8,13,1,18423.9),
(9,14,2,7468.31),
(10,15,3,18856),
(11,16,4,16997),
(12,17,1,18848.9),
(13,18,2,4559.57),
(14,19,2,6146.21),
(15,20,4,8967.74),
(16,21,3,17141),
(17,22,3,21153.6),
(18,23,4,17942.8),
(19,24,4,11203.8),
(20,25,2,5346.95),
(21,26,2,7383.48),
(22,27,3,23461.5),
(23,28,4,12617.3),
(24,29,4,17843.9),
(25,30,3,22118.6),
(26,31,1,29359.7),
(27,32,3,24118.7),
(28,33,1,16925.6),
(29,34,2,6432.31),
(30,35,3,20858.9),
(31,36,1,26902.5),
(32,37,1,13076.8),
(33,38,4,15594.2),
(34,39,3,16717.5),
(35,40,4,19955.3),
(36,41,2,6094.05),
(37,42,1,19135.5),
(38,43,4,8061.19),
(39,44,1,16132.3),
(40,45,3,9589.34),
(41,46,4,14871.6),
(42,47,2,6479.75),
(43,48,3,21133.7),
(44,49,1,12580.1),
(45,50,4,17019.5),
(46,51,1,23970.2),
(47,52,2,5929.19),
(48,53,4,12827.5),
(49,54,4,10271.4),
(50,55,3,15525);
/*!40000 ALTER TABLE `Pracownicy` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `Zawody`
--

DROP TABLE IF EXISTS `Zawody`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Zawody` (
  `zawod_id` int(11) NOT NULL,
  `nazwa` varchar(50) NOT NULL,
  `pensja_min` float NOT NULL,
  `pensja_max` float NOT NULL,
  PRIMARY KEY (`zawod_id`),
  CONSTRAINT `check_pensja_gt_zero` CHECK (`pensja_min` > 0 and `pensja_max` > 0),
  CONSTRAINT `check_pensja_min_lt_max` CHECK (`pensja_min` < `pensja_max`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Zawody`
--

LOCK TABLES `Zawody` WRITE;
/*!40000 ALTER TABLE `Zawody` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `Zawody` VALUES
(1,'Polityk',12000,30000),
(2,'Nauczyciel',4000,7500),
(3,'Lekarz',9000,25000),
(4,'Informatyk',6000,20000);
/*!40000 ALTER TABLE `Zawody` ENABLE KEYS */;
UNLOCK TABLES;
commit;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2025-12-13 14:32:47
