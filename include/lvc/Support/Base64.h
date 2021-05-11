//===--- Base64.h - Base64 Encoder/Decoder ----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides generic base64 encoder/decoder.
//
//===----------------------------------------------------------------------===//

#ifndef LVC_SUPPORT_BASE64_H
#define LVC_SUPPORT_BASE64_H

#include <string>

namespace lvc {

template <class InputBytes> std::string encodeBase64(InputBytes const &Bytes) {
  static const char Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "abcdefghijklmnopqrstuvwxyz"
                              "0123456789+/";
  std::string Buffer;
  Buffer.resize(((Bytes.size() + 2) / 3) * 4);

  size_t i = 0, j = 0;
  for (size_t n = Bytes.size() / 3 * 3; i < n; i += 3, j += 4) {
    uint32_t x = ((unsigned char)Bytes[i] << 16) |
                 ((unsigned char)Bytes[i + 1] << 8) |
                 (unsigned char)Bytes[i + 2];
    Buffer[j + 0] = Table[(x >> 18) & 63];
    Buffer[j + 1] = Table[(x >> 12) & 63];
    Buffer[j + 2] = Table[(x >> 6) & 63];
    Buffer[j + 3] = Table[x & 63];
  }
  if (i + 1 == Bytes.size()) {
    uint32_t x = ((unsigned char)Bytes[i] << 16);
    Buffer[j + 0] = Table[(x >> 18) & 63];
    Buffer[j + 1] = Table[(x >> 12) & 63];
    Buffer[j + 2] = '=';
    Buffer[j + 3] = '=';
  } else if (i + 2 == Bytes.size()) {
    uint32_t x =
        ((unsigned char)Bytes[i] << 16) | ((unsigned char)Bytes[i + 1] << 8);
    Buffer[j + 0] = Table[(x >> 18) & 63];
    Buffer[j + 1] = Table[(x >> 12) & 63];
    Buffer[j + 2] = Table[(x >> 6) & 63];
    Buffer[j + 3] = '=';
  }
  return Buffer;
}

} // end namespace lvc

#endif
