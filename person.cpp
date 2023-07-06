#include "Person.h"

#include <string>
#include <iostream>

using namespace std;

Person::Person(string name, string phone, string email) {
	fullname = name;
	phone_number = phone;
	email_address = email;
	active = true;
}

Person::Person(string name, string phone, string email, string activity) {
	fullname = name;
	phone_number = phone;
	email_address = email;
	if (activity.compare("Active") == 0) { active = true; }
	else { active = false; }
}