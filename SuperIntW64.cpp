// Cian McNamara, 2024

#include <vector>
#include <string>

#include "pch.h"
#include "framework.h"
#include "SuperIntW64.h"

using superint = SuperIntW64::superint;

// Properties
const bool superint::IsNegative() {
	return this->_isNegative;
}

const bool superint::IsReady() {
	return this->_isReady;
}

// Constructors
superint::superint() {
	this->_isNegative = false;
	this->_isReady = true;
	this->vNumber = { 0 };
}
superint::superint(std::string sNumber) {
	this->_isNegative = isNumberNegative(sNumber);

	// If the number is negative remove the minus sign from the start of the string.
	if (IsNegative()) {
		sNumber = sNumber.erase(0, 1);
	}

	// If it is a valid number, place the numbers into the vector in reverse order.
	if (isValidNumber(sNumber)) {
		for (int i = sNumber.length() - 1; i >= 0; i--) {
			vNumber.push_back(sNumber[i] - '0');
		}

		this->_isReady = true; // Set the state of the number to ready.
	} else {
		throw std::exception("Invalid number");
	}
}

// Methods
std::string superint::toString() {
	std::string sNumber = "";

	if (this->_isNegative) {
		sNumber += "-";
	}

	for (int i = vNumber.size() - 1; i >= 0; i--) {
		sNumber += std::to_string(vNumber[i]);
	}

	return sNumber;
}

bool superint::isValidNumber(std::string sNumber) {
	if (sNumber.size() >= 1) {
		for (int i = 0; i < sNumber.length(); i++) {
			if (sNumber[i] < '0' || sNumber[i] > '9') {
				return false;
			}
		}

		return true;
	} else {
		return false;
	}
}

bool superint::isNumberNegative(std::string sNumber) {
	if (sNumber[0] == '-') {
		return true;
	} else {
		return false;
	}
}