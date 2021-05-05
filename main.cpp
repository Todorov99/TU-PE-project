/*
 * main.cpp
 *
 *  Created on: Mar 20, 2021
 *      Author: t.todorov
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "User.h"
#include "Product.h"
#include "Group.h"


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
	cout<< "Buy products with concrete user<10>\n";
	cout<< "Exit<0>\n";
	cout << "***************************************\n";

}

int main() {

	int option;
	User *userForShopping;
	vector<Product> newProducts;
	vector<User> newUsers;
	vector<Group> newGroups;

	User *user;
	Product *product;
	vector<User> users;
	vector<Product> products;
	vector<Group> groups;
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

			try {
				user = createUser();
			}catch(const char* ex) {
				cout << ex << endl;
				break;
			}

			cout << "Created user: \n";
			cout << user;

			newUsers.push_back(*user);

			menu();

			break;
		case 2:

			if (newUsers.size() == 0) {
				cout << "There is not any users to save" << endl;
				break;
			}

			saveUsersToFile(newUsers, "users.txt");
			newUsers.clear();
			menu();

			break;
		case 3:

			try {
				product = createProduct();
			}catch(const char* ex) {
				cout << ex << endl;
				break;
			}

			cout << "Created product: \n";
			cout << product;

			newProducts.push_back(*product);

			menu();

			break;
		case 4:

			if (newProducts.size() == 0) {
				cout << "There is not any products to save" << endl;
				break;
			}

			saveProductsToFile(newProducts, "products.txt");
			newProducts.clear();
			menu();

			break;
		case 5:

			try {
				group = createGroup();
			}catch(const char* ex) {
				cout << ex << endl;
				break;
			}

			newGroups.push_back(*group);

			cout << group;

			menu();

			break;
		case 6:

			if (newGroups.size() == 0) {
				cout << "There is not any groups to save" << endl;
				break;
			}

			saveGroupsToFile(newGroups, "groups.txt");
			newGroups.clear();
			menu();

			break;
		case 7:

			users = getUsersFromFile("users.txt");
			printUsers(users);

			menu();

			break;
		case 8:
			groups = getGroupsFromFile("groups.txt");
			printGroups(groups);

			menu();
			break;
		case 9:

			products = getProductsFromFile("products.txt");
			printProducts(products);

			menu();

			break;
		case 10:
			int id;
			cout << "Enter user ID for shopping: " << endl;
			cin >> id;

			userForShopping = getUserById(id);

			cout << userForShopping;

			cout << "Discount: " << getUserDiscount(userForShopping->getId()) << endl;

			vector<Product> cartProducts;
			double sumOfProducts = 0;
			double finalPrice = 0;

			cartProducts = addProductsInShoppingCart();

			printProducts(cartProducts);

			sumOfProducts = getSumOfProducts(cartProducts);

			cout << "Sum of the products in your cart is " << sumOfProducts << endl;

			finalPrice = getSumOfProducts(cartProducts) * (getUserDiscount(userForShopping->getId()) / 100);

			cout << "With discount of " << getUserDiscount(userForShopping->getId()) << "% you pay: " << finalPrice << "lv"<< endl;

			menu();
			break;
		}

		cout << "Enter option: \n";
		cin >> option;
	}


	cout << "Exit successfully\n";

    return 0;
}





