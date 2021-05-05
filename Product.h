/*
 * Product.h
 *
 *  Created on: Mar 20, 2021
 *      Author: t.todorov
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_

#define PRODUCT_FILE "products.txt";

#include <vector>
#include <string>
using namespace std;
#include "BaseEntity.h"
#include "User.h"

class Product : public BaseEntity {
private:
	string name;
	string type;
	string description;
	double price;
	int quantity;

public:

	~Product();

	Product();

	Product(int id, string name, string type, string description, double price, int quantity) : BaseEntity(id) {
		this -> name = name;
		this -> type = type;
		this -> description = description;
		this -> price = price;
		this -> quantity = quantity;
	}

	string getName();

	string getType();

	string getDescription();

	double getPrice();

	int getQuantity();

	void setName(string name);

	void setType(string type);

	void setDescription(string description);

	void setPrice(double price);

	void setQuantity(int quantity);

	void updateProductQuantity();

	friend ostream& operator<<(ostream& os, Product* product);
};

void saveProductsToFile(vector<Product> products, string filePath);

void printProducts(vector<Product> products);

double getSumOfProducts(vector<Product> products);

vector<Product> addProductsInShoppingCart();

//void updateProductQuantity(int id, int quantity);

Product* createProduct();

Product* getProductById(int id);

vector<Product> getProductsFromFile(string filePath);

#endif /* PRODUCT_H_ */
