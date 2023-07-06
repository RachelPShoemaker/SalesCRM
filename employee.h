#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H
#include <string>
#include <iostream>

class Employee : public Person
{
	private:
		int count_clients;
		long double total_sales;

	public:
		Employee(string name, string phone, string email);
		Employee(string name, string phone, string email, string activity, int clients, long double sales);
		~Employee() { }
		int getNumClients() { return count_clients; }
		void addClient() { count_clients++; }
		void removeClient() { count_clients--; }
		long double getTotalSales() { return total_sales; }
		void sold(long double sale) { total_sales += sale; }
		void displayInfo();

};

#endif // _EMPLOYEE_H
