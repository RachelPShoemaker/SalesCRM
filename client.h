#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string>
#include <iostream>
using namespace std;

class Client : public Person
{
	private:
		Person* employee;
		string last_contacted;
		string notepad;

	public:
		Client(string name, string phone, string email, Person* assigned_to, string contacted);
		Client(string name, string phone, string email, string contacted);
		Client(string name_input, string phone_input, string email_input, string activity, Person* employee, string date_input, string notes_input);
		//Client(string name_input, string phone_input, string email_input, string activity, string date_input, string notes_input);
		~Client() { }
		Person* getEmployee() { return employee; }
		void setEmployee(Person* assigned_to) { employee = assigned_to; }
		string getDate() { return last_contacted; }
		void setDate(string date) { last_contacted = date; }
		string getNotes() { return notepad; }
		void saveNotes(string notes) { notepad = notes; }
		void displayInfo();
};

#endif // _CLIENT_H_
