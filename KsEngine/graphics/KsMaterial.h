/************************************************************************************************/
/** 
 * @file		KsMaterial.h
 * @brief		�}�e���A��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMATERIAL_H__
#define __KSMATERIAL_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsTexture;

/************************************************************************************************/
/**
 * �}�e���A���N���X
 * @class		KsMaterial
 * @author		kato tukasa
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		(�g������)�g�p����e�N�X�`���̃|�C���^��ێ�����K�v������
 *				flags �Ł@�ǂ̃e�N�X�`�����g�p���邩�𒲂ׂ� std::vector< KsTexture* > m_pTextures;
 */
/************************************************************************************************/
class ksENGINE_API KsMaterial// : public KsRefCounter
{
	public:
		KsString						m_name;			/**< ���O							*/
		KsInt32							m_id;			/**< ID								*/
		KsColorReal						m_diffuse;		/**< �f�B�t���[�Y�F( �g�U�� )			*/
		KsColorReal						m_ambient;		/**< �A���r�G���g�F( ���� )			*/
		KsColorReal						m_specular;		/**< �X�y�L�����F( ���ʌ� )			*/
		KsColorReal						m_emissive;		/**< �G�~�b�V�����F					*/
		KsReal							m_power;		/**< �X�y�L���� �n�C���C�g�̑N��		*/
		KsInt32							m_textureID;	/**< �e�N�X�`��ID					*/
		KsTexture*						m_pTexture;		/**< �e�N�X�`��						*/

		/**
		 * �R���X�g���N�^
		 */
										KsMaterial() : m_id( 0 ), m_power( 0.0f ), m_textureID( -1 ), m_pTexture( 0 ) {}

		/**
		 * �R���X�g���N�^( �}�e���A�����Z�b�g���� )
		 * @param	pDiffuse			�f�B�t���[�Y�F
		 * @param	pAmbient			�A���r�G���g�F
		 * @param	pSpecular			�X�y�L�����F
		 * @param	pEmissive			�G�~�b�V�����F
		 * @param	power				�X�y�L���� �n�C���C�g�̑N��
		 */
										KsMaterial( const KsColorReal* pDiffuse, const KsColorReal* pAmbient, const KsColorReal* pSpecular, const KsColorReal* pEmissive, KsReal power );

		/**
		 * �R���X�g���N�^( �}�e���A�����Z�b�g���� )
		 * @param	refDiffuse			�f�B�t���[�Y�F
		 * @param	refAmbient			�A���r�G���g�F
		 * @param	refSpecular			�X�y�L�����F
		 * @param	refEmissive			�G�~�b�V�����F
		 * @param	power				�X�y�L���� �n�C���C�g�̑N��
		 */
										KsMaterial( const KsColorReal& refDiffuse, const KsColorReal& refAmbient, const KsColorReal& refSpecular, const KsColorReal& refEmissive, KsReal power );

		/**
		 * �R�s�[�R���X�g���N�^
		 * @param	refMaterial			�}�e���A��
		 */
										KsMaterial( const KsMaterial& refMaterial );

		/**
		 * �R�s�[�R���X�g���N�^
		 * @param	pMaterial			�}�e���A��
		 */
										KsMaterial( const KsMaterial* pMaterial );

		/**
		 * �f�B�t���[�Y�F���擾
		 * @return						�f�B�t���[�Y�F
		 */
		KsColorReal*					getDiffuse() { return &m_diffuse; }
		
		/**
		 * �A���r�G���g�F���擾
		 * @return						�A���r�G���g�F
		 */
		KsColorReal*					getAmbient() { return &m_ambient; }

		/**
		 * �X�y�L�����F���擾
		 * @return						�X�y�L�����F
		 */
		KsColorReal*					getSpecular() { return &m_specular; }
		
		/**
		 * �G�~�b�V�����F���擾
		 * @return						�G�~�b�V�����F
		 */
		KsColorReal*					getEmissive() { return &m_emissive; }

		/**
		 * �X�y�L���� �n�C���C�g�̑N�����擾
		 * @return						�X�y�L���� �n�C���C�g�̑N��
		 */
		KsReal							getPower() const { return m_power; }

		/**
		 * �g�p���Ă���e�N�X�`�����擾����
		 * @return						�g�p���Ă���e�N�X�`���̃|�C���^
		 */
		KsTexture*						getTexture() { return m_pTexture; }

		/**
		 * �e�N�X�`��ID���擾����
		 * @return						�e�N�X�`��ID
		 */
		KsInt32							getTextureID() const { return m_textureID; }
		
		/**
		 * �f�B�t���[�Y�F���擾
		 * @return						�f�B�t���[�Y�F
		 */
		void							setDiffuse( const KsColorReal& diffuse ) { m_diffuse = diffuse; }
		
		/**
		 * �A���r�G���g�F���擾
		 * @return						�A���r�G���g�F
		 */
		void							setAmbient( const KsColorReal& ambient ) { m_ambient = ambient; }

		/**
		 * �X�y�L�����F���擾
		 * @return						�X�y�L�����F
		 */
		void							setSpecular( const KsColorReal& specular ) { m_specular = specular; }
		
		/**
		 * �G�~�b�V�����F���擾
		 * @return						�G�~�b�V�����F
		 */
		void							setEmissive( const KsColorReal& emissive ) { m_emissive = emissive; }

		/**
		 * �X�y�L���� �n�C���C�g�̑N�����擾
		 * @return						�X�y�L���� �n�C���C�g�̑N��
		 */
		void							setPower( KsReal power ) { m_power = power; }

		/**
		 * �g�p���Ă���e�N�X�`�����擾����
		 * @param	pTexture			�g�p���Ă���e�N�X�`���̃|�C���^
		 */
		void							setTexture( KsTexture* pTexture ) { m_pTexture = pTexture; }

		/**
		 * �e�N�X�`��ID���擾����
		 * @param	textureID			�e�N�X�`��ID
		 */
		void							setTextureID( KsInt32 textureID ) { m_textureID = textureID; }

		/**
		 * �}�e���A�����Z�b�g����
		 * @param	refDiffuse			�f�B�t���[�Y�F
		 * @param	refAmbient			�A���r�G���g�F
		 * @param	refSpecular			�X�y�L�����F
		 * @param	refEmissive			�G�~�b�V�����F
		 * @param	power				�X�y�L���� �n�C���C�g�̑N��
		 */
		void							set( const KsColorReal& refDiffuse, const KsColorReal& refDmbient, const KsColorReal& refSpecular, const KsColorReal& refEmissive, KsReal power );

		/**
		 * �}�e���A�����Z�b�g����
		 * @param	pDiffuse			�f�B�t���[�Y�F
		 * @param	pAmbient			�A���r�G���g�F
		 * @param	pSpecular			�X�y�L�����F
		 * @param	pEmissive			�G�~�b�V�����F
		 * @param	power				�X�y�L���� �n�C���C�g�̑N��
		 */
		void							set( const KsColorReal* pDiffuse, const KsColorReal* pAmbient, const KsColorReal* pSpecular, const KsColorReal* pEmissive, KsReal power );

		/**
		 * �}�e���A�����Z�b�g����
		 * @param	refMaterial			�}�e���A��
		 */
		void							set( const KsMaterial& refMaterial );

		/**
		 * �}�e���A�����Z�b�g����
		 * @param	pMaterial			�}�e���A��
		 */
		void							set( const KsMaterial* pMaterial );

		KsBool							operator == ( const KsMaterial& refMaterial ) const	{ return ( 0 == memcmp( this, &refMaterial, sizeof(KsMaterial) ) ); }
		KsBool							operator != ( const KsMaterial& refMaterial ) const	{ return ( 0 != memcmp( this, &refMaterial, sizeof(KsMaterial) ) ); }
		const KsMaterial&				operator  = ( const KsMaterial& refMaterial )		{ memcpy( &m_diffuse, &refMaterial, sizeof(KsMaterial) ); return ( *this ); }
};

/************************************************************************************************/
/**
 * �}�e���A�����X�g
 */
/************************************************************************************************/
typedef KsArray< KsMaterial* >		KsMaterialArray;


#endif		/* __KSMATERIAL_H__ */


