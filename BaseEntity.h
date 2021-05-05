/*
 * BaseEntity.h
 *
 *  Created on: May 4, 2021
 *      Author: t.todorov
 */

#ifndef BASEENTITY_H_
#define BASEENTITY_H_


class BaseEntity {

private:
	int id;

public:

	~BaseEntity();

	BaseEntity();
	BaseEntity(int id);


	int getId();

	void setId(int id);
};



#endif /* BASEENTITY_H_ */
