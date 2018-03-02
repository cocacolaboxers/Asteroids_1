#pragma once
#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

class InputManager
{
public:
	/*CTOR*/
	InputManager();

	/*PUBLIC FUNCTIONS*/
	void SetUpKeyPressedStatus(bool);
	void SetLeftKeyPressedStatus(bool);
	void SetRightKeyPressedStatus(bool);
	void SetAkeyPressedStatus(bool);
	void SetRkeyPressedStatus(bool);
	void SetFkeyPressedStatus(bool);
	void SetDkeyPressedStatus(bool);
	void SetSkeyPressedStatus(bool);
	void SetSpaceKeyPressedStatus(bool);

	bool GetUpKeyStatus(void);
	bool GetLeftKeyStatus(void);
	bool GetRightKeyStatus(void);
	bool GetAkeyStatus(void);
	bool GetRkeyStatus(void);
	bool GetFkeyStatus(void);
	bool GetDkeyStatus(void);
	bool GetSkeyStatus(void);
	bool GetSpaceKeyStatus(void);

private:
	/*PRIVATE MEMBERS*/
	bool m_upKeyPressedStatus;
	bool m_leftKeyPressedStatus;
	bool m_rightKeyPressedStatus;
	bool m_aKeyPressedStatus;
	bool m_rKeyPressedStatus;
	bool m_fKeyPressedStatus;
	bool m_dKeyPressedStatus;
	bool m_sKeyPressedStatus;
	bool m_spaceKeyPressedStatus;
};

#endif // !_INPUT_MANAGER_H

