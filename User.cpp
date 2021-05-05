/*
 * User.cpp
 *
 *  Created on: Mar 20, 2021
 *      Author: t.todorov
 */

#include "User.h"
#include "Group.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


User::~User(){};
User::User(){};


string User::getFirstName() {
	return this->firstName;
}

string User::getLastName() {
	return this->lastName;
}

int User::getGroupID() {
	return this->groupID;
}

void User::setFirstName(string firstname) {
	this->firstName = firstname;
}

void User::setLastName(string lastName) {
	this->lastName = lastName;
}

void User::setGroupID(int groupID) {
	this->groupID = groupID;
}

double getUserDiscount(int userId) {
	double discount = 0;
	vector<Group> groups;
	vector <User> groupUsers;

	groups = getGroupsFromFile("groups.txt");

	for (int i =0; i<groups.size(); i++) {
		groupUsers = groups.at(i).getUsers();

		for (int j=0; j<groupUsers.size(); j++) {
			if (groupUsers.at(j).getId() == userId) {
				return groups.at(i).getDiscount();
			}
		}
	}

	return discount;
}

void updateUserGroupID(vector<User> groupUsers) {
	ofstream temp;

	printUsers(groupUsers);
	temp.open("temp.txt");

	vector<User> users;
	users = getUsersFromFile("users.txt");

	for (int i=0; i < users.size(); i++) {

		for (int j=0; j < groupUsers.size(); j++) {
			if (users.at(i).getId() == groupUsers.at(j).getId() && groupUsers.at(j).getGroupID() != 0) {
				users.at(i).setGroupID(groupUsers.at(j).getGroupID());
			}
		}

	}


	saveUsersToFile(users, "temp.txt");

	remove("users.txt");
	rename("temp.txt", "users.txt");

}

ostream& operator<<(ostream& os, User* user) {

	if (user->getGroupID() != 0) {
		os << "ID: " << user->getId() << "\nFirst name: " << user->firstName << "\nLast name: " <<
					user->lastName << "\nGroup ID: " << user->getGroupID() << endl;
		return os;
	}

	os << "ID: " << user->getId() << "\nFirst name: " << user->firstName << "\nLast name: " <<
				user->lastName << endl;

	return os;
}

void saveUsersToFile(vector<User> users, string filePath) {
	ofstream file;
	file.open(filePath, std::ofstream::out | std::ofstream::app);

	for (int i = 0; i<users.size(); i++){
		file << &users.at(i);
		file << "/// line separator" << endl;

	}

    file.close();
}

vector<User> getUsersFromFile(string filePath) {

	string str;

	int counter = 0;

	User *user = new User();
	vector<User> users;

	ifstream MyReadFile(filePath);

	while(getline (MyReadFile, str)) {


		if (str == "/// line separator") {
			users.push_back(*user);
			counter = 0;
			continue;
		}

		string line = "";

		line = str.substr(str.find(":") + 2 , str.length());

		switch(counter) {
		case 0:
			user->setId(stoi(line));
			break;
		case 1:
			user->setFirstName(line);
			break;
		case 2:
			user->setLastName(line);
			break;
		}

		counter++;

	}

	return users;
}

User* getUserById(int id) {

	User *user;
	vector<User> allUsers;
	allUsers = getUsersFromFile("users.txt");

	for (int i = 0; i < allUsers.size(); i++) {
		if (allUsers.at(i).getId() == id) {
			user = &allUsers.at(i);
			return user;
		}
	}

	return NULL;
}

void printUsers(vector<User> users) {

	for (int i = 0; i<users.size(); i++){
		cout << &users.at(i) << endl;
	}
}

User* createUser() {

	int id;
	string firstName;
	string lastName;

	cout << "Enter user id: ";
	cin >> id;

	cout << "Enter user first Name: \n";
	cin >> firstName;

	cout << "Enter user last Name: \n";
	cin >> lastName;

	bool ifExist = getUserById(id) != NULL;

	if (ifExist) {
		throw("User already exists.");
	}

	return new User(id, firstName, lastName);
}


