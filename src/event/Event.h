/*
 * Event.h
 *
 *  Created on: 12/05/2015
 *      Author: gandalf
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include <functional>

namespace event {


class Event {
public:
	Event(int value ) { this->val = value; }
	virtual ~Event() { };
	void SetValue(int value) { this->val = value; }
	int GetValue() { return this->val; }

private:
	int val;
};

} /* namespace event */

#endif /* EVENT_H_ */
