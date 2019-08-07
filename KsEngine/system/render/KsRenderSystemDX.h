/************************************************************************************************/
/** 
 * @file		KsRenderSystemDX.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSTEMDX_H__
#define __KSRENDERSYSTEMDX_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsRenderSystem.h"
#include "KsBufferManagerDX.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>
#include <Cg/Cg.h>
#include <Cg/CgD3D9.h>

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsAdapterDXList;
class KsAdapterDX;

/************************************************************************************************/
/**
 * @class		KsRenderSystemDX
 * @brief		DirectX�p�̕`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderSystemDX : public KsRenderSystem
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsRenderSystemDX();

		/**
		 * �R���X�g���N�^
		 * @param		hWnd				�E�C���h�E�̃n���h��
		 */
											KsRenderSystemDX( HWND hWnd );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsRenderSystemDX();

		/**
		 * ����������
		 * @param		hWnd				�E�C���h�E�̃n���h��
		 * @retval		ksTRUE				����������
		 * @retval		ksFALSE				���������s
		 */
		virtual KsBool						initialize( HWND hWnd );

		/**
		 * �㏈��
		 * @retval		ksTRUE				�㏈������
		 * @retval		ksFALSE				�㏈�����s
		 */
		virtual KsBool						terminate();
		
		/**
		 * �V�[���`��J�n
		 */
		virtual void						beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * �V�[���`��I��
		 */
		virtual void						endScene();

		/**
		 * �`��o�b�t�@�ƕ\���o�b�t�@�����ւ�
		 */
		virtual void						swapBuffer();

		/**
		 * �}�e���A�����Z�b�g����
		 * @param		pMaterial			�}�e���A��
		 */
		virtual void						setMaterial( KsMaterial* pMaterial );

		/**
		 * �r���[�|�[�g���Z�b�g����
		 * @param		pViewport			�r���[�|�[�g�ݒ�
		 */
		virtual void						setViewport( const KsViewport* pViewport );

		/**
		 * �g�����X�t�H�[������
		 * @param		state				�g�����X�t�H�[���̃��[�h
		 * @param		pMatrix				�ϊ��}�g���b�N�X
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix );

		/**
		 * �t�H�O���Z�b�g����
		 * @param		pFog				�t�H�O���Z�b�g����( NULL )���Z�b�g����ƃt�H�O�𖳌�
		 */
		virtual void						setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density );

		/**
		 * ���C�g��ǉ�����
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		pLight				���C�g���
		 * @note							���C�g��ݒu�ł��鐔�́A�ő�W�ł��B<br>
		 *									���C�g����菜�����Ƃ��͎�菜���������C�g�̃C���f�b�N�X�ƃ��C�g��NULL���Z�b�g���Ă��������B
		 */
		virtual void						setLight( KsUInt32 index, const KsLight* pLight );

		/**
		 * �w�胉�C�g��L���A�����ɂ���B
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		flag				���C�g��ON OFF�̃t���O( ksTRUE: ON, ksFALSE: OFF )
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag );

		/**
		 * �Z�`��`��
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		w					��
		 * @param		h					����
		 * @param		color				�F
		 */
		virtual void						drawRect( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsColor color );

		/**
		 *
		 */
		virtual void						drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer );

		virtual void						auto3DMode(){

			m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
			m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
			m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
			m_pD3DDevice->SetRenderState( D3DRS_COLORVERTEX, FALSE );
			m_pD3DDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_COLORVALUE( 0.2f, 0.2f, 0.2f, 1.0f ) );

			//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

			D3DLIGHT9 light;
			ZeroMemory( &light, sizeof(light) );
			light.Type = D3DLIGHT_DIRECTIONAL;

			D3DXVECTOR3 vecDir;
			//vecDir = D3DXVECTOR3(0.5f, 2.0f, -5.5f);
			vecDir = D3DXVECTOR3(0.0f, -2.0f, -4.0f);
			D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );


			// set directional light diffuse color
			light.Diffuse.r = 1.0f;
			light.Diffuse.g = 1.0f;
			light.Diffuse.b = 1.0f;
			light.Diffuse.a = 1.0f;
			light.Specular.r = 1.0f;
			light.Specular.g = 1.0f;
			light.Specular.b = 1.0f;
			light.Specular.a = 1.0f;

			m_pD3DDevice->SetLight( 0, &light );
			m_pD3DDevice->LightEnable( 0, TRUE );


			D3DXMATRIX matView;
			D3DXVECTOR3 pos(0.0f, 0.8f, 3.0f);
			D3DXVECTOR3 pnt(0.0f, 0.8f, 0.0f);
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			//D3DXMatrixLookAtLH(&matView, &pos, &pnt, &up);
			D3DXMatrixLookAtRH(&matView, &pos, &pnt, &up);
			m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView); 



			D3DXMATRIX mProjection;
			//D3DXMatrixPerspectiveFovLH( &mProjection, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 500.0f );
			D3DXMatrixPerspectiveFovRH( &mProjection, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 500.0f );
			m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &mProjection );

		}

	private:
		void								makeMatrixDX( D3DMATRIX* pMatrixDX, const KsMatrix* pMatrix  );
	public:
		IDirect3D9*							m_pD3D;					/**< DirectX Object							*/
		IDirect3DDevice9*					m_pD3DDevice;			/**< DirectX Device							*/
		D3DCAPS9							m_caps;					/**< DirectX Caps							*/
		D3DPRESENT_PARAMETERS				m_present;				/**< DirectX Present						*/
		KsBool								m_vsync;				/**< vsync���g�p���邩�̃t���O				*/
		KsBool								m_useStencilBuffer;		/**< �X�e���V���o�b�t�@���g�p���邩�ǂ���		*/

		D3DMULTISAMPLE_TYPE					m_FSAAType;				/**< �}���`�T���v�����O�^�C�v					*/
		KsUInt32							m_FSAAQuality;			/**< �}���`�T���v�����O�̕i��(level)			*/
	
		KsAdapterDX*						m_pAdapter;				/**< ���ݎg�p���Ă���A�_�v�^�[				*/
		KsAdapterDXList*					m_pAdapterList;			/**< �A�_�v�^�[���X�g							*/

		HWND								m_hWnd;					/**< �E�C���h�E�̃n���h��						*/
		//HINSTANCE							m_D3DLibrary;			/**< ���C�u����								*/
		//HINSTANCE							m_hInstance;			/**< �E�C���h�E�̃C���X�^���X					*/
		//ConfigOptionMap						m_Options;				/**< �I�v�V����								*/

		KsBool								m_bDeviceLost;			/**< �f�o�C�X�����X�g���ꂽ���ǂ���			*/
		KsBool								m_bFullScreen;

};
#if 0

class KsRenderSystemDX : public KsRenderSystem
{
	public:

		/**
		 * �e�N�X�`�����Z�b�g����
		 * @param		statge				�e�N�X�`���X�e�[�W
		 * @param		pTexture			�e�N�X�`��
		 */
		virtual void						setTexture(  KsUInt32 stage, KsTexture* pTexture );

		/**
		 * �����_�[�X�e�[�g
		 * @param		state				�X�e�[�g�̎��
		 * @param		value				�X�e�[�g�ɑΉ�����l
		 */
		virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value );

		void								setSrcBlendFunc( ksBLEND_MODE blend );
		void								setDstBlendFunc( ksBLEND_MODE blend );
		void								setCullMode( ksCULL_MODE value );
		void								setShadeMode( ksSHADE_MODE value );


		virtual KsTexture*					createTexture( const KsChar* pFileName );

	protected:
	
		IDirect3D9*							m_pD3D;					/**< DirectX Object							*/
		IDirect3DDevice9*					m_pD3DDevice;			/**< DirectX Device							*/
		D3DCAPS9							m_caps;					/**< DirectX Caps							*/
		D3DPRESENT_PARAMETERS				m_present;				/**< DirectX Present						*/
		KsBool								m_vsync;				/**< vsync���g�p���邩�̃t���O				*/
		KsBool								m_useStencilBuffer;		/**< �X�e���V���o�b�t�@���g�p���邩�ǂ���		*/

		D3DMULTISAMPLE_TYPE					m_FSAAType;				/**< �}���`�T���v�����O�^�C�v					*/
		KsUInt32							m_FSAAQuality;			/**< �}���`�T���v�����O�̕i��(level)			*/
	
		KsAdapterDX*						m_pAdapter;				/**< ���ݎg�p���Ă���A�_�v�^�[				*/
		KsAdapterDXList*					m_pAdapterList;			/**< �A�_�v�^�[���X�g							*/

		HWND								m_hWnd;					/**< �E�C���h�E�̃n���h��						*/

		KsBool								m_bDeviceLost;			/**< �f�o�C�X�����X�g���ꂽ���ǂ���			*/
		KsBool								m_bFullScreen;
};

#endif		/* __KSRENDERSYSTEMDX_H__ */

#endif

