/*
 * Group.cpp
 *
 *  Created on: Mar 20, 2021
 *      Author: t.todorov
 */


#include "Group.h"
#include <iostream>
#include <fstream>

Group::~Group(){};

Group::Group(){};

string Group::getGroupName() {
	return this->groupName;
}

double Group::getDiscount() {
	return this -> discount;
}

vector<User> Group::getUsers() {
	return this -> users;
}

void Group::setGroupName(string groupName) {
	this->groupName = groupName;
}

void Group::setDiscount(double discount) {
	this -> discount = discount;
}

void Group::setUsers(vector<User> users){
	this -> users = users;
}

ostream& operator<<(ostream& os, Group* group) {

	os << "Group ID: " << group->getId() << "\nGroup name: " << group->groupName << "\nDiscount: " <<
			group->discount << endl;

	os << "Group Users: " << endl;

	for (int i = 0; i < group->users.size(); i++) {
		os << &group->users.at(i);
	}

	return os;
}

void saveGroupsToFile(vector<Group> groups, string filePath) {
	ofstream file;
	file.open(filePath,std::ofstream::out | std::ofstream::app);

	for (int i = 0; i<groups.size(); i++){
		file << &groups.at(i);
		file << "/// line separator" << endl;
	}

    file.close();
}

vector<Group> getGroupsFromFile(string filePath) {

	bool isUser;
	string str;

	int counter = 0;
	int userCount = 0;

	Group *group = new Group();
	vector<Group> groups;
	vector<User> groupUsers;
	User *currentGroupUser = new User();

	ifstream MyReadFile(filePath);

	while(getline (MyReadFile, str)) {

		if (str == "/// line separator") {
			group -> setUsers(groupUsers);
			groups.push_back(*group);
			counter = 0;
			userCount = 0;
			isUser = false;
			userCount = 0;
			currentGroupUser = new User();
			continue;
		}

		if (userCount - 1 == 3) {
			userCount = 0;
		}

		string line = "";
		line = str.substr(str.find(":") + 2 , str.length());

		if (str == "Group Users: ") {

			isUser = true;
			continue;
		}

		switch(counter) {
		case 0:
			group->setId(stoi(line));
			break;
		case 1:
			group->setGroupName(line);
			break;
		case 2:
			group->setDiscount(stod(line));
			break;

		}

		if (isUser) {

			switch(userCount) {
			case 0:
				currentGroupUser -> setId(stoi(line));
				break;
			case 1:
				currentGroupUser -> setFirstName(line);
				break;
			case 2:
				currentGroupUser -> setLastName(line);
				break;
			case 3:
				currentGroupUser -> setGroupID(stoi(line));
				groupUsers.push_back(*currentGroupUser);

				break;

			}


			userCount++;

		}

		counter++;
	}

	return groups;
}

void printGroups(vector<Group> groups) {

	for (int i = 0; i<groups.size(); i++){
		cout << &groups.at(i) << endl;
	}
}
Group* getGroupById(int id) {
	Group *group;
	vector<Group> allGroups;
	allGroups = getGroupsFromFile("groups.txt");

	for (int i = 0; i < allGroups.size(); i++) {
		if (allGroups.at(i).getId() == id) {
			group = &allGroups.at(i);
			return group;
		}
	}

	return NULL;
}

Group* createGroup() {
	cout << "Creating new Group\n";

	int userId;

	int id;
	string name;
	double discount;

	vector<User> allUsers;
	vector<User> groupUsers;

	allUsers = getUsersFromFile("users.txt");

	cout << "Enter group id: ";
	cin >> id;

	bool ifGroupExists = getGroupById(id) != NULL;

	if (ifGroupExists) {
		throw "Group with current id already exists";
	}

	cout << "Enter group name: \n";
	cin.ignore();
	getline(cin, name);

	cout << "Enter discount: \n";

	cin >> discount;

	cout << "Add group users: " << endl;

	cout << "All available users: " << endl;

	printUsers(allUsers);

	cout << "Exit from choose user menu<0>" << endl;

	cout << "Chose users id for the group: " << endl;

	cin >> userId;

	while(true) {

		if (userId == 0) {
			break;
		}

		User *user = new User();
		user = getUserById(userId);

		bool ifUserExists = user == NULL;

		if (ifUserExists) {
			throw "User with current id does not exists";
		}

		user->setGroupID(id);

	//	user->updateUserGroupID(id);

		groupUsers.push_back(*user);
		cout << "Chose users id for the group: " << endl;

		cin >> userId;
	}

	updateUserGroupID(groupUsers);
	return new Group(id, name, discount, groupUsers);
}


