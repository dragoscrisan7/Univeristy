Use ExamExample
Go

--1)
Drop table country_mountain_range_system
Drop table country_river
Drop table countries
Drop table peaks
Drop table rivers
Drop table mountain_groups
Drop table mountain_range_systems
go

CREATE TABLE countries (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    area INT,
    population INT
)

CREATE TABLE mountain_range_systems (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    length INT
)

CREATE TABLE mountain_groups (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    mountain_range_system_id INT,
    FOREIGN KEY (mountain_range_system_id) REFERENCES mountain_range_systems(id)
)

CREATE TABLE peaks (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    height INT,
    latitude REAL,
    longitude REAL,
    mountain_group_id INT,
    FOREIGN KEY (mountain_group_id) REFERENCES mountain_groups(id)
)

CREATE TABLE rivers (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    length INT,
    basin_area REAL
)

CREATE TABLE country_mountain_range_system (
    country_id INT,
    mountain_range_system_id INT,
    PRIMARY KEY (country_id, mountain_range_system_id),
    FOREIGN KEY (country_id) REFERENCES countries(id),
    FOREIGN KEY (mountain_range_system_id) REFERENCES mountain_range_systems(id)
)

CREATE TABLE country_river (
    country_id INT,
    river_id INT,
    PRIMARY KEY (country_id, river_id),
    FOREIGN KEY (country_id) REFERENCES countries(id),
    FOREIGN KEY (river_id) REFERENCES rivers(id)
)
Go

INSERT INTO countries (id, name, area, population) 
VALUES (1, 'Country A', 1000000, 5000000),(2, 'Country B', 2000000, 7000000),
(3, 'Country C', 3000000, 10000000);

INSERT INTO mountain_range_systems (id, name, length) 
VALUES (1, 'Mountain range A', 1500), (2, 'Mountain range B', 2000),
(3, 'Mountain range C', 2500);

INSERT INTO mountain_groups (id, name, mountain_range_system_id) 
VALUES (1, 'Mountain group A', 1), (2, 'Mountain group B', 1), (3, 'Mountain group C', 2);

INSERT INTO peaks (id, name, height, latitude, longitude, mountain_group_id) 
VALUES (1, 'Peak A', 4000, -20.5, 30.5, 1), (2, 'Peak B', 4500, -20.6, 30.6, 1),
(3, 'Peak C', 4600, -20.7, 30.7, 2), (4, 'Peak D', 4200, -20.8, 30.8, 2),
(5, 'Peak E', 4800, -20.9, 30.9, 3);

INSERT INTO rivers (id, name, length, basin_area) 
VALUES (1, 'River A', 800, 120000),(2, 'River B', 1000, 150000), (3, 'River C', 1200, 180000);

INSERT INTO country_mountain_range_system (country_id, mountain_range_system_id) 
VALUES (1, 1), (1, 2), (2, 1), (2, 3);

INSERT INTO country_river(country_id, river_id) 
Values (3,2), (2,1), (2,2), (3,3)

Select *
From countries

Select *
From mountain_range_systems

Select * 
From mountain_groups

Select * 
From peaks

Select *
From rivers

Select * 
From country_mountain_range_system

Select *
From country_river

--2)
CREATE PROCEDURE delete_peaks_in_mountain_group (@mountain_group_name VARCHAR(255))
AS
BEGIN
    DECLARE @mountain_group_id INT
    SELECT @mountain_group_id = id FROM mountain_groups WHERE name = @mountain_group_name

    DELETE FROM peaks WHERE mountain_group_id = @mountain_group_id
END

EXEC delete_peaks_in_mountain_group 'Mountain group A'
Go

--3)
CREATE VIEW countries_with_long_rivers_and_mountains AS
SELECT c.name
FROM countries c
JOIN country_river cr ON c.id = cr.country_id
JOIN rivers r ON r.id = cr.river_id
JOIN country_mountain_range_system cmrs ON c.id = cmrs.country_id
JOIN mountain_range_systems mrs ON mrs.id = cmrs.mountain_range_system_id
WHERE r.length > 300 AND mrs.length > 1000
GROUP BY c.name
HAVING COUNT(DISTINCT r.id) >= 2

SELECT * FROM countries_with_long_rivers_and_mountains

--4)
CREATE FUNCTION get_mountain_groups_by_peaks (@P INT, @H INT)
RETURNS TABLE
AS
RETURN
    SELECT mg.name
    FROM mountain_groups mg
    JOIN peaks p ON p.mountain_group_id = mg.id
    WHERE p.height > @H
    GROUP BY mg.name
    HAVING COUNT(p.id) >= @P

SELECT * FROM get_mountain_groups_by_peaks(2, 4000)