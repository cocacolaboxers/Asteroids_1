#include "InputManager.hpp"

InputManager::InputManager()
{
	m_upKeyPressedStatus = false;
	m_leftKeyPressedStatus = false;
	m_rightKeyPressedStatus = false;
	m_aKeyPressedStatus = false;
	m_rKeyPressedStatus = false;
	m_fKeyPressedStatus = false;
	m_dKeyPressedStatus = false;
	m_sKeyPressedStatus = false;
	m_spaceKeyPressedStatus = false;
}

void InputManager::SetUpKeyPressedStatus(bool status)
{
	m_upKeyPressedStatus = status;
}

void InputManager::SetLeftKeyPressedStatus(bool status)
{
	m_leftKeyPressedStatus = status;
}

void InputManager::SetRightKeyPressedStatus(bool status)
{
	m_rightKeyPressedStatus = status;
}

void InputManager::SetAkeyPressedStatus(bool status)
{
	m_aKeyPressedStatus = status;
}

void InputManager::SetRkeyPressedStatus(bool status)
{
	m_rKeyPressedStatus = status;
}

void InputManager::SetFkeyPressedStatus(bool status)
{
	m_fKeyPressedStatus = status;
}

void InputManager::SetDkeyPressedStatus(bool status)
{
	m_dKeyPressedStatus = status;
}

void InputManager::SetSkeyPressedStatus(bool status)
{
	m_sKeyPressedStatus = status;
}

void InputManager::SetSpaceKeyPressedStatus(bool status)
{
	m_spaceKeyPressedStatus = status;
}

bool InputManager::GetUpKeyStatus(void)
{
	return m_upKeyPressedStatus;
}

bool InputManager::GetLeftKeyStatus(void)
{
	return m_leftKeyPressedStatus;
}

bool InputManager::GetRightKeyStatus(void)
{
	return m_rightKeyPressedStatus;
}

bool InputManager::GetAkeyStatus(void)
{
	return m_aKeyPressedStatus;
}

bool InputManager::GetRkeyStatus(void)
{
	return m_rKeyPressedStatus;
}

bool InputManager::GetFkeyStatus(void)
{
	return m_fKeyPressedStatus;
}

bool InputManager::GetDkeyStatus(void)
{
	return m_dKeyPressedStatus;
}

bool InputManager::GetSkeyStatus(void)
{
	return m_sKeyPressedStatus;
}

bool InputManager::GetSpaceKeyStatus(void)
{
	return m_spaceKeyPressedStatus;
}
