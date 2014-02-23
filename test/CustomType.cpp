#include "stdafx.h"
#include "CustomType.h"

BaseType::BaseType()
: int_(0)
, float_(0.f)
, short_(0)
, uint_(0U)
, int64_(0LL)
{

}

BaseType::BaseType(int int_, float float_, short short_, unsigned int uint_, int64_t int64_)
: int_(int_)
, float_(float_)
, short_(short_)
, uint_(uint_)
, int64_(int64_)
{

}
