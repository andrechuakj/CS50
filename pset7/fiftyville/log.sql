-- Keep a log of any SQL queries you execute as you solve the mystery.

.schema
--> see the tables and columns in the .db file
-- RESULTS:
/*CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE courthouse_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);*/

SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street LIKE "%chamberlin%";
--> find all existing details about what happened at the time and location where the theft happened
/*RESULTS:
id | year | month | day | street | description
295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street
courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their
interview transcripts mentions the courthouse.*/
-- NEW INFO:
-- time:1015am
-- location: chamberlin street courthouse
-- 3 witness
-- interviews mention the courthouse

SELECT * FROM interviews WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%";
--> find all interviewees and their transcript
/* RESULTS:
id | name | year | month | day | transcript
161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.*/

--BASED OF RUTH transcript
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
--> find out the activities happening and license plates during the stated timing by RUTH
/* RESULTS:
id | year | month | day | hour | minute | activity | license_plate
260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55*/

--BASED OF EUGENE transcript
SELECT * FROM atm_transactions WHERE year = 2020 AND month = 07 AND day = 28 AND atm_location LIKE "%fifer street%";
--> Find all the account number that made withdrawals that day
/*RESULTS:
246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
275 | 86363979 | 2020 | 7 | 28 | Fifer Street | deposit | 10
288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35*/

SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 07 AND day = 28 AND atm_location LIKE "%fifer street%" AND transaction_type LIKE "%withdraw%"));
--> Find the details of all the people that made ATM withdrawals that day
/*RESULTS:
395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X*/

--BASED OF RAYMOND transcript
SELECT * FROM phone_calls WHERE year = 2020 AND month = 07 year = 2020 AND month = 07;
--> to check the format of duration so as to further narrow down search
-- RESULTS: duration in SECONDS
SELECT * FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60;
--> Find details of all the people who made phone calls on that day with duration less than a minute
/*RESULTS:
id | caller | receiver | year | month | day | duration
221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54 */

SELECT * FROM airports WHERE city LIKE "%fiftyville";
--> Find the details of the airport in Fiftyville
-- RESULTS:
-- id | abbreviation | full_name | city
-- 8 | CSF | Fiftyville Regional Airport | Fiftyville

SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2020 AND month = 07 AND day = 29 ORDER BY hour, minute;
--> find the details of all the flights from fiftyville on the day after the theft
/* RESULTS:
id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 --> EARLIEST
43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30
23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15
53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20
18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0*/

SELECT * FROM passengers WHERE flight_id = 36;
--> Find details of the passengers on the earliest flight from fiftyville
/*RESULTS:
36 | 7214083635 | 2A
36 | 1695452385 | 3B
36 | 5773159633 | 4A
36 | 1540955065 | 5C
36 | 8294398571 | 6C
36 | 1988161715 | 6D
36 | 9878712108 | 7A
36 | 8496433585 | 7B*/


-- PROCESSING ALL THE DATA FOUND
SELECT passport_number FROM passengers WHERE flight_id = 36
INTERSECT
SELECT passport_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 07 AND day = 28 AND atm_location LIKE "%fifer street%" AND transaction_type LIKE "%withdraw%"))
INTERSECT
SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)
INTERSECT
SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60);
--> Find passport number of person who took earliest flight on the 29th, withdraw money on the 28Tth, called for less than a minute on the 28th, and exited the courthouse within 10 minutes of the theft
-- RESULTS: 
--passport_number
--5773159633 (THIEF FOUND!!)


--FIND THE thief name, place he escaped to and his accomplice:

-- FIND THIEF NAME:
SELECT name FROM people WHERE passport_number = 5773159633;
-- NAME: Ernest

-- FIND WHERE HE ESCAPED TO:
SELECT city FROM airports WHERE id = 4;
-- CITY: London

-- FIND ACCOMPLICE:
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 07 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE passport_number = 5773159633));
-- ACCOMPLICE: Berthold