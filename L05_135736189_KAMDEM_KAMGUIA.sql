-- Q1 	For all employees in France, display employee number, first name, last name, city, phone number and postal code

SELECT e.employeeNumber, e.firstName, e.lastName,o.city, o.phone, o.postalCode
FROM employees e ,offices o 
WHERE e.officeCode = o.officeCode
AND lower(o.country) = 'france';

-- Q2a 	Create a view (Customer_Order) to list all orders with the following data for all customers:
		-- Customer Number, Order number, order date, product name, quantity ordered, and price for each product in every order
CREATE VIEW Customer_Order AS
SELECT o.orderNumber,o.orderDate, p.productName,
d.quantityOrdered, d.priceEach
FROM orders o JOIN orderdetails d USING(orderNumber)
		JOIN products p ON d.productCode = p.productCode;

-- Q3 	Using CustomerOrder (just created) display the information for customer number 124.  
		-- Sort the output based on order number and then order line number.
SELECT v.*
FROM Customer_Order v JOIN orderdetails d ON v.orderNumber = d.orderNumber
AND v.quantityOrdered = d.quantityOrdered
AND v.priceEach = d.priceEach
WHERE v.customerNumber = 124  
ORDER BY d.orderNumber, d.orderLineNumber;

-- Q4	Display customer number, first name, last name, phone, and credit limits for all customers who do not have any orders.
SELECT c.customerNumber, c.contactFirstName, c.contactLastName, c.phone, c.creditLimit 
FROM customers c LEFT OUTER JOIN orders o USING(customerNumber)
WHERE o.orderNumber is null;

-- Q5	Create a view (EmployeeManager) to display all information of employees and the name and the last name of 
        -- their managers if there is any manager that the employee reports to. 
CREATE VIEW vwEmployeeManager AS
SELECT e.*, m.firstName AS managerFirstName, m.lastName AS managerLastName
FROM employees e JOIN employees m ON e.reportsTo = m.employeeNumber;

-- Q6	Modify the employee_manager view so the view returns employee information for ALL employees who have a manager or not. 
		-- Do not DROP and recreate the view – modify it. (Google is your friend).

ALTER VIEW vwEmployeeManager AS
SELECT e.*, m.firstName AS managerFirstName, m.lastName AS managerLastName
FROM employees e LEFT OUTER JOIN employees m ON e.reportsTo = m.employeeNumber;

-- Q7 	Drop both the 2 new views just created in the previous questions
DROP VIEW vwCustomer_Order, vwEmployeeManager;