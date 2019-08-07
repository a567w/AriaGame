/************************************************************************************************/
/**
 * @class		KsMaterialManager
 * @brief		�}�e���A���}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�{���́A�n�b�V���e�[�u���Ȃǂ��g�p�����ق������������܂�e�N�X�`���}�e���A���́A
 *				���܂�A�g��Ȃ��͂��Ȃ̂Ő��`�ŒT������B
 */
/************************************************************************************************/
class KsMaterialManager : public KsSingleton< KsMaterialManager >
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsMateiralManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsMateiralManager();

		/**
		 * �w�肵�����O�̃e�N�X�`������������
		 * �擾������ɎQ�ƃJ�E���g��������K�v������
		 * @param	pName				�t�@�C����
		 * @return						���������e�N�X�`���̃|�C���^
		 */
		virtual KsTexture*				find( const KsChar* pName );

		/**
		 * �������Č���������Q�ƃJ�E���g���A�b�v����
		 * @param	pName				�t�@�C����
		 * @return						���������e�N�X�`���̃|�C���^
		 */
		virtual KsTexture*				findRefInc( const KsChar* pName );

		/**
		 * �e�N�X�`����ǉ�����
		 * DEBUG���[�h�̂Ƃ��́A2�d�o�^�`�F�b�N������
		 * @param	pMaterial			�ǉ�����e�N�X�`���̃|�C���^
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					add( KsMaterial* pMaterial );

		/**
		 * �e�N�X�`�����}�l�[�W�������菜��
		 * @param	pMaterial			��菜���e�N�X�`���̃|�C���^
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					remove( KsMaterial* pMaterial );

		/**
		 * �e�N�X�`�����폜����
		 * @param	pMaterial			�폜����e�N�X�`���̃|�C���^
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					destroy( KsMaterial* pMaterial );

		/**
		 * ���ׂẴe�N�X�`����j������(�Q�ƃJ�E���g�֌W�Ȃ��j�������)
		 * @retval	ksTRUE				����
		 * @retval	ksFALSE				���s
		 */
		virtual KsBool					destroyAll();

		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return						�V���O���g���̎Q��
		 */
		static KsMaterialManager&		getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return						�V���O���g���̃|�C���^
		 */
		static KsMaterialManager*		getInstancePtr();

	protected:
		KsTexture*						m_pTop;		/**< ���X�g�̐擪�|�C���^	*/
};

