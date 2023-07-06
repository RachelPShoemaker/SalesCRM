#include "person.h"
#include "client.h"

#include <string>
#include <iostream>

Client::Client(string name, string phone, string email, Person* assigned_to, string contacted) : Person(name, phone, email) {
	employee = assigned_to;
	last_contacted = contacted;
	notepad = "";
}

Client::Client(string name, string phone, string email, string contacted) : Person(name, phone, email) {
	employee = NULL;
	last_contacted = contacted;
	notepad = "";
}

Client::Client(string name_input, string phone_input, string email_input, string activity, Person* employee_input, string date_input, string notes_input) : Person(name_input, phone_input, email_input, activity) {
	employee = employee_input;
	last_contacted = date_input;
	notepad = notes_input;

}

void Client::displayInfo() {
	cout << "\tClient's name: " << getName() << endl;
	cout << "\tPhone number: " << getPhone() << endl;
	cout << "\tEmail: " << getEmail() << endl;
	if (employee == NULL) { cout << "\tAssigned to: " << endl; }
	else if (employee != NULL) { cout << "\tAssigned to: " << employee->getName() << endl; }
	cout << "\tLast contacted: " << last_contacted << endl;
	if (isActive()) { cout << "\tActive" << endl; }
	else { cout << "\tInactive" << endl; }
	cout << "\tNotes: " << notepad << endl;
}