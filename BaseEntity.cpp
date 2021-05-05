/*
 * BaseEntity.cpp
 *
 *  Created on: May 4, 2021
 *      Author: t.todorov
 */
#include "BaseEntity.h"

BaseEntity::BaseEntity(){

}

BaseEntity::BaseEntity(int id){
	this->id = id;
}

BaseEntity::~BaseEntity() {

}

int	BaseEntity::getId() {
	return id;
}

void BaseEntity::setId(int id) {
	this -> id = id;
}

