#pragma once

enum class VoteResult
{
	Success,
	UserAlreadyVoted,
	InvalidVoteType,
	IdNotFound
};