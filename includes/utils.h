#pragma once

#include "Libs.h"

template <typename T>
void append(std::vector<T>& a, const std::vector<T>& b) {
	a.reserve(a.size() + b.size());
	a.insert(a.end(), b.begin(), b.end());
}