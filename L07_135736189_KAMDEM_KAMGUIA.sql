-- 1.	Create an empty table exactly the same as the employees table and name it newEmployees.
CREATE TABLE newEmployees(
employeeNumber int primary key,
lastName varchar(50) not null,
firstName varchar(50) not null,
extension varchar(10) not null,
email varchar(100) not null,
officeCode varchar(10) not null,
reportsTo int(11) default null,
jobTitle varchar(50) not null,
CONSTRAINT EMPLLOYEE_OFFICECODE_FK FOREIGN KEY (officeCode) REFERENCES offices(officeCode),
CONSTRAINT EMPLLOYEE_REPORT_FK FOREIGN KEY (reportsTo) REFERENCES employees(employeeNumber)
);

-- 2.	Execute the following commands.
set autocommit = off;
start transaction;

-- 3.	Write an INSERT statement to populate the newEmployees table with the rows of the sample data. 
     -- Insert the NULL value for the reportsTo column. (Write a single INSERT statement to insert all the rows)
     INSERT INTO newEmployees 
VALUE
 (100, 'Patel', 'Ralph', 22333, 'rpatel@mail.com', 1, null, 'Sales Rep'),
 (101, 'Denis', 'Betty', 33444, 'bdenis@mail.com', 4, NULL, 'Sales Rep'),
 (102, 'Biri', 'Ben', 44555, 'bbirir@mail.com', 2, NULL, 'Sales Rep'),
 (103, 'Newman', 'Chad', 66777, 'cnewman@mail.com', 3, NULL, 'Sales Rep'),
 (104, 'Ropeburn', 'Audrey', 77888, 'aropebur@mail.com',1 , NULL, 'Sales Rep');
 
-- 4.	Create a report that shows all the inserted rows from the newEmployees table. How many rows are selected?
select * from newEmployees;  -- 05 rows are selected

-- 5.	Execute the rollback command. Display all rows and columns from the newEmployees table. How many rows are selected?
rollback;
select * from newEmployees; -- 05 rows are selected

-- 6.	Do Task 3. Make the insertion permanent to the table newEmployees. 
   -- Display all rows and columns from the newEmployee table. How many rows are selected?
  INSERT INTO newEmployees
select * from newEmployees 
commit;          -- 05 rows are selected

-- 7.	Write an update statement to update the value of column jobTitle to ‘unknown’ for all the employees in the newEmployees table.
update newEmployees set
jobTitle = 'unknown'
where employeeNumber != 0;

-- 8.	Make your changes permanent.
commit;

-- 9.	Execute the rollback command.
rollback;

-- a.	Display all employees from the newEmployees table whose job title is ‘unknown’. How many rows are updated?
select * from newEmployees
where jobTitle = 'unknown';   -- 5 rows are updated

-- b.	Was the rollback command effective?
  -- No because all the commands was saved before using rollback, so it could not undo anything

-- c.	What was the difference between the result of the rollback execution 
  -- from Task 5 and the result of the rollback execution of this task?
  /* on task 5 the rollback command was working because we had not used the command "commit" yet, while on this task,
the command commit has been usinf to save everything and when we used rollback to undo on the previous statement, it will not do anything */ 



 
