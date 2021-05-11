//===- Optional.cpp - Optional values ---------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "lvc/ADT/Optional.h"
#include "lvc/Support/raw_ostream.h"

lvc::raw_ostream &lvc::operator<<(raw_ostream &OS, NoneType) {
  return OS << "None";
}
