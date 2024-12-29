// Created by: Cian McNamara (cian@telecomeireann.ie), December 28th 2024

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

superint* superint::Add(superint* siNumber1, superint* siNumber2) {
	superint* siResult = new superint();

	superint* usiNumber1 = new superint(siNumber1->vNumber);
	superint* usiNumber2 = new superint(siNumber2->vNumber);

	// Executes the correct unsigned operation then adds the sign to the result.
	if (siNumber1->IsNegative() && siNumber2->IsNegative()) {
		siResult = _uAdd(usiNumber1, usiNumber2);
		siResult->_isNegative = true;
	} else if (!siNumber1->IsNegative() && !siNumber2->IsNegative()) {
		siResult = _uAdd(usiNumber1, usiNumber2);
		siResult->_isNegative = false;
	} else {
		if (IsGreater(usiNumber2, usiNumber1) && siNumber2->IsNegative()) {
			siResult = _uSub(usiNumber2, usiNumber1);
			siResult->_isNegative = true;
		} else if (IsGreater(usiNumber2, usiNumber1) && !siNumber2->IsNegative()) {
			siResult = _uAdd(usiNumber2, usiNumber1);
			siResult->_isNegative = false;
		} else if (IsGreater(usiNumber1, usiNumber2) && !siNumber2->IsNegative()) {
			siResult = _uSub(usiNumber1, usiNumber2);
			siResult->_isNegative = false;
		} else {
			siResult = _uSub(usiNumber1, usiNumber2);
			siResult->_isNegative = true;
		}
	}

	siResult->format();

	return siResult;
}

superint* superint::_uAdd(superint* usiNumber1, superint* usiNumber2) {
	superint* usiResult = new superint();

	if (usiNumber1->vNumber.size() < usiNumber2->vNumber.size()) {
		std::swap(usiNumber1->vNumber, usiNumber2->vNumber);
	}

	for (int i = 0; i < usiNumber1->vNumber.size(); i++) {
		if (i < usiNumber2->vNumber.size()) {
			usiResult->vNumber[i] = usiNumber1->vNumber[i] + usiNumber2->vNumber[i];
		} else {
			usiResult->vNumber[i] = usiNumber1->vNumber[i];
		}
	}

	usiResult->format();

	return usiResult;
}

superint* superint::Sub(superint* siNumber1, superint* siNumber2) {
	superint* siResult = new superint();

	siNumber2->_isNegative = !siNumber2->_isNegative;

	siResult = Add(siNumber1, siNumber2);

	return siResult;
}

superint* superint::_uSub(superint* usiNumber1, superint* usiNumber2) {
	superint* usiResult = new superint();

	// Ladies and gentlemen, lets not sign the unsigned.
	if (IsLesser(usiNumber1, usiNumber2)) {
		throw std::exception("LHS is less than RHS.");
	}

	// Takes the two numbers away from eachother at each index.
	for (int i = 0; i < usiNumber1->vNumber.size(); i++) {
		if (i < usiNumber2->vNumber.size()) {
			usiResult->vNumber[i] = usiNumber1->vNumber[i] - usiNumber2->vNumber[i];
		} else {
			usiResult->vNumber[i] = usiNumber1->vNumber[i];
		}
	}

	usiResult->format();

	return usiResult;
}

superint* superint::Mult(superint* siNumber1, superint* siNumber2) {
	superint* siResult = new superint();

	if (siNumber1->vNumber.size() < siNumber2->vNumber.size()) {
		std::swap(siNumber1->vNumber, siNumber2->vNumber);
	}

	for (int offset = 0; offset < siNumber1->vNumber.size(); offset++) {
		superint* siTemp = new superint();

		for (int i = 0; i < siNumber2->vNumber.size(); i++) {
			int selection_a = siNumber1->vNumber[offset];
			int selection_b = siNumber2->vNumber[i];
			siTemp->insertAtLocation(i + offset, selection_a * selection_b);
		}

		siTemp->format();
		siResult = Add(siResult, siTemp);
	}

	siResult->format();

	if (siNumber2->IsNegative() && !siNumber1->IsNegative()) {
		siResult->_isNegative = true;
	} else if (!siNumber2->IsNegative() && siNumber1->IsNegative()) {
		siResult->_isNegative = true;
	} else {
		siResult->_isNegative = false;
	}

	return siResult;
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