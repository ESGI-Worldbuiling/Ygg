//
// Created by ianpo on 26/05/2024.
//

#pragma once

#define YGG_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define YGG_CONCAT(x, y) x ## y
#define YGG_COMBINE(x, y) YGG_CONCAT(x, y)

#define YGG_BIT(X) (1 << X)

#define YGG_CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#ifndef __FUNCSIG__
	#ifdef __PRETTY_FUNCTION__
		#define __FUNCSIG__ __PRETTY_FUNCTION__
	#else
		#define __FUNCSIG__ __FUNCTION__
	#endif
#endif

#ifdef YGG_USE_SIMPLE_FUNCTION
	#define YGG_FUNC __FUNCTION__
#else
	#define YGG_FUNC __FUNCSIG__
#endif