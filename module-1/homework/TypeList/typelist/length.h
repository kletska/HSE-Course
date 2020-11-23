#pragma once

#include "typelist.h"

template <typename TList>
struct Length {
  static constexpr int length = Length<typename TList::T>::length + 1;
};

template <>
struct Length<NullType> {
  static constexpr int length = 0;
};
