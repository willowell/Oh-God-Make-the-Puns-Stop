/*
 * Object.h
 *
 *  Created on: Oct. 31, 2019
 *      Author: whowell
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <string>

namespace whowell {

class Object {
public:
	Object();

	virtual ~Object();

	Object(const Object &other);

	Object(Object &&other);

	friend std::ostream& operator << (std::ostream& out_stream, Object& obj);

	virtual std::string to_string() const;
};

} /* namespace whowell */

#endif /* OBJECT_H_ */
