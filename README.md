# SalesCRM
This Customer Relationship Management(CRM) system is a tool for a company's sales department. It is a contact management system for both employees and potential clients.
It allows the user to create, search, delete, or update records. It can also display the complete list of contacts in alphabetical order.	
The employee record stores the name, phone, email, sales totals, and the total number of clients they have. 
The CRM automatically updates the employee's sales total and number of clients.
The client record stores name, phone, email, the employee they're working with, the date of most recent contact, and notes about how the sale is going. 
The record can be assigned to an existing employee record. Once the client is ready to buy, the user can finalize the sale and enter how much the customer paid. 
The payment will be automatically added to the associated employee's sales totals.

## Getting Started
You can launch this program in Visual Studio. If you don't have it already, you can download it at https://visualstudio.microsoft.com/downloads/
If this is your first time using the CRM, click the green <> Code button and click "Open with Visual Studio".
Click "Open Microsoft Visual Studio Web Protocol Handler Selector".
Visual Studio will open and you can clone this project to a new folder on your desktop.

If you have used the CRM on your computer before, go to the folder where the program is stored. 
Click the file "SalesCRM.sln" and it will launch in Visual Studio.

Once you are in Visual Studio, you can run my program by clicking the green triangle. The terminal will open and you will see the main menu.

## Information on the code
CRM organizes it's employee/client records in a binary search tree. This program has five classes,
* main.cpp
* BST.h and BST.cpp (This class is for the nodes of the binary search tree.)
* person.h and person.cpp: (This class is the parent class for the employee and client classes.)
* employee.h and employee.cpp
* client.h and client.cpp

## CRM Tutorial
## Main Menu
The program will launch to the main menu. If you've used CRM before, all of the save data are loaded automatically. 
You can access the employee menu by entering "e", the client menu by entering "c", or quit the program by entering "q". 
After you choose to quit the program, the data is saved automatically before closing.

## Employee Menu
### Add new contact
In the employee menu, you can add a new employee by entering "1".
CRM will prompt you to enter the employee's name, phone number, and email. An error message will appear if an identical record already exists.

### Search contact
You can search for an existing contact by entering "2". CRM will prompt you to enter the salesperson's name. Their contact information, number of clients,
and their total sales are displayed. If there aren't any employee records on file, or the person
you search for doesn't exist yet, an error message will appear.

### Display all
To display all employee records, enter "3". The employees and their information will be displayed in alphabetical order by first name.
If there aren't any records yet, an error message will be displayed.

### Delete contact
To delete a contact, enter "4". CRM will prompt you to enter the name of the record you wish to delete.
If there aren't any records yet, or if the record doesn't exist, an error message will appear.
The employee will be removed from all the client records associated with them automatically.

### Update record
To update an employee's phone number enter "a". CRM will prompt you to enter the name and new phone number.
Enter "b" to update the email. CRM will prompt you to enter the name and new email.
Finally, you can enter "c" to activate or deactivate the record. You will be prompted for the name.
If the record is inactive, CRM will activate it. If active, CRM will deactivate it.

### Main menu
Enter "m" to return to the main menu.

## Client Menu
### Add new contact
Enter "1" to create a new client record. CRM will prompt you to enter the name, phone number, and email address.
You will be asked to enter the name of the sales employee they are working with. If the employee doesn't exist,
CRM will give you a warning. You can continue to create the client contact and you have the option to assign them to an employee record later. 
For more information on assigning employees, please see the "Update record" section below. 
If an employee was successfully assigned to the client, that employee's client count is adjusted automatically.
Finally, CRM will prompt you to enter the date the sales employee most recently contacted them.

### Search contact
To search for a client record, enter "2". This function works the same way as the Employee Seach contact process.

### Display
To display all the clients and their information, enter "3". The clients will be listed in alphabetical order by first name.
It lists the phone number, email, name of the employee they're assigned to, the date they most recently spoke to the sales employee,
and notes about the conversation. 

### Finalize sale
Enter "4" to finalize a sale. CRM will prompt you for the name of the client. If the client isn't assigned to an employee record yet,
CRM will tell you to assign an employee before continuing. The instructions to assign an employee 
are shown under the "Update record" section of this tutorial.

Otherwise, CRM will ask you to enter the sale amount and it will be added to the sales employee's sales total automatically.
The client record is automatically deactivated since they are no longer a potential client.

### Delete contact
Enter "5' to delete a client record. This process works the same as the Employee Delete contact function above.
If they were assigned to an employee, the employee's number of clients is automatically adjusted.

### Update record
The "Change phone number", "Change email address", and "Activate/Deactivate record" options work the same as the employee menu.

To assign the client record to an employee, or to reassign them to a different employee, enter "d".
CRM will prompt you for the client's name and the employee's name. If both records exist, the client is assigned to the employee record.
The new sales employee's client count will be adjusted automatically. If the client was reassigned from a different employee, 
that employee's client count will be adjusted as well.

If the employee spoke with the client again, you can update the date last contacted by entering "e".
CRM will prompt you for the name of the client, the date, and notes about how the sale is going. 

### Main menu
Enter "m" to return to the main menu.

## Built With
Visual Studio in C++

## Author
Rachel Shoemaker

Version 1.0


