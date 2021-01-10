// ReadWriter_Write.h   simple stream write implementation example

// This is freeand unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non - commercial, and by any
// means.
// 
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain.We make this dedication for the benefit
// of the public at largeand to the detriment of our heirsand
// successors.We intend this dedication to be an overt act of
// relinquishment in perpetuity of all presentand future rights to this
// software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// 
// For more information, please refer to < https://unlicense.org>

#pragma once

#include "ReadWrite_Base.h"

template <typename Pod>
auto write(std::ofstream& os, Pod const& pod) -> std::enable_if_t<std::is_pod_v<Pod>>
{
	os.write((char*)&pod, sizeof(pod));
}

HEADER_INLINE
void write(std::ofstream& os, std::string const& str)
{
	write(os, size(str));
	os.write(data(str), size(str));
}

template <typename T>
void write(std::ofstream& os, std::vector<T> const& vec)
{
	write(os, size(vec));
	for (auto const& el : vec)
		write(os, el);
}

