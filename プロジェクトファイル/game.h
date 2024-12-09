//================================
//
//game.cpp�ɕK�v�Ȑ錾[game.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAME_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GAME_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "scene.h"
#include "player.h"
#include "field.h"
#include "time.h"
#include "enemymanager.h"
#include "gimmickmanager.h"
#include "explosionmanager.h"
#include "enemybulletmanager.h"
#include "barriermanager.h"
#include "lockon.h"

class CPlayer;

//�Q�[���N���X
class CGame : public CScene
{
public:

	//�����o�֐�
	CGame();						//�R���X�g���N�^
	~CGame() override;				//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	void Load() override;			//�ǂݍ���

	//�|�C���^�̎擾
	CPlayer* GetGamePlayer() { if (m_pPlayer == nullptr) { return nullptr; } return m_pPlayer; }								//�v���C���[�̎擾
	CField* GetGameField() { if (m_pField == nullptr) { return nullptr; } return m_pField; }									//�t�B�[���h�̎擾
	CTime* GetTime() { if (m_pTime == nullptr) { return nullptr; } return m_pTime; }											//���Ԃ̎擾
	CEnemyManager* GetEnemyManager() { if (m_pEnemyManager == nullptr) { return nullptr; } return m_pEnemyManager; }			//�G�l�~�[�}�l�[�W���[�̎擾
	CGimmickManager* GetGimmickManager() { if (m_pGimmickManager == nullptr) { return nullptr; } return m_pGimmickManager; }	//�M�~�b�N�}�l�[�W���[�̎擾
	CExplosionManager* GetExplosionManager() { if (m_pExplosionManager == nullptr) { return nullptr; } return m_pExplosionManager; }	//�����}�l�[�W���[�̎擾
	CEnemyBulletManager* GetEnemyBulletManager() { if (m_pEnemyBulletManager == nullptr)  { return nullptr; } return m_pEnemyBulletManager;}	//�G�l�~�[�e�̎擾
	CBarrierManager* GetBarrierManager() { if (m_pBarrierManager == nullptr) { return nullptr; } return m_pBarrierManager; }			//���E�}�l�[�W���[
	CLockon* GetLockon() { if (m_pLockon == nullptr) { return nullptr; } return m_pLockon; }									//���b�N�I���̎擾
	void SetLockon(bool lockon);																								//���b�N�I���̐ݒ�

	//�N���A����
	void SetClear(bool crear) { m_bClear = crear; }	//�ݒ�

private:

	void ModelLoad();	//���f���̓ǂݍ���

	CPlayer* m_pPlayer;					//�v���C���[
	CField* m_pField;					//�t�B�[���h
	CTime* m_pTime;						//�^�C���N���X
	CEnemyManager* m_pEnemyManager;		//�G�l�~�[�}�l�[�W���[
	CGimmickManager* m_pGimmickManager;	//�M�~�b�N�}�l�[�W���[
	CExplosionManager* m_pExplosionManager;	//�����}�l�[�W���[
	CLockon* m_pLockon;						//���b�N�I��
	CEnemyBulletManager* m_pEnemyBulletManager;	//�G�l�~�[�e�}�l�[�W���[
	CBarrierManager* m_pBarrierManager;		//���E�}�l�[�W���[

	
	bool m_bClear;			//�N���A����
	bool m_bDirectioning;	//���o����
};

#endif