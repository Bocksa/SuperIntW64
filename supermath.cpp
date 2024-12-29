// Created by: Cian McNamara (cian@telecomeireann.ie), December 29th 2024

#include <vector>

#include "pch.h"
#include "supermath.h"
#include "superint.h"

using namespace SuperIntW64;

superint* supermath::Random(superint* usiMin, superint* usiMax) {
	std::srand(time(nullptr));

	int loopCount = rand() % 101;
	superint* usiResult = new superint("1");

	for (int i = 0; i < loopCount; i++) {
		long randomNumber = std::rand() % 24411256;

		superint* rand = new superint(randomNumber);
		usiResult = superint::Mult(usiResult, rand);
	}
	
	std::vector<int>* vResult = new std::vector<int>();
	int lowerCount = usiMin->GetVector().size();
	int higherCount = usiMax->GetVector().size();

	std::vector<int> usiResultVector = usiResult->GetVector();

	for (int i = 0; i < higherCount; i++) {
		vResult->push_back(usiResultVector[i]);
	}

	usiResult = new superint(vResult);

	// if min <= result <= max then return result
	if ((superint::IsGreater(usiResult, usiMin) || superint::IsEqual(usiResult, usiMin)) && 
		(superint::IsLesser(usiResult, usiMax) || superint::IsEqual(usiResult, usiMax))) {
		return usiResult;
	} else {
		return Random(usiMin, usiMax);
	}
}