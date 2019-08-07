/************************************************************************************************/
/** 
 * @file		KsShaderManager.h
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSHADERMANAGER_H__
#define __KSSHADERMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsShaderProgram;

/************************************************************************************************/
/**
 * @class		KsShaderManager
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�{���́A�n�b�V���e�[�u���Ȃǂ��g�p�����ق������������܂�e�N�X�`���}�e���A���́A
 *				���܂�A�g��Ȃ��͂��Ȃ̂Ő��`�ŒT������B
 */
/************************************************************************************************/
class ksENGINE_API KsShaderManager : public KsSingleton< KsShaderManager >
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsShaderManager(){}

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsShaderManager(){}

		/**
		 * �t�@�C������V�F�[�_�[�𐶐�
		 * @param	pFileName			�t�@�C����
		 * @param	pEntryPoint			�G���g���[�|�C���g
		 * @param	shaderModel			�V�F�[�_�[���f��
		 * @param	shaderType			�V�F�[�_�[�^�C�v
		 * @return						�V�F�[�_�[�v���O�����̃|�C���^
		 */
		virtual KsShaderProgram*		createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel, ksSHADER_TYPE shaderType ) = 0;

		/**
		 * �f�[�^����V�F�[�_�[�𐶐�
		 * @param	pData				�f�[�^
		 * @param	dataSize			�f�[�^�T�C�Y
		 * @param	shaderType			�V�F�[�_�[�^�C�v
		 * @return						�V�F�[�_�[�v���O�����̃|�C���^
		 */
		virtual KsShaderProgram*		createFromMemory( const void* pData, KsUInt32 dataSize, ksSHADER_TYPE shaderType ) = 0;

		/**
		 * �t�@�C������V�F�[�_�[�𐶐�
		 * @param	pFileName			�t�@�C����
		 * @param	pEntryPoint			�G���g���[�|�C���g
		 * @param	shaderModel			�V�F�[�_�[���f��
		 * @param	shaderType			�V�F�[�_�[�^�C�v
		 * @return						�V�F�[�_�[�v���O�����̃|�C���^
		 */
		virtual KsShaderProgram*		createFromResource( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel, ksSHADER_TYPE shaderType ) = 0;

		/**
		 * �w�肵�����O�̃V�F�[�_�[����������
		 * �擾������ɎQ�ƃJ�E���g��������K�v������
		 * @param	pName				�t�@�C����
		 * @return						���������V�F�[�_�[�̃|�C���^
		 */
		virtual KsShaderProgram*		find( const KsChar* pName );

		/**
		 * �������Č���������Q�ƃJ�E���g���A�b�v����
		 * @param	pName				�t�@�C����
		 * @return						���������V�F�[�_�[�̃|�C���^
		 */
		virtual KsShaderProgram*		findRefInc( const KsChar* pName );

		/**
		 * �V�F�[�_�[��ǉ�����
		 * DEBUG���[�h�̂Ƃ��́A2�d�o�^�`�F�b�N������
		 * @param	pShader				�ǉ�����V�F�[�_�[�̃|�C���^
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					add( KsShaderProgram* pShader );

		/**
		 * �V�F�[�_�[���}�l�[�W�������菜��
		 * @param	pShader				��菜���V�F�[�_�[�̃|�C���^
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					remove( KsShaderProgram* pShader );

		/**
		 * �V�F�[�_�[���폜����
		 * @param	pShader				�폜����V�F�[�_�[�̃|�C���^
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					destroy( KsShaderProgram* pShader );

		/**
		 * ���ׂẴV�F�[�_�[��j������(�Q�ƃJ�E���g�֌W�Ȃ��j�������)
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					destroyAll();

	protected:
		KsHashTable< KsShaderProgram* >	m_pShaders;		/**< �V�F�[�_�[���X�g	*/

	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return						�V���O���g���̎Q��
		 */
		static KsShaderManager&			getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return						�V���O���g���̃|�C���^
		 */
		static KsShaderManager*			getInstancePtr();
};

#endif		/* __KSSHADERMANAGER_H__ */




