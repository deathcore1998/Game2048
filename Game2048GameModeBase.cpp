#include "Game2048GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "InputManager.h"

AGame2048GameModeBase::AGame2048GameModeBase()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AInputManager::StaticClass();
}

