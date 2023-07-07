// Rachel Shoemaker
// Version 1.0

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BST.h"
#include "person.h"
#include "employee.h"
#include "client.h"
using namespace std;

void mainMenu();
void employeeMenu();
void clientMenu();

// These functions work together to unload the data from the save file
// They create a sorted employee and client vectors, then converts them to binary search trees.
void initializeEmployee(string name_input, string phone_input, string email_input, string activity, int num_clients, long double sales_input);
void initializeClient(string name_input, string phone_input, string email_input, string activity, Person* employee_name_input, string date_input, string notes_input);
BST* vectorToTree(vector<Person*> person, int start, int end);

// These functions add new employee/client records, and inserts them into the BST's
bool addEmployeeContact(string name_input, string phone_input, string email_input); 
bool addClientContact(string name_input, string phone_input, string email_input, Person* employee, string date_input);
void insert(BST* iter, Person *p); 

void unassignEmployee(BST* iter, string name_input); // Unassigns the employee from a client record, before deletion
BST* deleteByName(BST* iter, string name_input);
void display(BST* iter);
BST* searchByName(BST* iter, string name); 

// These functions are used in the save feature. Converts the binary search trees to vectors, and deletes the entire BST's.
void employeeTreeToVector(BST* iter);
void clientTreeToVector(BST* iter);
void deleteTree(BST* iter);

BST* clientTree = NULL;
BST* employeeTree = NULL;
int countEmployee = 0;
int countClient = 0;
vector<Person*> employees;
vector<Person*> clients;

int main(){ 
	int count = 0;
	string name_input = "";
	string salesperson_name = "";
	string phone_input = "";
	string email_input = "";
	string activity = "";
	string date_input;
	string notes_input;
	int num_clients = 0;
	long double sales_input = 0.0;
	BST* node = NULL;
	Person* person = NULL;

	ifstream load_file;
	load_file.open("save_data.txt");
	if (load_file.is_open()) {
		load_file >> count; // Number of employee records
		load_file.ignore();

		// Obtains all the employee data and adds them to the employee vector
		for (int i = 0; i < count; i++) {
			getline(load_file, name_input);
			getline(load_file, phone_input);
			getline(load_file, email_input);
			getline(load_file, activity);
			load_file >> num_clients;
			load_file.ignore();
			load_file >> sales_input;
			load_file.ignore();
			initializeEmployee(name_input, phone_input, email_input, activity, num_clients, sales_input);
		}
		if (employees.size() != 0) { employeeTree = vectorToTree(employees, 0, (count - 1)); }
		countEmployee = count;
		employees.clear();

		load_file >> count; // Number of client records
		load_file.ignore();

		// Obtains all the client data and adds them to the client vector
		for (int i = 0; i < count; i++) {
			getline(load_file, name_input);
			getline(load_file, phone_input);
			getline(load_file, email_input);
			getline(load_file, activity);
			getline(load_file, salesperson_name);
			if (salesperson_name.compare("N/A") == 0) { person = NULL; } 
			else {
				node = searchByName(employeeTree, salesperson_name);
				person = node->person;
			}
			getline(load_file, date_input);
			getline(load_file, notes_input);
			initializeClient(name_input, phone_input, email_input, activity, person, date_input, notes_input);
		}
		if (clients.size() != 0) { clientTree = vectorToTree(clients, 0, (count - 1)); }
		countClient = count;
		clients.clear();
	}
	load_file.close();	

	mainMenu();

	// Auto-save feature
	employeeTreeToVector(employeeTree);
	clientTreeToVector(clientTree);
	ofstream save_file;
	save_file.open("save_data.txt");
	save_file << countEmployee << endl;
	for (int i = 0; i < countEmployee; i++) {
		Employee* employee = (Employee*)employees[i];
		save_file << employee->getName() << endl;
		save_file << employee->getPhone() << endl;
		save_file << employee->getEmail() << endl;
		if (employee->isActive()) { save_file << "Active" << endl; }
		else { save_file << "Inactive" << endl; }
		save_file << employee->getNumClients() << endl;
		save_file << employee->getTotalSales() << endl;
	}
	save_file << countClient << endl;
	for (int i = 0; i < countClient; i++) {
		Client* client = (Client*)clients[i];
		save_file << client->getName() << endl;
		save_file << client->getPhone() << endl;
		save_file << client->getEmail() << endl;
		if(client->isActive()) { save_file << "Active" << endl; }
		else { save_file << "Inactive" << endl; }
		if (client->getEmployee() == NULL) { save_file << "N/A" << endl; }
		else { save_file << client->getEmployee()->getName() << endl; }
		save_file << client->getDate() << endl;
		if (client->getNotes() == "") { save_file << "N/A" << endl; }
		else { save_file << client->getNotes() << endl; }
	}
	save_file.close();

	// delete trees, vectors, and the person objects before exiting
	employees.clear();
	deleteTree(employeeTree);
	clients.clear();
	deleteTree(clientTree);
	return 0;
}

void mainMenu() {
	char choice = 'i';
	while (choice != 'q') {
		cout << "Please make a selection:" << endl;
		cout << "\t e: employee menu" << endl;
		cout << "\t c: client menu" << endl;
		cout << "\t q: quit" << endl;
		cin >> choice;
		cin.ignore();
		
		switch (choice) { 
		case 'e': 
			employeeMenu();
			break;
		case 'c':
			clientMenu();
			break;
		case 'q': 
			break; 
		default: 
			cout << "Invalid entry. Please try again." << endl;
			break;
		}
	}
}

void employeeMenu() {
	string name_input;
	string phone_input;
	string email_input;
	BST* node; 
	Employee* employee;
	
	char choice = 'i'; 
	while (choice != 'm') {
		cout << endl;
		cout << "EMPLOYEE RECORDS" << endl;
		cout << "Please make a selection:" << endl;
		cout << "\t 1: Add new contact" << endl;
		cout << "\t 2: Search contact" << endl;
		cout << "\t 3: Display all" << endl;
		cout << "\t 4: Delete contact" << endl;
		cout << "\t    Update record" << endl;
		cout << "\t\t a: Change phone number" << endl;
		cout << "\t\t b: Change email address" << endl;
		cout << "\t\t c: Activate/Deactivate record" << endl;
		cout << "\t m: Main menu\n";
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case '1': // Add a new employee record
			cout << "Enter salesperson's name: ";
			getline(cin, name_input);
			cout << "Enter phone number (XXX-XXX-XXXX): ";
			getline(cin, phone_input);
			cout << "Enter email address: ";
			getline(cin, email_input);

			// addEmployeeContact helper function returns true if the record was successfully added.
			if (addEmployeeContact(name_input, phone_input, email_input)) { 
				cout << "New salesperson added." << endl;
				countEmployee++;
			}
			else { cout << "Employee is already on file." << endl; }
			cout << "There are " << countEmployee << " employee(s) on file." << endl;
			break;
		case '2': // Searches for an employee record by name.
			if (countEmployee == 0) { cout << "There are zero employee records on file." << endl; }
			else {
				cout << "Enter salesperson's name: ";
				getline(cin, name_input);
				node = searchByName(employeeTree, name_input); 
				if (node == NULL) { cout << "Record doesn't exist." << endl; }
				else if (node != NULL) { node->person->displayInfo(); }
			}
			break;
		case '3': // Displays all the employee records in alphabetical order by first name.
			if (countEmployee == 0) { cout << "There are zero employee records on file." << endl; }
			else { display(employeeTree); }
			break;
		case '4': // Delete an employee record
			if (countEmployee == 0) {
				cout << "There are zero employees on file" << endl;
				break;
			}
			cout << "Enter employee's name: ";
			getline(cin, name_input);
			node = searchByName(employeeTree, name_input);
			if (node == NULL) {
				cout << "Record doesn't exist." << endl;
				break;
			}
			unassignEmployee(clientTree, name_input); // Unassign this employee from all associated client files
			employee = (Employee*)node->person;
			deleteByName(employeeTree, name_input);
			delete employee;
			countEmployee--;
			cout << "Record deleted." << endl;
			break;
		case 'a': // Updates phone number
			if(countEmployee == 0) { 
				cout << "There are zero employee records on file." << endl;
				break;
			}
			cout << "Which record do you wish to update? \nEnter employee's name: ";
			getline(cin, name_input);
			node = searchByName(employeeTree, name_input);
			if (node == NULL) { 
				cout << "Record doesn't exist." << endl; 
				break;
			}
			cout << "Please enter new phone number: ";
			getline(cin, phone_input);
			node->person->setPhone(phone_input);
			cout << "\nRecord updated.\n";
			node->person->displayInfo();
			break;
		case 'b': // Updates email address
			if (countEmployee == 0) { 
				cout << "There are zero employee records on file." << endl; 
				break;
			}
			cout << "Which record do you wish to update? \nEnter employee's name: ";
			getline(cin, name_input);
			node = searchByName(employeeTree, name_input);
			if (node == NULL) { 
				cout << "Record doesn't exist." << endl; 
				break;
			}
			cout << "Enter new email address: ";
			getline(cin, email_input);
			node->person->setEmail(email_input);
			cout << "\nRecord updated.\n";
			node->person->displayInfo();
			break;
		case 'c': // Activate/Deactivate record
			if (countEmployee == 0) { 
				cout << "There are zero employee records on file." << endl;
				break;
			}
			cout << "Which record do you wish to update? \nEnter employee's name: ";
			getline(cin, name_input);
			node = searchByName(employeeTree, name_input);
			if (node == NULL) { 
				cout << "Record doesn't exist." << endl;
				break;
			}
			if (node->person->isActive()) {
				node->person->makeInactive();
				cout << "Employee record is now inactive." << endl;
			}
			else {
				node->person->makeActive();
				cout << "Employee record is now active." << endl;
			}
			break;
		case 'm': break; // Returns to main menu
		default: cout << "Invalid entry. Please try again." << endl;
			break;
		}
	}
}

void clientMenu() {
	string name_input;
	string phone_input;
	string email_input;
	string employee_name_input; // Used to assign an employee to the client.
	string date_input; // Date of most recent contact
	string notes; // Notes about how the sale is going
	long double price; 
	BST* node;
	Client* client = NULL;
	Employee* employee = NULL;

	char choice = 'i';
	while (choice != 'm') {
		cout << "\nCLIENT RECORDS" << endl;
		cout << "Please make a selection:" << endl;
		cout << "\t 1: Add new contact" << endl;
		cout << "\t 2: Search contact" << endl;
		cout << "\t 3: Display\n";
		cout << "\t 4: Finalize sale" << endl;
		cout << "\t 5: Delete contact" << endl;
		cout << "\t    Update record" << endl;
		cout << "\t\t a: Change phone number" << endl;
		cout << "\t\t b: Change email address" << endl;
		cout << "\t\t c: Activate/Deactivate record" << endl;
		cout << "\t\t d: Assign/Reassign salesperson" << endl;
		cout << "\t\t e: Last contacted" << endl;
		cout << "\t m: Main menu\n";
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case '1': // Add client
			cout << "Enter client name: ";
			getline(cin, name_input);
			cout << "Enter phone number (XXX-XXX-XXXX): ";
			getline(cin, phone_input);
			cout << "Enter email address: ";
			getline(cin, email_input);
			if (countEmployee != 0) {
				cout << "Who is this client working with? ";
				getline(cin, employee_name_input);
				node = searchByName(employeeTree, employee_name_input);
				if (node == NULL) {
					cout << "Salesperson doesn't exist. Please assign the client to an agent later." << endl;
					employee = NULL;
				}
				else if (node != NULL) { employee = (Employee*)node->person; }
			}
			cout << "Date last contacted (YYYY-MM-DD): ";
			getline(cin, date_input);

			// addClientContact returns true if the record was successfully added.
			if (addClientContact(name_input, phone_input, email_input, employee, date_input)) {
				cout << "New client added." << endl;
				countClient++;
				if (employee != NULL) { employee->addClient(); } // increments the employee's total client count.
			}
			else { cout << "Client is already on file." << endl; }
			cout << "There are " << countClient << " client(s) on file." << endl;
			break;
		case '2': // Search client
			if (countClient == 0) { 
				cout << "There are zero client records on file." << endl;
				break;
			}
			cout << "Enter client's name: ";
			getline(cin, name_input);
			node = searchByName(clientTree, name_input);
			if (node == NULL) { cout << "Record doesn't exist." << endl; }
			else if (node != NULL) { node->person->displayInfo(); }
			break;
		case '3': // Displays all the clients in alphabetical order by first name.
			if (countClient == 0) { 
				cout << "There are zero client records on file." << endl;
				break;
			}
			display(clientTree);
			break;
		case '4': // Finalize sale
			cout << "Enter client's name: ";
			getline(cin, name_input);
			node = searchByName(clientTree, name_input);
			if (node == NULL) {
				cout << "Record doesn't exist. Please try again." << endl;
				break;
			}
			client = (Client*)node->person;
			if (client->getEmployee() == NULL) {
				cout << "Please assign a salesperson to this record before continuing." << endl;
				break;
			}
			cout << "Enter the final selling price: ";
			cin >> price;
			employee = (Employee*)client->getEmployee();
			employee->sold(price);
			client->makeInactive();
			cout << "Records updated." << endl;
			break;
		case '5': // Delete client record
			if (countClient == 0) {
				cout << "There are zero client on file" << endl;
				break;
			}
			cout << "Enter client's name: ";
			getline(cin, name_input);
			node = searchByName(clientTree, name_input);
			if (node == NULL) {
				cout << "Record doesn't exist." << endl;
				break;
			}
			client = (Client*)node->person;
			if (client->getEmployee() != NULL) {
				employee = (Employee*)client->getEmployee();
				employee->removeClient();
			}
			deleteByName(clientTree, name_input);
			delete client;
			countClient--;
			cout << "Record deleted." << endl;
			break;
		case 'a': // Updates phone number
			if (countClient == 0) {
				cout << "There are zero client records on file." << endl;
				break;
			}
			cout << "Which record do you wish to update? \nEnter client's name: ";
			getline(cin, name_input);
			node = searchByName(clientTree, name_input);
			if (node == NULL) {
				cout << "Record doesn't exist." << endl;
				break;
			}
			cout << "Please enter new phone number: ";
			getline(cin, phone_input);
			node->person->setPhone(phone_input);
			cout << "\nRecord updated.\n";
			node->person->displayInfo();
			break;
		case 'b': // Updates email address
			if (countClient == 0) {
				cout << "There are zero client records on file." << endl;
				break;
			}
			cout << "Which record do you wish to update? \nEnter client's name: ";
			getline(cin, name_input);
			node = searchByName(clientTree, name_input);
			if (node == NULL) {
				cout << "Record doesn't exist." << endl;
				break;
			}
			cout << "Enter new email address: ";
			getline(cin, email_input);
			node->person->setEmail(email_input);
			cout << "\nRecord updated.\n";
			node->person->displayInfo();
			break;
		case 'c': // Activate/Deactivate
			if (countClient == 0) {
				cout << "There are zero client records on file." << endl;
				break;
			}
			cout << "Which record do you wish to update? \nEnter client's name: ";
			getline(cin, name_input);
			node = searchByName(clientTree, name_input);
			if (node == NULL) {
				cout << "Record doesn't exist." << endl;
				break;
			}
			if (node->person->isActive()) {
				node->person->makeInactive();
				cout << "Client record is now inactive." << endl;
			}
			else {
				node->person->makeActive();
				cout << "Client record is now active." << endl;
			}
			break;
		case 'd': // Assign/Reassign employee to client
			if (countClient == 0) {
				cout << "There are zero client records on file." << endl;
				break;
			}
			cout << "Which record do you wish to update?\n Enter client's name: ";
			getline(cin, name_input);
			node = searchByName(clientTree, name_input);
			if (node == NULL) { 
				cout << "Record doesn't exist." << endl; 
				break;
			}
			cout << "Enter salesperson's name: ";
			getline(cin, employee_name_input);
			client = (Client*)node->person;
			node = searchByName(employeeTree, employee_name_input);
			if (node == NULL) {
				cout << "Salesperson doesn't exist. Please try again." << endl;
				break;
			}
			// If the client is currently assigned to an employee, decrement that employee's number of clients
			if (client->getEmployee() != NULL) {
				employee = (Employee*)client->getEmployee();
				employee->removeClient();
			}
			// Assign the new employee to the client and increment the new employee's number of clients
			client->setEmployee(node->person);
			employee = (Employee*)node->person;
			employee->addClient();

			cout << "Record updated." << endl;
			client->displayInfo();
			break;
		case 'e': // Update date of most recent contact
			if (countClient == 0) {
				cout << "There are zero client records on file." << endl;
				break;
			}
			cout << "Which record do you wish to update?\n Enter client's name: ";
			getline(cin, name_input);
			node = searchByName(clientTree, name_input);
			if (node == NULL) {
				cout << "Record doesn't exist." << endl;
				break;
			}
			cout << "When was the client last contacted? Enter date (YYYY-MM-DD): ";
			getline(cin, date_input);
			client = (Client*)node->person;
			client->setDate(date_input);
			cout << "Enter notes about the meeting: ";
			getline(cin, notes);
			client->saveNotes(notes);
			cout << "Record updated." << endl;
			node->person->displayInfo();
			break;
		case 'm': // Return to main menu
			break;
		default: 
			cout << "Invalid entry. Please try again." << endl; 
			break;
		}
	}
}

void initializeEmployee(string name_input, string phone_input, string email_input, string activity, int num_clients, long double sales_input) {
	Employee* employee = new Employee(name_input, phone_input, email_input, activity, num_clients, sales_input);
	employees.push_back(employee);
}

void initializeClient(string name_input, string phone_input, string email_input, string activity, Person* employee, string date_input, string notes_input) {
	Client* client = new Client(name_input, phone_input, email_input, activity, employee, date_input, notes_input);
	clients.push_back(client);
}

BST* vectorToTree(vector<Person*> person, int start, int end) {
	if (start > end) { return NULL; }
	int mid = (start + end) / 2;
	BST* root = new BST();
	root->person = person[mid];
	root->left = vectorToTree(person, start, (mid - 1));
	root->right = vectorToTree(person, (mid + 1), end);
	return root;
}

bool addEmployeeContact(string name_input, string phone_input, string email_input) {
	if (countEmployee == 0) {
		employeeTree = new BST();
		employeeTree->person = new Employee(name_input, phone_input, email_input);
		return true;
	}
	else {
		if (searchByName(employeeTree, name_input) != NULL) { return false; }
		else {
			Employee* employee = new Employee(name_input, phone_input, email_input);
			insert(employeeTree, employee);
			return true;
		}
	}
}

bool addClientContact(string name_input, string phone_input, string email_input, Person* employee, string date_input) {
	if (countClient == 0) {
		clientTree = new BST();
		if (employee != NULL) { clientTree->person = new Client(name_input, phone_input, email_input, employee, date_input); }
		else { clientTree->person = new Client(name_input, phone_input, email_input, date_input); }
		return true;
	}
	if(searchByName(clientTree, name_input) != NULL) { return false; }	
	Client* client = NULL;
	if (employee != NULL) { client = new Client(name_input, phone_input, email_input, employee, date_input); }
	else if(employee == NULL) { client = new Client(name_input, phone_input, email_input, date_input); }
	insert(clientTree, client);
	return true;
}

void insert(BST* iter, Person *p) {
	string this_name = iter->person->getName();
	string other_name = p->getName();
	if (this_name.compare(other_name) > 0) {
		if(iter->left == NULL) {
			iter->left = new BST();
			iter->left->person = p;
			iter->left->parent = iter;
		}
		else { insert(iter->left, p); }
	}
	else if (this_name.compare(other_name) < 0) {
		if (iter->right == NULL) {
			iter->right = new BST();
			iter->right->person = p;
			iter->right->parent = iter;		
		}
		else { insert(iter->right, p); }
	}
}

void unassignEmployee(BST* iter, string name_input) {
	if (iter == NULL) { return; }
	else {
		Client* client = (Client*)iter->person;
		unassignEmployee(iter->left, name_input);
		if (client->getEmployee() != NULL) {
			string employee_name = client->getEmployee()->getName();
			if (employee_name.compare(name_input) == 0) {
				client->setEmployee(NULL);
			}
		}
		unassignEmployee(iter->right, name_input);
		return;
	}
}

BST* deleteByName(BST* iter, string name_input) {
	string this_name = iter->person->getName();
	if (iter == NULL) { return iter; } // Base case
	if (this_name.compare(name_input) > 0) {
		iter->left = deleteByName(iter->left, name_input);
		return iter;
	}
	else if (this_name.compare(name_input) < 0) {
		iter->right = deleteByName(iter->right, name_input);
		return iter;
	}
	if (iter->left == NULL) {
		BST* temp = iter->right;
		delete iter;
		return temp;
	}
	else if (iter->right == NULL) {
		BST* temp = iter->left;
		delete iter;
		return temp;
	}
	else {
		BST* parent = iter;
		BST* child = iter->right;
		while (child->left != NULL) {
			parent = child;
			child = child->left;
		}

		if (parent != iter) { parent->left = child->right; }
		else { parent->right = child->right; }
		iter->person = child->person;
		delete child;
		return iter;
	}
}

BST* searchByName(BST* iter, string name_input) {
	string person_name = iter->person->getName();
	if (person_name.compare(name_input) == 0) { return iter; }// Base case 1: returns the person when a match is found
	else if (person_name.compare(name_input) > 0) {
		if (iter->left == NULL) { return NULL; }// Base case 2: returns null if the person's record doesn't exist
		else { return searchByName(iter->left, name_input); } 
	}
	else {
		if (iter->right == NULL) { return NULL; }// Base case 3: returns null if the person's record doesn't exist
		else { return searchByName(iter->right, name_input); } 
	}
}

void display(BST* iter) {
	if (iter == NULL) { return; }
	else {
		display(iter->left);
		iter->person->displayInfo();
		cout << endl;
		display(iter->right);
		return;
	}
}

void employeeTreeToVector(BST* iter) {
	if (iter == NULL) { return; }
	else {
		employeeTreeToVector(iter->left);
		employees.push_back(iter->person);
		employeeTreeToVector(iter->right);
		return;
	}
}

void clientTreeToVector(BST* iter) {
	if (iter == NULL) { return; }
	else {
		clientTreeToVector(iter->left);
		clients.push_back(iter->person);
		clientTreeToVector(iter->right);
		return;
	}
}

void deleteTree(BST* iter) {
	if (iter == NULL) { return; }
	else {
		deleteTree(iter->left);
		deleteTree(iter->right);
		Person* person = iter->person;
		delete person;
		delete iter;
		iter = NULL;
	}
}