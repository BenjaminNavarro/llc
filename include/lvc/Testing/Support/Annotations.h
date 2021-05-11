//===--- Annotations.h - Annotated source code for tests ---------*- C++-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#ifndef LVC_TESTING_SUPPORT_ANNOTATIONS_H
#define LVC_TESTING_SUPPORT_ANNOTATIONS_H

#include "lvc/ADT/SmallVector.h"
#include "lvc/ADT/StringMap.h"
#include "lvc/ADT/StringRef.h"
#include <tuple>
#include <vector>

namespace lvc {

/// Annotations lets you mark points and ranges inside source code, for tests:
///
///    Annotations Example(R"cpp(
///       int complete() { x.pri^ }         // ^ indicates a point
///       void err() { [["hello" == 42]]; } // [[this is a range]]
///       $definition^class Foo{};          // points can be named: "definition"
///       $fail[[static_assert(false, "")]] // ranges can be named too: "fail"
///    )cpp");
///
///    StringRef Code = Example.code();             // annotations stripped.
///    std::vector<size_t> PP = Example.points();   // all unnamed points
///    size_t P = Example.point();                  // there must be exactly one
///    lvc::Range R = Example.range("fail");       // find named ranges
///
/// Points/ranges are coordinated into `code()` which is stripped of
/// annotations.
///
/// Ranges may be nested (and points can be inside ranges), but there's no way
/// to define general overlapping ranges.
///
/// FIXME: the choice of the marking syntax makes it impossible to represent
///        some of the C++ and Objective C constructs (including common ones
///        like C++ attributes). We can fix this by:
///          1. introducing an escaping mechanism for the special characters,
///          2. making characters for marking points and ranges configurable,
///          3. changing the syntax to something less commonly used,
///          4. ...
class Annotations {
public:
  /// Two offsets pointing to a continuous substring. End is not included, i.e.
  /// represents a half-open range.
  struct Range {
    size_t Begin = 0;
    size_t End = 0;

    friend bool operator==(const Range &L, const Range &R) {
      return std::tie(L.Begin, L.End) == std::tie(R.Begin, R.End);
    }
    friend bool operator!=(const Range &L, const Range &R) { return !(L == R); }
  };

  /// Parses the annotations from Text. Crashes if it's malformed.
  Annotations(lvc::StringRef Text);

  /// The input text with all annotations stripped.
  /// All points and ranges are relative to this stripped text.
  lvc::StringRef code() const { return Code; }

  /// Returns the position of the point marked by ^ (or $name^) in the text.
  /// Crashes if there isn't exactly one.
  size_t point(lvc::StringRef Name = "") const;
  /// Returns the position of all points marked by ^ (or $name^) in the text.
  /// Order matches the order within the text.
  std::vector<size_t> points(lvc::StringRef Name = "") const;

  /// Returns the location of the range marked by [[ ]] (or $name[[ ]]).
  /// Crashes if there isn't exactly one.
  Range range(lvc::StringRef Name = "") const;
  /// Returns the location of all ranges marked by [[ ]] (or $name[[ ]]).
  /// They are ordered by start position within the text.
  std::vector<Range> ranges(lvc::StringRef Name = "") const;

private:
  std::string Code;
  lvc::StringMap<lvc::SmallVector<size_t, 1>> Points;
  lvc::StringMap<lvc::SmallVector<Range, 1>> Ranges;
};

lvc::raw_ostream &operator<<(lvc::raw_ostream &O,
                              const lvc::Annotations::Range &R);

} // namespace lvc

#endif
