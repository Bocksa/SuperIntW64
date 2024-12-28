// SuperIntW64.cpp : Defines the functions for the static library.
//
#include <vector>
#include <string>
#include "pch.h"
#include "framework.h"
#include "SuperIntW64.h"

using superint = SuperIntW64::superint;

// Properties
const bool superint::isNegative() {
	return this->_isNegative;
}

const bool superint::isReady() {
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

	if (isNegative()) {
		sNumber = sNumber.erase(0, 1);
	}

	if (isValidNumber(sNumber)) {
		vNumber.clear();

		for (int i = sNumber.length() - 1; i >= 0; i--) {
			vNumber.push_back(sNumber[i] - '0');
		}

		this->_isReady = true;
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