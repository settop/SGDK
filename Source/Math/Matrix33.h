#pragma once

#include "Vector.h"
#include "Vector3.h"

__declspec(align(16)) class Matrix33
{
public:
	typedef Matrix33 const Matrix33ConstParam;
	typedef Matrix33 const& Matrix33ConstRef;
	typedef Matrix33& Matrix33Ref;
public:
	template<int I>
	static Matrix33 Integer();

	static Matrix33 Identity();
	static Matrix33 Zero();
	
	inline Matrix33();
	inline Matrix33(Vector3ConstRef _c1, Vector3ConstRef _c2, Vector3ConstRef _c3);
	inline Matrix33(Matrix33ConstRef _other);

	inline Matrix33Ref operator=(Matrix33ConstRef _other);

	inline Vector3 GetColumn1() const;
	inline Vector3 GetColumn2() const;
	inline Vector3 GetColumn3() const;
	inline Vector3 Column1() const { return GetColumn1(); }
	inline Vector3 Column2() const { return GetColumn2(); }
	inline Vector3 Column3() const { return GetColumn3(); }

	inline void SetColumn1(Vector3ConstRef _c1);
	inline void SetColumn2(Vector3ConstRef _c2);
	inline void SetColumn3(Vector3ConstRef _c3);

	__m128 m_c1;
	__m128 m_c2;
	__m128 m_c3;
};

inline Matrix33 operator+(Matrix33ConstRef _l, Matrix33ConstRef _r);
inline Matrix33 operator-(Matrix33ConstRef _l, Matrix33ConstRef _r);
inline Matrix33 operator*(Matrix33ConstRef _l, Matrix33ConstRef _r);
inline Vector3 operator*(Matrix33ConstRef _l, Vector3ConstRef _r);

inline bool operator==(Matrix33ConstRef _l, Matrix33ConstRef _r);
inline bool operator!=(Matrix33ConstRef _l, Matrix33ConstRef _r);

inline Matrix33 Transpose(Matrix33ConstRef _param);

#include "Matrix33.inl"