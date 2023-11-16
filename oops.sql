create database if not exists oops;
use oops ;
SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";

--
-- Database: `oops`
--

--
-- Table structure for table `musicinfo_db`
--
drop table if exists `musicinfo_db`;
CREATE TABLE `musicinfo_db`
(
    `id`       int(11) NOT NULL,
    `type`     varchar(100)  DEFAULT '0',
    `instrument`     varchar(100)  NOT NULL DEFAULT '0',
    `brand`   varchar(100)  NOT NULL DEFAULT '0',
    `price`   int(11)  NOT NULL DEFAULT '0',
    `quantity` int(11)  NOT NULL DEFAULT '0'
)

ENGINE = InnoDB DEFAULT CHARSET = latin1;

--
-- Dumping data for table `musicinfo_db`
--

INSERT INTO `musicinfo_db`
(
    `id`,`type`,`instrument`,`brand`,`price`,`quantity`
)
VALUES
(1,  'Percussion', 'Piano', 'Yamaha','3000','25'), 
(2, 'Stringed','violin','Jay Haide','3000','35'),
(3, 'Electronic','Guitar','Henrix','3500','40'),
(4,'Windwoods','Flute','Yamaha','2000','15');


--
-- Table structure for table `solditem_db`
--
drop table if exists `solditem_db`;
CREATE TABLE `solditem_db`
(
    `id`       int(11) NOT NULL,
    `type`     varchar(100)  DEFAULT '0',
    `instrument`     varchar(100)  NOT NULL DEFAULT '0',
    `brand`   varchar(100)  NOT NULL DEFAULT '0',
    `price`    int(11)  NOT NULL DEFAULT '0',
    `quantity` int(11)  NOT NULL DEFAULT '0'
     
)

ENGINE= InnoDB DEFAULT CHARSET= latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `solditem_db`
--

INSERT INTO `solditem_db`
(
    `id`,`type`,`instrument`,`brand`,`price`,`quantity`
)
VALUES
(1, 'Electronic',  'Guitar', 'Henrix','3500','2'),
(2, 'Woodwinds', 'Flute', 'Yamaha','2500','3'),
(3, 'Brass', 'Trumpet','Vincent Bach','3500','1'),
(4, 'Percussion', 'Drums', 'Tama','4500','3');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `musicinfo_db`
--

ALTER TABLE `musicinfo_db`
ADD PRIMARY KEY(`id`);

--
-- Indexes for table `solditem_db`
--

ALTER TABLE `solditem_db`
ADD PRIMARY KEY (`id`);
--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `musicinfo_db`
--

ALTER TABLE `musicinfo_db`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `solditem_db`
--

ALTER TABLE `solditem_db`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;

COMMIT;


