// Created by: Cian McNamara (cian@telecomeireann.ie), December 28th 2024

#include <vector>
#include <string>

#include "pch.h"
#include "framework.h"
#include "superint.h"
#include "supermath.h"

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
}

superint::superint(std::string sNumber) {
	sInit(sNumber);
}

superint::superint(long lNumber) {
	sInit(std::to_string(lNumber));
}

superint::superint(std::vector<int>* vNumber) {
	this->vNumber = *vNumber;
	this->_isNegative = false;

	format();

	this->_isReady = true;
}

superint::superint(std::vector<int>* vNumber, bool isNegative) {
	this->vNumber = *vNumber;
	this->_isNegative = isNegative;

	format();

	this->_isReady = true;
}

void superint::sInit(std::string sNumber) {
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

// Public Methods
std::string superint::ToString() {
	std::string sNumber = "";

	if (hasLeadingZeroes()) {
		removeLeadingZeroes();
	}

	if (this->_isNegative) {
		sNumber = sNumber + "-";
	}

	if (vNumber.empty()) {
		sNumber = sNumber + "0";
	}

	for (int i = vNumber.size() - 1; i >= 0; i--) {
		sNumber = sNumber + std::to_string(vNumber[i]);
	}

	return sNumber;
}

std::vector<int> superint::GetVector() {
	return this->vNumber;
}

superint* superint::Add(superint* siNumber1, superint* siNumber2) {
	superint* siResult = new superint();

	// Executes the correct unsigned operation then adds the sign to the result.
	if (!(siNumber1->IsNegative() || siNumber2->IsNegative())) {
		siResult = _uAdd(siNumber1, siNumber2);
		siResult->_isNegative = false;
	} else if (siNumber1->IsNegative() && siNumber2->IsNegative()) {
		siResult = _uAdd(siNumber1, siNumber2);
		siResult->_isNegative = true;
	} else if (siNumber1->IsNegative() && !siNumber2->IsNegative()) {
		siResult = _uSub(siNumber1, siNumber2);
		siResult->_isNegative = true;
	} else if (!siNumber1->IsNegative() && siNumber2->IsNegative()) {
		siResult = _uSub(siNumber1, siNumber2);
		siResult->_isNegative = false;
	}

	return siResult;
}

superint* superint::Sub(superint* siNumber1, superint* siNumber2) {
	superint* siResult = new superint();

	if (!(siNumber1->IsNegative() || siNumber2->IsNegative())) {
		siResult = _uSub(siNumber1, siNumber2);
		siResult->_isNegative = false;
	} else if (siNumber1->IsNegative() && siNumber2->IsNegative()) {
		siNumber2->_isNegative = false;
		siResult = Add(siNumber1, siNumber2);
	} else if (siNumber1->IsNegative() && !siNumber2->IsNegative()) {
		siResult = _uAdd(siNumber1, siNumber2);
		siResult->_isNegative = true;
	} else if (!siNumber1->IsNegative() && siNumber2->IsNegative()) {
		siResult = _uAdd(siNumber1, siNumber2);
		siResult->_isNegative = false;
	}

	return siResult;
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

superint* superint::Div(superint* siNumber1, superint* siNumber2) {
	// x / y = z
	// y * z = x

	// if y < x, answer is 0
	if (IsLesser(siNumber1, siNumber2)) {
		return new superint((long)0);
	}

	// set up our pivots
	superint* min = new superint(1);
	superint* max = siNumber2;
	superint* pivot = supermath::Random(min, max);

	// while y * z != x
	while (!superint::IsEqual(superint::Mult(siNumber2, pivot), siNumber1)) {
		// if y * z + r = x, break out of the loop
		if (superint::IsLesser(superint::Mult(siNumber2, pivot), siNumber1) &&
			(superint::IsGreater(superint::Add(superint::Mult(siNumber2, pivot), siNumber2), siNumber1)
		)) {
			break;
		}

		// if y * z + r != x, adjust the limits of z
		if (superint::IsGreater(superint::Mult(siNumber2, pivot), siNumber1)) {
			max = pivot;
		} else {
			min = pivot;
		}

		// guess z again
		pivot = supermath::Random(min, max);
	}

	if (siNumber2->IsNegative() && siNumber1->IsNegative() || !(siNumber2->IsNegative() || siNumber1->IsNegative())) {
		pivot->_isNegative = false;
	} else {
		pivot->_isNegative = true;
	}

	// y * z = x
	return pivot;
}

superint* superint::Mod(superint* siNumber1, superint* siNumber2) {
	// x / y = z
	// y * z = x

	// if x < y, answer is x
	if (IsLesser(siNumber1, siNumber2)) {
		return siNumber1;
	}

	// set up our pivots
	superint* min = new superint(1);
	superint* max = siNumber2;
	superint* pivot = supermath::Random(min, max);

	// while y * z != x
	while (!superint::IsEqual(superint::Mult(siNumber2, pivot), siNumber1)) {
		// if y * z + r = x, break out of loop, answer found
		if (superint::IsLesser(superint::Sub(siNumber1, pivot), siNumber1)) {
			break;
		}

		// if y * z + r != x, adjust the limits of z
		if (superint::IsGreater(superint::Mult(siNumber2, pivot), siNumber1)) {
			max = pivot;
		} else {
			min = pivot;
		}

		// guess z again
		pivot = supermath::Random(min, max);
	}

	superint* remainder = superint::Sub(siNumber1, pivot);

	if (siNumber2->IsNegative() && siNumber1->IsNegative() || !(siNumber2->IsNegative() || siNumber1->IsNegative())) {
		remainder->_isNegative = false;
	} else {
		remainder->_isNegative = true;
	}

	return remainder;
}

bool superint::IsGreater(superint* siNumber1, superint* siNumber2) {
	if (siNumber2->IsNegative() && !siNumber1->IsNegative()) {
		return true;
	} else if (siNumber1->IsNegative() && !siNumber2->IsNegative()) {
		return false;
	} else if (siNumber1->vNumber.size() > siNumber2->vNumber.size()) {
		return true;
	} else if (siNumber1->vNumber.size() < siNumber2->vNumber.size()) {
		return false;
	} else {
		for (int i = siNumber1->vNumber.size() - 1; i >= 0; i--) {
			if (siNumber1->vNumber[i] > siNumber2->vNumber[i]) {
				return true;
			} else if (siNumber1->vNumber[i] < siNumber2->vNumber[i]) {
				return false;
			}
		}
	}
}

bool superint::IsLesser(superint* siNumber1, superint* siNumber2) {
	if (siNumber1->vNumber.size() < siNumber2->vNumber.size()) {
		return true;
	} else if (siNumber1->vNumber.size() > siNumber2->vNumber.size()) {
		return false;
	} else {
		for (int i = siNumber1->vNumber.size() - 1; i >= 0; i--) {
			if (siNumber1->vNumber[i] < siNumber2->vNumber[i]) {
				return true;
			} else if (siNumber1->vNumber[i] > siNumber2->vNumber[i]) {
				return false;
			}
		}
	}
}

bool superint::IsEqual(superint* siNumber1, superint* siNumber2) {
	if (!IsGreater(siNumber1, siNumber2) && !IsLesser(siNumber1, siNumber2)) {
		return true;
	} else {
		return false;
	}
}

// Private Methods
superint* superint::_uAdd(superint* usiNumber1, superint* usiNumber2) {
	superint* usiResult = new superint();

	if (usiNumber1->vNumber.size() < usiNumber2->vNumber.size()) {
		std::swap(usiNumber1->vNumber, usiNumber2->vNumber);
	}

	for (int i = 0; i < usiNumber1->vNumber.size(); i++) {
		if (i < usiNumber2->vNumber.size()) {
			usiResult->vNumber.push_back(usiNumber1->vNumber[i] + usiNumber2->vNumber[i]);
		} else {
			usiResult->vNumber.push_back(usiNumber1->vNumber[i]);
		}
	}

	usiResult->format();

	return usiResult;
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
			usiResult->vNumber.push_back(usiNumber1->vNumber[i] - usiNumber2->vNumber[i]);
		} else {
			usiResult->vNumber.push_back(usiNumber1->vNumber[i]);
		}
	}

	usiResult->format();

	return usiResult;
}

void superint::format() {
	if (!vNumber.empty()) {
		for (int i = 0; i < vNumber.size(); i++) {
			if (vNumber[i] >= 10) {
				passToHigherIndex(vNumber[i], i);
			} else if (vNumber[i] < 0) {
				borrowFromHigherIndex(vNumber[i], i);
			}
		}

		if (!isFormattedCorrectly()) {
			format();
		}

		if (hasLeadingZeroes()) {
			removeLeadingZeroes();
		}
	}
}

void superint::passToHigherIndex(int currentEntry, int i) {
	int upperNumber = currentEntry / 10;

	if (vNumber.size() - 1 > i) {
		int upperEntry = vNumber[i + 1];
		vNumber[i] = currentEntry % 10;
		vNumber[i + 1] = upperEntry + upperNumber;
	} else {
		vNumber[i] = currentEntry % 10;
		vNumber.push_back(upperNumber);
	}
}

void superint::borrowFromHigherIndex(int currentEntry, int i) {
	vNumber[i] = currentEntry + 10;
	vNumber[i + 1] = vNumber[i + 1] - 1;
}

bool superint::isFormattedCorrectly() {
	for (int i = 0; i < vNumber.size(); i++) {
		if (vNumber[i] >= 10 || vNumber[i] < 0) {
			return false;
		}
	}

	return true;
}

bool superint::hasLeadingZeroes() {
	if (vNumber.size() == 0) {
		return false;
	} else if (vNumber[vNumber.size() - 1] == 0) {
		return true;
	} else {
		return false;
	}
}

void superint::removeLeadingZeroes() {
	for (int i = vNumber.size() - 1; i > 0; i--) {
		if (vNumber[i] == 0) {
			vNumber.pop_back();
		} else {
			break;
		}
	}
}

void superint::insertAtLocation(int location, int value) {
	if (vNumber.size() <= location) {
		for (int i = vNumber.size(); i < location; i++) {
			vNumber.push_back(0);
		}

		vNumber.push_back(value);
	} else {
		vNumber[location] = value;
	}
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