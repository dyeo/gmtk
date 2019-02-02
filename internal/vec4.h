#ifndef _GMTK_VEC4_H_
#define _GMTK_VEC4_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"
#include "swizzle2.h"
#include "swizzle3.h"
#include "swizzle4.h"

//

#define GMTK_VEC4_LOOP(oper) GMTK_UNROLL_LOOP(i,4,oper)

//

#define GMTK_VEC4_UN_OP(op) \
	inline vec<4, T> operator op () const \
	{ vec<4, T> res; GMTK_VEC4_LOOP(res.data[i] = op data[i]); return res; }

#define GMTK_VEC4_VEC_OP(op) \
	inline vec<4, T> operator op (const vec<4, T>& v) const \
	{ vec<4, T> res; GMTK_VEC4_LOOP(res.data[i] = data[i] op v.data[i]); return res; }

#define GMTK_VEC4_SCL_OP(op) \
	inline vec<4, T> operator op (const T& v) const \
	{ vec<4, T> res; GMTK_VEC4_LOOP(res.data[i] = data[i] op v); return res; }

#define GMTK_VEC4_VEC_ROP(op) \
	inline vec<4, T>& operator op (const vec<4, T>& v) \
	{ GMTK_VEC4_LOOP(data[i] op v.data[i]); return *this; }

#define GMTK_VEC4_SCL_ROP(op) \
	inline vec<4, T>& operator op (const T& v) \
	{ GMTK_VEC4_LOOP(data[i] op v); return *this; }

#define GMTK_VEC4_SWZ_BOP(op) \
	template<int a, int b, int c, int d, typename T> \
	static inline vec<4, T> operator op (const vec<4, T> &v, const swizzle4<a, b, c, d, vec<4, T>, T> &s) \
	{ vec<4, T> res; res.data[0] = data[0] op s[a]; res.data[1] = data[1] op s[b]; res.data[2] = data[2] op s[c]; res.data[3] = data[3] op s[d]; return res; } \
	template<int a, int b, int c, int d, typename T> \
	static inline vec<4, T> operator op (const swizzle4<a, b, c, d, vec<4, T>, T> &s, const vec<4, T> &v) \
	{ vec<4, T> res; res.data[0] = s[a] op data[0]; res.data[1] = s[b] op data[1]; res.data[2] = s[c] op data[2]; res.data[3] = s[d] op data[3]; return res; } \
	template<int a1, int b1, int c1, int d1, int a2, int b2, int c2, int d2, typename T> \
	static inline vec<4, T> operator op (const swizzle4<a1, b1, c1, d1, vec<4, T>, T> &s, const swizzle4<a2, b2, c2, d2, vec<4, T>, T> &t) \
	{ vec<4, T> res; res.data[0] = s[a1] op t[a2]; res.data[1] = s[b1] op t[b2]; res.data[2] = s[c1] op t[c2]; res.data[3] = s[d1] op t[d2]; return res; }

#define GMTK_VEC4_SWZ_BROP(op) \
	template<int a, int b, int c, int d, typename T> \
	static inline vec<4, T>& operator op (vec<4, T> &v, const swizzle4<a, b, c, d, vec<4, T>, T> &s) \
	{ v.data[0] op s[a]; v.data[1] op s[b]; v.data[2] op s[c]; v.data[3] op s[d]; return v; } \
	template<int a, int b, int c, int d, typename T> \
	static inline swizzle4<a, b, c, d, vec<4, T>, T>& operator op (swizzle4<a, b, c, d, vec<4, T>, T> &s, const vec<4, T> &v) \
	{ s[a] op v.data[0]; s[b] op v.data[1]; s[c] op v.data[2]; s[d] op v.data[3]; return s; } \
	template<int a1, int b1, int c1, int d1, int a2, int b2, int c2, int d2, typename T> \
	static inline swizzle4<a1, b1, c1, d1, vec<4, T>, T>& operator op (swizzle4<a1, b1, c1, d1, vec<4, T>, T> &s, const swizzle4<a2, b2, c2, d2, vec<4, T>, T> &t) \
	{ s[a1] op t[a2]; s[b1] op t[b2]; s[c1] op t[c2]; s[d1] op t[d2]; return s; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec <4, T>
	{
		////////////
		//! TYPES //
		////////////

		template<int a, int b> using swz2 = swizzle2<a, b, vec<2, T>, T>;
		template<int a, int b, int c> using swz3 = swizzle3<a, b, c, vec<3, T>, T>;
		template<int a, int b, int c, int d> using swz4 = swizzle4<a, b, c, d, vec<3, T>, T>;

		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct { T data[4]; };
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			GMTK_VEC4_SWIZZLES
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Initialize vec4 with four values
		inline vec(const T& s0, const T& s1, const T& s2, const T& s3)
		{
			data[0] = s0;
			data[1] = s1;
			data[2] = s2;
			data[3] = s3;
		}

		//! Initialize vec4 with a vec3 and a fourth value
		inline vec(const vec<3, T>& v012, const T& s3)
		{
			data[0] = v012.data[0];
			data[1] = v012.data[1];
			data[2] = v012.data[2];
			data[3] = s3;
		}

		//! Initialize vec4 with two vec2s
		inline vec(const vec<2, T>& v01, const vec<2, T>& v23)
		{
			data[0] = v01.data[0];
			data[1] = v01.data[1];
			data[2] = v23.data[0];
			data[2] = v23.data[1];
		}

		//! Default constructor
		inline vec() {
			GMTK_VEC4_LOOP(data[i] = static_cast<T>(0));
		}

		//! Swizzle2 constructor
		template<int a, int b>
		inline vec(const swz2<a, b>&s) {
			data[0] = s[a];
			data[1] = s[b];
			data[2] = static_cast<T>(1);
			data[3] = static_cast<T>(1);
		}

		//! Swizzle3 constructor
		template<int a, int b, int c>
		inline vec(const swz3<a, b, c>&s) {
			data[0] = s[a];
			data[1] = s[b];
			data[2] = s[c];
			data[3] = static_cast<T>(1);
		}

		//! Swizzle4 constructor
		template<int a, int b, int c, int d>
		inline vec(const swz4<a, b, c, d>&s) {
			data[0] = s[a];
			data[1] = s[b];
			data[2] = s[c];
			data[3] = s[d];
		}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMTK_VEC4_LOOP(data[i] = *(list.begin() + i));
		}

		//! Copy constructor
		inline vec(const vec<4, T>& v) {
			GMTK_VEC4_LOOP(data[i] = v.data[i]);
		}

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<d2, T> &v) {
			GMTK_STATIC_ASSERT(d2 >= 4);
			GMTK_VEC4_LOOP(data[i] = v.data[i]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> 
		explicit inline vec(const vec<4, U>& v) {
			GMTK_VEC4_LOOP(data[i] = static_cast<T>(v[i]));
		}

		//! Fill constructor
		explicit inline vec(const T& s) {
			GMTK_VEC4_LOOP(data[i] = s);
		}

		//! Array initializer
		explicit inline vec(const T* a) {
			GMTK_VEC4_LOOP(data[i] = a[i]);
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Vector index operator
		inline T& operator[](const int i) {
			return data[i];
		}

		//! Vector const index operator
		inline const T& operator[](const int i) const {
			return data[i];
		}

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Component-wise unary negation
		GMTK_VEC4_UN_OP(-)

		//! Component-wise vector multiplication
		GMTK_VEC4_VEC_OP(*)

		//! Component-wise vector division
		GMTK_VEC4_VEC_OP(/ )

		//! Component-wise vector addition
		GMTK_VEC4_VEC_OP(+)

		//! Component-wise vector subtraction
		GMTK_VEC4_VEC_OP(-)

		//! Component-wise scalar multiplication
		GMTK_VEC4_SCL_OP(*)

		//! Component-wise scalar division
		GMTK_VEC4_SCL_OP(/)

		//! Component-wise scalar addition
		GMTK_VEC4_SCL_OP(+)

		//! Component-wise scalar subtraction
		GMTK_VEC4_SCL_OP(-)

		//! Component-wise scalar reference multiplication
		GMTK_VEC4_SCL_ROP(*=)

		//! Component-wise vector reference multiplication
		GMTK_VEC4_VEC_ROP(*=)

		//! Component-wise vector reference division
		GMTK_VEC4_VEC_ROP(/=)

		//! Component-wise vector reference addition
		GMTK_VEC4_VEC_ROP(+=)

		//! Component-wise vector reference subtraction
		GMTK_VEC4_VEC_ROP(-=)

		//! Component-wise scalar reference division
		GMTK_VEC4_SCL_ROP(/=)

		//! Component-wise scalar reference addition
		GMTK_VEC4_SCL_ROP(+=)

		//! Component-wise scalar reference subtraction
		GMTK_VEC4_SCL_ROP(-=)

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! Zero vector (0,0,0,0)
		static inline constexpr vec<4, T> zero() { return vec<4, T>(0, 0, 0, 0); }

		//! One vector (1,1,1,1)
		static inline constexpr vec<4, T> one() { return vec<4, T>(1, 1, 1, 1); }

		//! Up vector (0,1,0,0)
		static inline constexpr vec<4, T> up() { return vec<4, T>(0, 1, 0, 0); }

		//! Down vector (0,-1,0,0)
		static inline constexpr vec<4, T> down() { return vec<4, T>(0, -1, 0, 0); }

		//! Right vector (1,0,0,0)
		static inline constexpr vec<4, T> right() { return vec<4, T>(1, 0, 0, 0); }

		//! Left vector (-1,0,0,0)
		static inline constexpr vec<4, T> left() { return vec<4, T>(-1, 0, 0, 0); }

		//! Forward vector (0,0,1,0)
		static inline constexpr vec<4, T> forward() { return vec<4, T>(0, 0, 1, 0); }

		//! Back vector (0,0,-1,0)
		static inline constexpr vec<4, T> back() { return vec<4, T>(0, 0, -1, 0); }

	}; //! struct vec4
	
	//////////////////////////
	//! SWIZZLING OPERATORS //
	//////////////////////////
	
	GMTK_VEC4_SWZ_BOP(*)
	GMTK_VEC4_SWZ_BOP(/)
	GMTK_VEC4_SWZ_BOP(+)
	GMTK_VEC4_SWZ_BOP(-)

	GMTK_VEC4_SWZ_BROP(*=)
	GMTK_VEC4_SWZ_BROP(/=)
	GMTK_VEC4_SWZ_BROP(+=)
	GMTK_VEC4_SWZ_BROP(-=)

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////
	
	typedef vec<4, float>			vec4, vec4f;
	typedef vec<4, double>			vec4d;
	typedef vec<4, unsigned char>	vec4uc;
	typedef vec<4, char>			vec4c;
	typedef vec<4, unsigned short>	vec4us;
	typedef vec<4, short>			vec4s;
	typedef vec<4, unsigned int>	vec4ui;
	typedef vec<4, int>				vec4i;
	typedef vec<4, unsigned long>	vec4ul;
	typedef vec<4, long>			vec4l;

}////

//

#undef GMTK_VEC4_LOOP
#undef GMTK_VEC4_OPERATOR
#undef GMTK_VEC4_UN_OP
#undef GMTK_VEC4_VEC_OP
#undef GMTK_VEC4_SCL_OP
#undef GMTK_VEC4_VEC_ROP
#undef GMTK_VEC4_SCL_ROP

#undef GMTK_VEC4_SWZ_BOP
#undef GMTK_VEC4_SWZ_BROP

//

#pragma warning(pop)

//

#endif