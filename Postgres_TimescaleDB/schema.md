
## First, we create a normal PostgreSQL Database named **timescale_test** 

```sql
CREATE DATABASE timescale_test;
```
## Connect to the Database:

```sql
\c test_timescale
```

## The following code will extend the database with TimescaleDB:

```sql
CREATE EXTENSION IF NOT EXISTS timescaledb;
```
## Now, we create our first table, called `device_master`, which will keep track of the devices in use:

```sql
CREATE TABLE device_master (  
    device_id INT,  
    device_name VARCHAR(15) NOT NULL,   
    PRIMARY KEY (device_id)  
); 
```

## The second table is created to log the data froom ESP8266. Two of the fields are given default values:
 ### 1. `log_id`: This field will have a UUID generated for every entry.
 ### 2. `timestamp`: The "CURRENT TIMESTAMP" will insert the timestamp during insertion.
```sql
CREATE TABLE log_master (  
    log_id uuid DEFAULT uuid_in(md5(random()::text)::cstring),  
    timestamp TIMESTAMP NOT NULL DEFAULT CURRENT TIMESTAMP,  
    temperature REAL NOT NULL,  
    humidity REAL NOT NULL,  
    device_id INT,  
    PRIMARY KEY (log_id),
    FOREIGN KEY(device_id) REFENCES device_master(device_id)  
); 
```
## The `\d` command can be used to describe the created tables and view for yourself, like so:
```sql
\d device_master
```
## And so:
```sql
\d log_master
```
 