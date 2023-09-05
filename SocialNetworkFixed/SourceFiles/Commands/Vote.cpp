#include "../../Headers/Commands/Vote.h"
#include "../../Headers/ResultEnums/VoteResult.h"

#include <string>

void Vote::execute() const
{
	const User* loggedUser = usersRepository->getLoggedUserConst();
	Theme* loadedTheme = themesRepository->getOpenedTheme();

	if (!GlobalFunctions::userLogged(loggedUser) ||
		!GlobalFunctions::openedTheme(loadedTheme) ||
		!GlobalFunctions::postOpened(loadedTheme->getOpenedPostConst()))
	{
		return;
	}

	std::cout << "---------" << std::endl;

	std::cout << "Comment Id: ";
	char idText[16];
	std::cin.getline(idText, 16);

	std::cout << "Chose vote type (U-upvote/D-downvote): ";
	char voteType[8];
	std::cin.getline(voteType, 8);

	int commentId = GlobalFunctions::ParseId(idText);

	VoteResult voteResult = VoteResult::UserAlreadyVoted;

	if (!validateVoteType(voteType))
	{
		voteResult = VoteResult::InvalidVoteType;
		writeResultMessageToConsole(voteResult);

		return;
	}

	if (commentId >= 0 && !loggedUser->hasVoted(commentId))
	{
		if (voteType[0] == 'U' || voteType[0] == 'u')
		{
			voteResult = loadedTheme->getOpenedPost()->vote(commentId, VoteType::UpVote);
		}
		else
		{
			voteResult = loadedTheme->getOpenedPost()->vote(commentId, VoteType::DownVote);
		}
	}

	writeResultMessageToConsole(voteResult);
}
void Vote::writeResultMessageToConsole(VoteResult voteResult) const
{
	const char* resultMessage = "";

	switch (voteResult)
	{
	case VoteResult::Success:resultMessage = "Successfully voted!";
		break;
	case VoteResult::UserAlreadyVoted:resultMessage = "You have already voted for this comment!";
		break;
	case VoteResult::InvalidVoteType:resultMessage = "Invalid vote type!";
		break;
	case VoteResult::IdNotFound:resultMessage = "Comment with such id does not exist in the current post!";
		break;
	default:
		break;
	}

	std::cout << resultMessage << std::endl << std::endl;
}

bool Vote::validateVoteType(const char* voteType) const
{
	if (voteType[1])
	{
		return false;
	}

	return voteType[0] == 'U' || voteType[0] == 'u' ||
		voteType[0] == 'D' || voteType[0] == 'd'
		? true : false;
}
