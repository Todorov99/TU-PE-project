/*
 * main.cpp
 *
 *  Created on: Mar 20, 2021
 *      Author: t.todorov
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class BaseEntity {

private:
	int id;

public:

	BaseEntity(){};

	BaseEntity(int id){
		this -> id = id;
	}

	int getId() {
		return this -> id;
	}

	void setId(int id) {
		this -> id = id;
	}

};

class User : public BaseEntity {

private:
	string firstName;
	string lastName;

public:

	User(){};

	User(int id, string firstName, string lastName):BaseEntity(id) {
		this -> firstName = firstName;
		this -> lastName = firstName;
	}

	string getFirstName() {
		return this->firstName;
	}

	string getLastName() {
		return this->lastName;
	}

	void setFirstName(string firstname) {
		this->firstName = firstname;
	}

	void setLastName(string lastName) {
		this->lastName = lastName;
	}

	friend ostream& operator<<(ostream& os, User* user);
};


ostream& operator<<(ostream& os, User* user) {

	os << "ID: " << user->getId() << "\nFirst name: " << user->firstName << "\nLast name: " <<
			user->lastName << endl;

	return os;
}


class Group : public BaseEntity {

private:
	string groupName;
	double discount;
	vector<User> users;

public:

	Group(){};

	Group(int id, string groupName, double discount, vector<User> users):BaseEntity(id) {
				this -> groupName = groupName;
				this -> discount = discount;
				this -> users = users;
	}

	Group(int id, string groupName, double discount):BaseEntity(id) {
			this -> groupName = groupName;
			this -> discount = discount;
	}

	string getGroupName() {
		return this->groupName;
	}

	double getDiscount() {
		return this -> discount;
	}

	vector<User> getUsers() {
		return this -> users;
	}

	void setGroupName(string groupName) {
		this->groupName = groupName;
	}

	void setDiscountName(double discount) {
		this -> discount = discount;
	}

	void setUsers(vector<User> users){
		this -> users = users;
	}

	friend ostream& operator<<(ostream& os, Group* group);
};



ostream& operator<<(ostream& os, Group* group) {

	os << "Group ID: " << group->getId() << "\nGroup name: " << group->groupName << "\nDiscount: " <<
			group->discount << endl;

	os << "Group Users: " << endl;

	for (int i = 0; i < group->users.size(); i++) {
		os << &group->users.at(i);
	}

	return os;
}

class Product : public BaseEntity {
private:
	string name;
	string type;
	string description;
	double price;

public:
	Product(){};

	Product(int id, string name, string type, string description, double price) : BaseEntity(id) {
		this -> name = name;
		this -> type = type;
		this -> description = description;
		this -> price = price;
	}

	string getName() {
		return this -> name;
	}

	string getType() {
		return this -> type;
	}

	string getDescription() {
		return this -> description;
	}

	double getPrice() {
		return this -> price;
	}

	void setName(string name) {
		this -> name = name;
	}

	void setType(string type) {
		this -> type = type;
	}

	void setDescription(string description) {
		this -> description = description;
	}

	void setPrice(double price) {
		this -> price = price;
	}

	friend ostream& operator<<(ostream& os, Product* product);
};

ostream& operator<<(ostream& os, Product* product) {

	os << "ID: " << product->getId() << "\nProduct name: " << product->name <<
			"\nType: " << product->type << "\nDescription: " << product -> description <<
			"\nPrice: " << product->price << endl;

	return os;
}


void saveUsersToFile(vector<User> users, string filePath) {
	cout << "Saving users into " << filePath << "file" << endl;

	ofstream file;
	file.open(filePath, std::ofstream::out | std::ofstream::app);

	for (int i = 0; i<users.size(); i++){
		file << &users.at(i);
		file << "/// line separator" << endl;

		cout << "User: " << &users.at(i) << "successfully saved!\n";
	}

    file.close();


}

void saveGroupsToFile(vector<Group> groups, string filePath) {
	cout << "Saving groups into " << filePath << "file" << endl;

	ofstream file;
	file.open(filePath,std::ofstream::out | std::ofstream::app);

	for (int i = 0; i<groups.size(); i++){
		file << &groups.at(i);
		file << "/// line separator" << endl;

		cout << "Group: " << &groups.at(i) << "successfully saved!\n";
	}

    file.close();
}

void saveProductsToFile(vector<Product> products, string filePath) {
	cout << "Saving products into " << filePath << "file" << endl;

	ofstream file;
	file.open(filePath, std::ofstream::out | std::ofstream::app);

	for (int i = 0; i<products.size(); i++){
		file << &products.at(i);
		file << "/// line separator" << endl;

		cout << "Product: " << &products.at(i) << "successfully saved!\n";
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

vector<Product> getProductsFromFile(string filePath) {

	string str;

	int counter = 0;

	Product *product = new Product();
	vector<Product> products;

	ifstream MyReadFile(filePath);

	while(getline (MyReadFile, str)) {


		if (str == "/// line separator") {
			products.push_back(*product);
			counter = 0;
			continue;
		}

		string line = "";
		line = str.substr(str.find(":") + 2 , str.length());

		switch(counter) {
		case 0:
			product->setId(stoi(line));
			break;
		case 1:
			product->setName(line);
			break;
		case 2:
			product->setType(line);
			break;
		case 3:
			product->setDescription(line);
			break;
		case 4:
			product->setPrice(stod(line));
			break;
		}

		counter++;

	}

	return products;
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

void printGroups(vector<Group> groups) {

	for (int i = 0; i<groups.size(); i++){
		cout << &groups.at(i) << endl;
	}
}

void printProducts(vector<Product> products) {

	for (int i = 0; i<products.size(); i++){
		cout << &products.at(i) << endl;
	}
}

User* createUser() {
	cout << "Creating new User\n";

	int id;
	string firstName;
	string lastName;

	cout << "Enter user id: ";
	cin >> id;

	cout << "Enter user first Name: \n";
	cin.ignore();
	getline(cin, firstName);

	cout << "Enter user last Name: \n";
	cin.ignore();
	getline(cin, lastName);

	return new User(id, firstName, lastName);

}

Product* createProduct() {
	cout << "Creating new Product\n";

	int id;
	string name;
	string type;
	string description;
	double price;

	cout << "Enter product id: ";
	cin >> id;

	cout << "Enter product name: \n";
	cin.ignore();
	getline(cin, name);

	cout << "Enter product type: \n";
	cin.ignore();
	getline(cin, name);

	cout << "Enter product description: \n";
	cin.ignore();
	getline(cin, name);

	cout << "Enter product price: \n";
	cin >>  price;

	return new Product(id, name, type, description, price);
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

	cout << "Enter group name: \n";
	cin.ignore();
	getline(cin, name);

	cout << "Enter discount: \n";
	cin.ignore();
	cin >> discount;

	cout << "Add group users: " << endl;

	cout << "All available users: " << endl;

	printUsers(allUsers);

	cout << "Exit from choose user menu<0>" << endl;

	cout << "Chose users id for the group: " << endl;

	cin.ignore();
	cin >> userId;

	while(true) {

		if (userId == 0) {
			break;
		}

		User *user;
		user = getUserById(userId);

		groupUsers.push_back(*user);
		cout << "Chose users id for the group: " << endl;
		cin.ignore();
		cin >> userId;
	}


	return new Group(id, name, discount, groupUsers);

}

void menu() {

	cout << "***************************************\n";
	cout << "College cafeteria menu\n";
	cout << "***************************************\n";
	cout<< "Create user <1>\n";
	cout<< "Save user in file <2>\n";
	cout<< "Create product <3>\n";
	cout<< "Save product in file <4>\n";
	cout<< "Create group <5>\n";
	cout<< "Save group in file <6>\n";
	cout<< "See all users <7>\n";
	cout<< "See all groups <8>\n";
	cout<< "See all products <9>\n";
	cout<< "Buy product with concrete user<10>\n";
	cout<< "Exit<0>\n";
	cout << "***************************************\n";

}

//TODO add validation for different objects values
//TODO validate for existing users, groups, products by ID when creating new ones
//TODO implement getting all groups
//TODO implement buying product

int main() {

	int option;

	vector<Product> newProducts;
	vector<User> newUsers;
	vector<Group> newGroups;

	User *user;
	Product *product;
	vector<User> users;
	vector<Product> products;
	Group *group;

	menu();

	cout << "Enter option: \n";
	cin >> option;

	while(true) {

		if (option == 0) {
			break;
		}

		switch (option) {
		case 1:

			user = createUser();

			cout << "Created user: \n";
			cout << user;

			newUsers.push_back(*user);

			menu();

			break;
		case 2:

			saveUsersToFile(newUsers, "users.txt");

			menu();

			break;
		case 3:

			product = createProduct();

			cout << "Created product: \n";
			cout << product;

			newProducts.push_back(*product);

			menu();

			break;
		case 4:

			saveProductsToFile(newProducts, "products.txt");

			menu();

			break;
		case 5:

			group = createGroup();
			newGroups.push_back(*group);

			cout << group;

			menu();

			break;
		case 6:

			saveGroupsToFile(newGroups, "groups.txt");

			menu();

			break;
		case 7:

			users = getUsersFromFile("users.txt");
			printUsers(users);

			menu();

			break;
		case 8:
			cout << "Option 8\n";
			break;
		case 9:

			products = getProductsFromFile("products.txt");
			printProducts(products);

			menu();

			break;
		case 10:
			cout << "Option 10\n";

			menu();
			break;
		}

		cout << "Enter option: \n";
		cin >> option;
	}


	cout << "Exit successfully\n";

    return 0;
}





