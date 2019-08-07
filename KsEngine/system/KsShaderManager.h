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
#include "KsType.h"
#include "KsSingleton.h"
#include "KsHash.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsShader;

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
		 * �V�F�[�_�[�p�����[�^
		 */
		enum ksSHADER_PARAM
		{
			ksSHADER_TIME,
			ksSHADER_WORLD_MATRIX,
			ksSHADER_VIEW_MATRIX,
			ksSHADER_WORLD_VIEW_MATRIX,
			ksSHADER_VIEW_PROJECTION_MATRIX,
			ksSHADER_WORLD_VIEW_PROJECTION_MATRIX,
			ksSHADER_MATERIAL_DIFFUSE,
			ksSHADER_MATERIAL_AMBIENT,
			ksSHADER_MATERIAL_SPECULER,
			ksSHADER_LIGHT_DIFFUSE,
			ksSHADER_LIGHT_AMBIENT,
			ksSHADER_LIGHT_SPECULER,
			ksSHADER_GLOBAL_DATA_MAX,
			ksSHADER_FORCE32          = 0x7fffffff,
		};
#if 0
		static const KsChar*	 s_globalShaderDataParams[] = 
		{
			"g_fTime",
			"g_ViewMatrix",
			"g_ViewProjectionMatrix",
			"g_materialDiffuseColor",
			"g_materialAmbientColor",
			"g_materialAmbientColor",
		};
#endif

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsShaderManager(){}

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsShaderManager(){}

		/**
		 * �t�@�C������V�F�[�_�[�𐶐�
		 * @param	_bCompiled		�R���p�C���ς݂��ǂ����̃t���O
		 * @return					�V�F�[�_�[�f�[�^�̃|�C���^
		 */
		virtual KsShader*			createFromFile( const KsChar* pName, KsBool _bCompiled ) = 0;

		/**
		 * ���\�[�X����V�F�[�_�[�𐶐�
		 * @param	_bCompiled		�R���p�C���ς݂��ǂ����̃t���O
		 * @return					�V�F�[�_�[�f�[�^�̃|�C���^
		 */
		virtual KsShader*			createFromResource( const KsChar* pName, KsBool _bCompiled ) = 0;

		/**
		 * �w�肵�����O�̃V�F�[�_�[����������
		 * �擾������ɎQ�ƃJ�E���g��������K�v������
		 * @param	pName			�t�@�C����
		 * @return					���������V�F�[�_�[�̃|�C���^
		 */
		virtual KsShader*			find( const KsChar* pName );

		/**
		 * �������Č���������Q�ƃJ�E���g���A�b�v����
		 * @param	pName			�t�@�C����
		 * @return					���������V�F�[�_�[�̃|�C���^
		 */
		virtual KsShader*			findRefInc( const KsChar* pName );

		/**
		 * �V�F�[�_�[��ǉ�����
		 * DEBUG���[�h�̂Ƃ��́A2�d�o�^�`�F�b�N������
		 * @param	pShader			�ǉ�����V�F�[�_�[�̃|�C���^
		 * @retval	ksTRUE			����
		 * @retval	ksFALSE			���s
		 */
		virtual KsBool				add( KsShader* pShader );

		/**
		 * �V�F�[�_�[���}�l�[�W�������菜��
		 * @param	pShader			��菜���V�F�[�_�[�̃|�C���^
		 * @retval	ksTRUE			����
		 * @retval	ksFALSE			���s
		 */
		virtual KsBool				remove( KsShader* pShader );

		/**
		 * �V�F�[�_�[���폜����
		 * @param	pShader			�폜����V�F�[�_�[�̃|�C���^
		 * @retval	ksTRUE			����
		 * @retval	ksFALSE			���s
		 */
		virtual KsBool				destroy( KsShader* pShader );

		/**
		 * ���ׂẴV�F�[�_�[��j������(�Q�ƃJ�E���g�֌W�Ȃ��j�������)
		 * @retval	ksTRUE			����
		 * @retval	ksFALSE			���s
		 */
		virtual KsBool				destroyAll();


		virtual void				setVertexShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setVertexShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setVertexShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count ) = 0;

		virtual void				setPixelShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setPixelShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setPixelShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count ) = 0;

#if 0
		virtual void				setTime( KsReal fTime ) = 0;
		virtual void				setViewMatrix( const KsMatrix4x4* pMatrix ) = 0;
		virtual void				setViewProjectionMatrix( const KsMatrix4x4* pMatrix ) = 0;
		virtual void				setWorldViewProjectionMatrix( const KsMatrix4x4* pMatrix ) = 0;
		virtual void				setWorldMatrix( const KsMatrix4x4* pMatrix ) = 0;

		virtual void				setMaterialDiffuse( const KsColorReal* pColor ) = 0;
		virtual void				setMaterialAmbient( const KsColorReal* pColor ) = 0;
		virtual void				setMaterialSpeculer( const KsColorReal* pColor ) = 0;
		virtual void				setLightDiffuse( const KsColorReal* pColor ) = 0;
		virtual void				setLightAmbient( const KsColorReal* pColor ) = 0;
		virtual void				setLightSpeculer( const KsColorReal* pColor ) = 0;
		//setVertexDeclaration

		HRESULT CreateVertexDeclaration(          CONST D3DVERTEXELEMENT9* pVertexElements,
    IDirect3DVertexDeclaration9** ppDecl
);

typedef struct _D3DVERTEXELEMENT9 {
    WORD Stream;
    WORD Offset;
    BYTE Type;
    BYTE Method;
    BYTE Usage;
    BYTE UsageIndex;
} D3DVERTEXELEMENT9;

HRESULT SetVertexDeclaration(          IDirect3DVertexDeclaration9 *pDecl
);

#endif
	protected:
		KsHashTable< KsShader* >	m_pShaders;		/**< �V�F�[�_�[���X�g	*/

	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return					�V���O���g���̎Q��
		 */
		static KsShaderManager&		getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return					�V���O���g���̃|�C���^
		 */
		static KsShaderManager*		getInstancePtr();
};

#endif		/* __KSSHADERMANAGER_H__ */




