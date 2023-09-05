#pragma once
#include "IComment.h"

class Reply : public IComment
{
public:
	Reply() = default;
	Reply(unsigned authorId, const MyString& text);

	void free();
};

