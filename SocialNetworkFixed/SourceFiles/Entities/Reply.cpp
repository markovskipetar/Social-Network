#pragma once
#include "../../Headers/Entities/Reply.h"

Reply::Reply(unsigned authorId, const MyString& text)
	: IComment(authorId, text) {}

void Reply::free()
{
	removeAuthorPoints();
}
 