#include "person.h"
#include "employee.h"

#include <iostream>

Employee::Employee(string name, string phone, string email) : Person(name, phone, email) {
	count_clients = 0;
	total_sales = 0.0;
}

Employee::Employee(string name, string phone, string email, string activity, int clients, long double sales) : Person(name, phone, email, activity) {
	count_clients = clients;
	total_sales = sales;
}

void Employee::displayInfo() {
	cout << "\tEmployee's name: " << getName() << endl;
	cout << "\tPhone number: " << getPhone() << endl;
	cout << "\tEmail: " << getEmail() << endl;
	cout << "\tNumber of clients: " << getNumClients() << endl;
	printf("\tTotal sales: $%.2f\n", total_sales);
	if (isActive()) { cout << "\tActive" << endl; }
	else { cout << "\tInactive" << endl; }
}

