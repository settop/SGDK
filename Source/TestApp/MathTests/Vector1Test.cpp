#include "Vector1Test.h"

#include <Math/Math.h>

namespace Vector1Test
{
	void Run
	(
	)
	{
		Vector2 test = Vector2::One();

		Vector3 z = Cross(Vector3::Integer<1, 0, 0>(), Vector3::Integer<0, 1, 0>());

		Vector1 length = Length(Vector3::Integer<1>());
		Assert(length < Vector1::Integer<2>());
	}
}