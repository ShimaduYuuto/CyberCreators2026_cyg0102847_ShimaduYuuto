//================================
//
//object.cpp�ɕK�v�Ȑ錾[object.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _OBJECT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	//�萔
	static const int MAX_OBJECT = 256;	//�I�u�W�F�N�g�̍ő�
	static const int NUM_PRIORITY = 16;	//�v���C�I���e�B�̐�

	//�I�u�W�F�N�g�̃^�O
	typedef enum
	{
		TAG_NONE = 0,	//���ɖ���
		TAG_PAUSE,		//�|�[�Y���ɍX�V����I�u�W�F�N�g
		TAG_GAME,		//�Q�[�����ɍX�V����I�u�W�F�N�g
		TAG_MAX,		//�񋓂̍ő�
	}TAG;

	//�I�u�W�F�N�g�̎��
	typedef enum
	{
		TYPE_NONE = 0,	//�^�C�v�Ȃ�
		TYPE_ENEMY,		//�G
		TYPE_PLAYER,	//�v���C���[
		TYPE_MAX,		//�ő�
	}TYPE;

	//�֐�
	CObject(int nPriority = 3);			//�R���X�g���N�^
	virtual ~CObject();					//�f�X�g���N�^
	virtual HRESULT Init() = 0;			//������
	virtual void Uninit() = 0;			//�I��
	virtual void Update() = 0;			//�X�V
	virtual void Draw() = 0;			//�`��
	static void ReleaseAll();			//�S�I�u�W�F�N�g�̊J��
	static void UpdateAll();			//�S�I�u�W�F�N�g�̍X�V
	static void DrawAll();				//�S�I�u�W�F�N�g�̕`��
	void SetDeath() { m_bDeath = true; }//�I�u�W�F�N�g�̎��S�t���O�𗧂Ă�
	bool GetDeath() { return m_bDeath; }//�I�u�W�F�N�g�̎��S����̎擾
	static CObject* GetTopObject(int priority);//�I�u�W�F�N�g�̐擪���擾

	//�p�����[�^�[�̐ݒ�Ǝ擾
	virtual void SetPos(D3DXVECTOR3 Pos) { m_Pos = Pos; }	//�ʒu�̐ݒ�
	D3DXVECTOR3& GetPos() { return m_Pos; }					//�ʒu�̎擾
	void SetType(TYPE type) {m_Type = type;}				//��ނ̐ݒ�
	TYPE GetType() { return m_Type; }						//��ނ̎擾
	CObject* GetNext() { return m_pNext; }					//���̃|�C���^�̎擾

protected:
	void Release();							//�������g�̊J��

private:
	static int m_nNumAll;					//�I�u�W�F�N�g�̑���
	static CObject* m_pTop[NUM_PRIORITY];	//�擪�̃I�u�W�F�N�g�|�C���^
	static CObject* m_pCur[NUM_PRIORITY];	//���݁i�Ō���j�̃|�C���^
	CObject* m_pPrev;						//�O�̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pNext;						//���̃I�u�W�F�N�g�̃|�C���^
	bool m_bDeath;							//���S�t���O
	int m_nPriority;						//�`��D��x
	D3DXVECTOR3 m_Pos;						//�I�u�W�F�N�g�̈ʒu
	TYPE m_Type;							//�I�u�W�F�N�g�̎��
};

#endif