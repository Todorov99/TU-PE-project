/*
 * Group.h
 *
 *  Created on: Mar 20, 2021
 *      Author: t.todorov
 */

#ifndef GROUP_H_
#define GROUP_H_

#include <vector>
#include <string>
using namespace std;
#include "BaseEntity.h"
#include "User.h"

class Group : public BaseEntity {

private:
	string groupName;
	double discount;
	vector<User> users;

public:

	~Group();
	Group();

	Group(int id, string groupName, double discount, vector<User> users):BaseEntity(id) {
				this -> groupName = groupName;
				this -> discount = discount;
				this -> users = users;
	}

	Group(int id, string groupName, double discount):BaseEntity(id) {
			this -> groupName = groupName;
			this -> discount = discount;
	}

	string getGroupName();

	double getDiscount();

	vector<User> getUsers();

	void setGroupName(string groupName);

	void setDiscount(double discount);

	void setUsers(vector<User> users);

	friend ostream& operator<<(ostream& os, Group* group);
};


void saveGroupsToFile(vector<Group> groups, string filePath);

vector<Group> getGroupsFromFile(string filePath);

void printGroups(vector<Group> groups);

Group* createGroup();

Group* getGroupById();

#endif /* GROUP_H_ */
