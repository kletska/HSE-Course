#pragma once

#include "typelist.h"

template <typename TList, typename TargetType>
struct IndexOf {
 private:
  static constexpr int rec = IndexOf<typename TList::T, TargetType>::pos;

 public:
  static constexpr int pos = rec == -1 ? -1 : rec + 1;
};

template <typename TList>
struct IndexOf<TList, typename TList::H> {
  static constexpr int pos = 0;
};

template <typename TargetType>
struct IndexOf<NullType, TargetType> {
  static constexpr int pos = -1;
};
