
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_SE_KASOKU= 0,		// ����
	SOUND_LABEL_SE_COUNTDOWN= 1,	// �J�E���g�_�E��
	SOUND_LABEL_SE_COIN= 2,		// �R�C��
	SOUND_LABEL_DAMAGE= 3,		// �_���[�W
	SOUND_LABEL_BUTTON = 4,		// �{�^��
	SOUND_LABEL_LASTLAP = 5,		// ���X�g���b�v
	SOUND_LABEL_START = 6,		// �X�^�[�g
	SOUND_LABEL_STAR = 7,		// �X�^�[���
	SOUND_LABEL_ITEMBOX = 8,		// �A�C�e�������_��
	SOUND_LABEL_WAHAA = 9,		// �L�m�R�g�p
	SOUND_LABEL_WAHAAKINO = 10,		// �L�m�R�g�p�Q
	SOUND_LABEL_TURBO = 11,		// �^�[�{
	SOUND_LABEL_START_ENGIN = 12,		// �G���W��
	SOUND_LABEL_DRIFT = 13,		// �h���t�g
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
