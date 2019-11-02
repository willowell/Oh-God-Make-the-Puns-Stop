/*
 * Object.cpp
 *
 *  Created on: Oct. 31, 2019
 *      Author: whowell
 */

#include "Object.h"

namespace whowell {

Object :: Object() {
	// TODO Auto-generated constructor stub

}

Object :: ~Object() {
	// TODO Auto-generated destructor stub
}

Object :: Object( const Object &other ) {
	// TODO Auto-generated constructor stub

}

Object :: Object( Object &&other ) {
	// TODO Auto-generated constructor stub

}

std::ostream& operator << ( std::ostream& out_stream, Object& obj ) {
	out_stream << obj.to_string();

	return out_stream;
}

std::string Object :: to_string() const {
	return std::string("Object [" + this + "]");
}

} /* namespace whowell */
