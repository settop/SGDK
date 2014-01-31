#pragma once

#include "Vector.h"
#include "Vector4.h"

__declspec(align(16)) class Matrix44
{
public:
	typedef Matrix44 const Matrix44ConstParam;
	typedef Matrix44 const& Matrix44ConstRef;
	typedef Matrix44& Matrix44Ref;
public:
	template<int I>
	static Matrix44 Integer();

	static Matrix44 Identity();
	static Matrix44 Zero();
	
	inline Matrix44();
	inline Matrix44(Vector4ConstRef _c1, Vector4ConstRef _c2, Vector4ConstRef _c3, Vector4ConstRef _c4);
	inline Matrix44(Matrix44ConstRef _other);

	inline Matrix44Ref operator=(Matrix44ConstRef _other);

	inline Vector4 GetColumn1() const;
	inline Vector4 GetColumn2() const;
	inline Vector4 GetColumn3() const;
	inline Vector4 GetColumn4() const;
	inline Vector4 Column1() const { return GetColumn1(); }
	inline Vector4 Column2() const { return GetColumn2(); }
	inline Vector4 Column3() const { return GetColumn3(); }
	inline Vector4 Column4() const { return GetColumn4(); }

	inline void SetColumn1(Vector4ConstRef _c1);
	inline void SetColumn2(Vector4ConstRef _c2);
	inline void SetColumn3(Vector4ConstRef _c3);
	inline void SetColumn4(Vector4ConstRef _c3);

	__m128 m_c1;
	__m128 m_c2;
	__m128 m_c3;
	__m128 m_c4;
};

inline Matrix44 operator+(Matrix44ConstRef _l, Matrix44ConstRef _r);
inline Matrix44 operator-(Matrix44ConstRef _l, Matrix44ConstRef _r);
inline Matrix44 operator*(Matrix44ConstRef _l, Matrix44ConstRef _r);
inline Vector4 operator*(Matrix44ConstRef _l, Vector4ConstRef _r);

inline bool operator==(Matrix44ConstRef _l, Matrix44ConstRef _r);
inline bool operator!=(Matrix44ConstRef _l, Matrix44ConstRef _r);

inline Matrix44 Transpose(Matrix44ConstRef _param);

#include "Matrix44.inl"