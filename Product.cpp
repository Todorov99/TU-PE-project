/*
 * Product.cpp
 *
 *  Created on: Mar 20, 2021
 *      Author: t.todorov
 */

#include "Product.h"
#include <iostream>
#include <fstream>

const string productFile = "product.txt";

Product::~Product(){};

Product::Product(){};


string Product::getName() {
	return this -> name;
}

string Product::getType() {
	return this -> type;
}

string Product::getDescription() {
	return this -> description;
}

double Product::getPrice() {
	return this -> price;
}

int Product::getQuantity() {
	return this -> quantity;
}

void Product::setName(string name) {
	this -> name = name;
}

void Product::setType(string type) {
	this -> type = type;
}

void Product::setDescription(string description) {
	this -> description = description;
}

void Product::setPrice(double price) {
	this -> price = price;
}

void Product::setQuantity(int quantity) {
	this -> quantity = quantity;
}

void Product::updateProductQuantity() {
	ofstream temp;

	temp.open("temp.txt");

	vector<Product> products;
	products = getProductsFromFile("products.txt");


	for (int i=0; i < products.size(); i++) {

		if (products.at(i).getId() == this->getId()) {
			products.at(i).setQuantity(this->getQuantity());
		}

	}

	saveProductsToFile(products, "temp.txt");

	remove("products.txt");
	rename("temp.txt", "products.txt");

}

ostream& operator<<(ostream& os, Product* product) {

	os << "ID: " << product->getId() << "\nProduct name: " << product->name <<
			"\nType: " << product->type << "\nDescription: " << product -> description <<
			"\nPrice: " << product->price << "\nQuantity: " << product -> quantity <<endl;

	return os;
}

void saveProductsToFile(vector<Product> products, string filePath) {
	ofstream file;
	file.open(filePath, std::ofstream::out | std::ofstream::app);

	for (int i = 0; i<products.size(); i++){
		file << &products.at(i);
		file << "/// line separator" << endl;

	}

    file.close();
}


void printProducts(vector<Product> products) {

	for (int i = 0; i<products.size(); i++){
		cout << &products.at(i) << endl;
	}
}

double getSumOfProducts(vector<Product> products) {

	double sumOfProducts = 0;

	for (int i =0; i < products.size(); i++) {
		sumOfProducts += products.at(i).getPrice() * products.at(i).getQuantity();
	}

	return sumOfProducts;
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
		case 5:
			product->setQuantity(stoi(line));
			break;
		}

		counter++;

	}

	return products;
}

Product* getProductById(int id) {

	Product *product;
	vector<Product> allProducts;
	allProducts = getProductsFromFile("products.txt");

	for (int i = 0; i < allProducts.size(); i++) {
		if (allProducts.at(i).getId() == id) {
			product = &allProducts.at(i);
			return product;
		}
	}

	return NULL;
}

Product* createProduct() {

	int id;
	string name;
	string type;
	string description;
	double price;
	int quantity;

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

	cout << "Enter product quantity: \n";
    cin >>  quantity;

    bool ifExists = getProductById(id) != NULL;

    if (ifExists) {
    	throw("Product already exists");
    }

	return new Product(id, name, type, description, price, quantity);
}

vector<Product> addProductsInShoppingCart() {
	vector<Product> products;

	Product *product;

	int productId = 0;
	int productQuantity = 0;
	int option;


	cout << "Press 1 to choose product for shopping cart" << endl;
	cout << "Press 0 to exit from shopping cart" << endl;

	while (true) {

		cout << "Enter option: \n";
		cin >> option;

		if (option != 0 && option != 1) {
			cout << "Invalid option" << endl;
			continue;
		}

		if (option == 0) {
			break;
		}

		cout << "Enter product ID: " << endl;
		cin >> productId;

		product = getProductById(productId);

		if (product == NULL) {
			cout << "There is not such product! Try again" << endl;
			continue;
		}

		cout << "Enter product quantity: " << endl;
		cin >> productQuantity;

		if (productQuantity > product->getQuantity()) {
			cout << "Not enough quantity";
			continue;
		}

		Product *cartProduct = new Product(product->getId(), product->getName(), product->getType(), product->getDescription(), product->getPrice(), productQuantity);
		products.push_back(*cartProduct);

		product->setQuantity(product->getQuantity() - productQuantity);

		product->updateProductQuantity();
	}

	return products;
}
