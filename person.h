#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
using namespace std;

class Person {
	private:
		string fullname;
		string phone_number;
		string email_address;
		bool active;

	public:
		Person(string name, string phone, string email); // Constructor
		Person(string name, string phone, string email, string activity); // Full constructor
		virtual ~Person() { }
		string getName() { return fullname; }
		void setName(string name) { fullname = name; }
		string getPhone() { return phone_number; }
		void setPhone(string phone) { phone_number = phone; }
		string getEmail() { return email_address; }
		void setEmail(string email) { email_address = email; }
		bool isActive() { return active; }
		void makeActive() { active = true; }
		void makeInactive() { active = false; }
		virtual void displayInfo() {}
};

#endif // _PERSON_H_