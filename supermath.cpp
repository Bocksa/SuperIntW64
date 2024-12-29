// Created by: Cian McNamara (cian@telecomeireann.ie), December 29th 2024

#include <vector>

#include "pch.h"
#include "supermath.h"
#include "superint.h"

using namespace SuperIntW64;

superint* supermath::Random(superint* usiMin, superint* usiMax) {
	superint* usiResult = nullptr;

	while (true) {
		std::srand(time(nullptr));

		long randomNumber = std::rand() % 24411256;
		long randomNumber2 = std::rand() % 694678937;

		superint* rand = new superint(randomNumber);
		superint* rand2 = new superint(randomNumber2);
		usiResult = superint::Mult(rand2, rand);

		delete rand;
		delete rand2;

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
			break;
		}
	}

	return usiResult;
}