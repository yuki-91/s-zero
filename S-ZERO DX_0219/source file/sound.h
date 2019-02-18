
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_SE_KASOKU= 0,		// ����
	SOUND_LABEL_SE_COUNTDOWN,	// �J�E���g�_�E��
	SOUND_LABEL_SE_COIN ,		// �R�C��
	SOUND_LABEL_DAMAGE,		// �_���[�W
	SOUND_LABEL_BUTTON ,		// �{�^��
	SOUND_LABEL_LASTLAP ,		// ���X�g���b�v
	SOUND_LABEL_START ,		// �X�^�[�g
	SOUND_LABEL_STAR ,		// �X�^�[���
	SOUND_LABEL_ITEMBOX ,		// �A�C�e�������_��
	SOUND_LABEL_WAHAA ,		// �L�m�R�g�p
	SOUND_LABEL_WAHAAKINO ,		// �L�m�R�g�p�Q
	SOUND_LABEL_TURBO ,		// �^�[�{
	SOUND_LABEL_START_ENGIN ,		// �G���W��
	SOUND_LABEL_DRIFT ,		// �h���t�g
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
