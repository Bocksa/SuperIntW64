// Created by: Cian McNamara, December 28th 2024

#include <vector>
#include <string>

#include "pch.h"
#include "framework.h"
#include "superint.h"

using namespace SuperIntW64;

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

superint::superint(std::vector<int> vNumber) {
	this->vNumber = vNumber;
	this->_isNegative = false;

	format();

	this->_isReady = true;
}

superint::superint(std::vector<int> vNumber, bool isNegative) {
	this->vNumber = vNumber;
	this->_isNegative = isNegative;

	format();

	this->_isReady = true;
}

// Methods
std::string superint::ToString() {
	std::string sNumber = "";

	if (this->_isNegative) {
		sNumber += "-";
	}

	for (int i = vNumber.size() - 1; i >= 0; i--) {
		sNumber += std::to_string(vNumber[i]);
	}

	return sNumber;
}

superint* superint::Add(superint siNumber1, superint siNumber2) {
	superint* siResult = new superint();

	std::vector<int> vResult;
	std::vector<int> vNumber1 = siNumber1.GetVector();
	std::vector<int> vNumber2 = siNumber2.GetVector();

	// Swap the two numbers so vNumber1 is always the larger number.
	if (vNumber1.size() < vNumber2.size()) {
		std::swap(vNumber1, vNumber2);
	}

	// Add every index together.
	for (int i = 0; i < vNumber1.size(); i++) {
		if (i < vNumber2.size()) {
			vResult.push_back(vNumber1[i] + vNumber2[i]);
		} else {
			vResult.push_back(vNumber1[i]);
		}
	}

	siResult->vNumber = vResult;

	return siResult;
}

superint* superint::_uAdd(superint usiNumber1, superint usiNumber2) {
	superint* usiResult = new superint();

	if (usiNumber1.vNumber.size() < usiNumber2.vNumber.size()) {
		std::swap(usiNumber1.vNumber, usiNumber2.vNumber);
	}

	for (int i = 0; i < usiNumber1.vNumber.size(); i++) {
		if (i < usiNumber2.vNumber.size()) {
			usiResult->vNumber[i] = usiNumber1.vNumber[i] + usiNumber2.vNumber[i];
		} else {
			usiResult->vNumber[i] = usiNumber1.vNumber[i];
		}
	}

	usiResult->format();

	return usiResult;
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