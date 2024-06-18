//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "Logger.hpp"
#include <cstdint>

namespace Ygg {

   // Non Owning Buffer
   struct Buffer {
      Buffer() = default;
      Buffer(const Buffer&) = default;
      Buffer& operator=(const Buffer&) = default;
      ~Buffer() = default;
      template<typename T>
      Buffer(T* data, uint64_t count) : data(reinterpret_cast<uint8_t*>(data)), size(count * sizeof(T)) {}
      explicit Buffer(void* data, uint64_t size) : data(reinterpret_cast<uint8_t *>(data)), size(size) {}

      void Allocate(uint64_t size);
      void Release();

      template<typename T>
      T* As();

      template<typename T>
      const T* As() const;

      template<typename T>
      T& operator[](uint64_t i);

      template<typename T>
      const T& operator[](uint64_t i) const;

      uint8_t* data = nullptr;
      uint64_t size = 0;
   };

   template<typename T>
   T *Buffer::As() {
      YGG_ASSERT(sizeof(T) >= size, "The size {} is not big enough to be cast as {}({} bytes)", size, typeid(T).name(), sizeof(T));
      return reinterpret_cast<T*>(data);
   }

   template<typename T>
   const T *Buffer::As() const {
      YGG_ASSERT(sizeof(T) >= size, "The size {} is not big enough to be cast as {}({} bytes)", size, typeid(T).name(), sizeof(T));
      return reinterpret_cast<T*>(data);
   }

   template<typename T>
   T& Buffer::operator[](uint64_t i) {
      YGG_ASSERT((i + 1) * sizeof(T) > size, "The size {} is too small to access the index {} of type {}", size, i, typeid(T).name());
      return reinterpret_cast<T*>(data)[i];
   }

   template<typename T>
   const T& Buffer::operator[](uint64_t i) const {
      YGG_ASSERT((i + 1) * sizeof(T) > size, "The size {} is too small to access the index {} of type {}", size, i, typeid(T).name());
      return reinterpret_cast<const T*>(data)[i];
   }

} // Core
