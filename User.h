/*
 * User.h
 *
 *  Created on: Mar 20, 2021
 *      Author: t.todorov
 */

#ifndef USER_H_
#define USER_H_

#include <string>
using namespace std;
#include "BaseEntity.h"


class User : public BaseEntity {

private:
	string firstName;
	string lastName;
	int groupID;

public:

	~User();
	User();

	User(int id, string firstName, string lastName):BaseEntity(id) {
		this -> firstName = firstName;
		this -> lastName = lastName;
		this -> groupID = 0;
	}

	string getFirstName();

	string getLastName();

	int getGroupID();

	void setFirstName(string firstname);

	void setLastName(string lastName);

	void setGroupID(int groupID);

	friend ostream& operator<<(ostream& os, User* user);
};

void saveUsersToFile(vector<User> users, string filePath);

vector<User> getUsersFromFile(string filePath);

User* getUserById(int id);

void printUsers(vector<User> users);

User* createUser();

double getUserDiscount(int userId);

void updateUserGroupID(vector<User> groupUsers) ;

#endif /* USER_H_ */
