//===-- None.h - Simple null value for implicit construction ------*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//  This file provides None, an enumerator for use in implicit constructors
//  of various (usually templated) types to make such construction more
//  terse.
//
//===----------------------------------------------------------------------===//

#ifndef LVC_ADT_NONE_H
#define LVC_ADT_NONE_H

namespace lvc {
/// A simple null object to allow implicit construction of Optional<T>
/// and similar types without having to spell out the specialization's name.
// (constant value 1 in an attempt to workaround MSVC build issue... )
enum class NoneType { None = 1 };
const NoneType None = NoneType::None;
} // namespace lvc

#endif
