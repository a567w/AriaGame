


#if 0


class ksENGINE_API KsShaderParam
{
	public:

		enum ksSHADER_PARAM_TYPE
		{
		  ksSHADER_PARAM_TYPE_NULL,
		  ksSHADER_PARAM_TYPE_SYSTEM,
		  PPT_FLOAT4,
		  PPT_VECTOR,
		  PPT_COLOR,
		  PPT_QUAT,
		  PPT_MATRIX
		};

		/**
		* \enum SHADERSYSTEMPARAM
		* \brief List of available system parameters for pipeline shaders
		*/
		enum SHADERSYSTEMPARAM
		{
		  /*! Bit set for all system matrix parameters */
		  SYSTEMMATRIXPARAM                          = 0x00010000,

		  /*! Current model matrix */
		  PSP_MODEL_MATRIX                           = 0x00010001,

		  /*! Current view matrix */
		  PSP_VIEW_MATRIX                            = 0x00010002,

		  /*! Current projection matrix */
		  PSP_PROJECTION_MATRIX                      = 0x00010003,

		  /*! Current concatenated model and view matrix */
		  PSP_MODELVIEW_MATRIX                       = 0x00010004,

		  /*! Current concatenated model, view and projection matrix */
		  PSP_MODELVIEWPROJ_MATRIX                   = 0x00010005,

		  /*! Inverted current model matrix */
		  PSP_INV_MODEL_MATRIX                       = 0x00010006,


		  /*! Bit set for all light parameters */
		  LIGHTPARAM                                 = 0x00020000,

		  /*! Current light position in world space */
		  PSP_LIGHT_POSITION                         = 0x00020001,

		  /*! Current light direction in world space */
		  PSP_LIGHT_DIRECTION                        = 0x00020002,

		  /*! Current light diffuse color */
		  PSP_LIGHT_DIFFUSE_COLOR                    = 0x00020003,

		  /*! Current light ambient color */
		  PSP_LIGHT_AMBIENT_COLOR                    = 0x00020004,

		  /*! Current light specular color */
		  PSP_LIGHT_SPECULAR_COLOR                   = 0x00020005,

		  /*! Current light position in object space */
		  PSP_LIGHT_POSITION_OBJECTSPACE             = 0x00020006,

		  /*! Current light direction in object space */
		  PSP_LIGHT_DIRECTION_OBJECTSPACE            = 0x00020007,

		  /*! Attenuation, values are 1.0f / ( constant | linear | quadratic ) for rgb channels respectively */
		  PSP_LIGHT_ATTENUATION                      = 0x00020008,

		  /*! Reciprocal attenuation, values are 1.0f / ( constant | linear | quadratic ) for rgb channels respectively */
		  PSP_LIGHT_REP_ATTENUATION                  = 0x00020009,


		  /*! Bit set for all mics system parameters */
		  MISCPARAM                                  = 0x00040000,

		  /*! Total ambient light color contributed by all lights, including directional and point lights */
		  PSP_TOTAL_LIGHT_AMBIENT_COLOR              = 0x00040001,

		  /*! Total ambient light color contributed by ambient lights, NOT including directional and point lights */
		  PSP_TOTAL_AMBIENTLIGHT_AMBIENT_COLOR       = 0x00040002,

		  /*! Eye position in object space */
		  PSP_EYE_POSITION_OBJECTSPACE               = 0x00040003
		};

		/*! Parameter index */
		unsigned int                                 m_uiIndex;

		/*! Parameter type */
		SHADERPARAMTYPE                              m_eType;

		/*! Value (depending on type) */
		union ShaderParamValue
		{
		  /*! System parameter (PPT_SYSTEM) */
		  SHADERSYSTEMPARAM                          m_eSystemID;

		  /*! Float (PPT_FLOAT4) */
		  float                                      m_afFloat[4];

		  /*! Vector (PPT_VECTOR), will be padded with 1.0f for w */
		  const Vector3d                            *m_pkVector;

		  /*! Color (PPT_COLOR) */
		  const Color                               *m_pkColor;

		  /*! Quaternion (PPT_QUAT) */
		  const Quaternion                          *m_pkQuaternion;

		  /*! Matrix (PPT_MATRIX) */
		  const Matrix                              *m_pkMatrix;

		}                                            m_Value;

		/*! Light index */
		unsigned int                                 m_uiLight;
};
/***************************************************************************
                       shader.h  -  Pipeline shaders
                             -------------------
    begin       : Mon May 05 2003
    copyright   : (C) 2003 by Reality Rift Studios
    email       : mattias@realityrift.com
 ***************************************************************************

 The contents of this file are subject to the Mozilla Public License Version
 1.1 (the "License"); you may not use this file except in compliance with
 the License. You may obtain a copy of the License at 
 http://www.mozilla.org/MPL/

 Software distributed under the License is distributed on an "AS IS" basis,
 WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 for the specific language governing rights and limitations under the
 License.

 The Original Code is the NeoEngine, NeoDevD3D9, shader.h

 The Initial Developer of the Original Code is Mattias Jansson.
 Portions created by Mattias Jansson are Copyright (C) 2003
 Reality Rift Studios. All Rights Reserved.

 Contributors: Keaton Mullis (kmullis@zianet.com)

 ***************************************************************************/

#ifndef __NED3D9SHADER_H
#define __NED3D9SHADER_H

#include "device.h"

#include <neoengine/shader.h>

namespace NeoD3D9
{


typedef NeoEngine::HashTable< class D3DShader > ShaderTable;


//typedef HRESULT ( __stdcall IDirect3DDevice9::* SetShaderConstantF )( unsigned int, const float*, unsigned int );


/**
  * \brief Direct3D9 implementation of pipeline shaders
  * \author Keaton Mullis (kmullis@zianet.com)
  * \author Mattias Jansson (mattias@realityrift.com)
  */
class D3D9Shader : public NeoEngine::Shader
{
	friend class Device;

	protected:

		/*! Vertex shader table */
		static ShaderTable                            s_kVSTable;

		/*! Fragment shader table */
		static ShaderTable                            s_kFSTable;


		/*! Render device */
		Device                                       *m_pkDevice;

		/*! Shader type enum (vertexshader or fragment shader) */
		NeoEngine::Shader::SHADERTYPE                 m_eType;

		/*! Shader compiled? */
		bool                                          m_bCompiled;

		/*! Vertex shader object */
		IDirect3DVertexShader9                       *m_pkVertexShader;

		/*! Pixel shader object */
		IDirect3DPixelShader9                        *m_pkPixelShader;


		/**
		* Bind parameter for vertex shader
		* \param pkParam                              Parameter
		* \param pkPrimitive                          Current primitive
		* \param rkView                               Current view matrix
		*/
		inline void                                   BindParameterVS( NeoEngine::ShaderParam *pkParam, NeoEngine::RenderPrimitive *pkPrimitive, const NeoEngine::Matrix &rkView );

		/**
		* Bind parameter for pixel shader
		* \param pkParam                              Parameter
		* \param pkPrimitive                          Current primitive
		* \param rkView                               Current view matrix
		*/
		inline void                                   BindParameterPS( NeoEngine::ShaderParam *pkParam, NeoEngine::RenderPrimitive *pkPrimitive, const NeoEngine::Matrix &rkView );


	public:

		/**
		* Create an Direct3D pipeline shader
		* \param pkDevice                             Render device
		* \param eType                                Shader type
		* \param pkFileManager                        File manager
		*/
		                                              D3D9Shader( Device *pkDevice, SHADERTYPE eType, NeoEngine::FileManager *pkFileManager );

		/**
		* Destruct this instance of the Direct3D vertex shader instance
		*/
		virtual                                      ~D3D9Shader();

		/**
		* Set name of shader
		* \param rstrName                             New name
		*/
		virtual void                                  SetName( const NeoEngine::HashString &rstrName );

		/**
		* Compile the pipeline shader
		* \param pstrSource                           Source string, null if use already loaded source
		* \return                                     True if compiled, or false
		*/
		virtual bool                                  Compile( const std::string *pstrSource );

		/**
		* Bind this pipeline shader, performing Direct3D specific operations
		* \param pkPrimitive                          Current render primitive
		* \param rkView                               Current view matrix (engine format)
		* \return                                     True if bound, or false if error
		*/
		bool                                          Bind( NeoEngine::RenderPrimitive *pkPrimitive, const NeoEngine::Matrix &rkView );

		/**
		* Bind light parameters
		* \param pkPrimitive                          Primitive currently processing
		* \return                                     True if bound, or false if error
		*/
		bool                                          BindLightParams( NeoEngine::RenderPrimitive *pkPrimitive );

		/**
		* Disable shader
		* \return                                     true if successful, false if error
		*/
		bool                                          Unbind();
};


};


#endif


/***************************************************************************
                       shader.h  -  Pipeline shaders
                             -------------------
    begin       : Mon May 05 2003
    copyright   : (C) 2003 by Reality Rift Studios
    email       : mattias@realityrift.com
 ***************************************************************************

 The contents of this file are subject to the Mozilla Public License Version
 1.1 (the "License"); you may not use this file except in compliance with
 the License. You may obtain a copy of the License at 
 http://www.mozilla.org/MPL/

 Software distributed under the License is distributed on an "AS IS" basis,
 WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 for the specific language governing rights and limitations under the
 License.

 The Original Code is the NeoEngine, shader.h

 The Initial Developer of the Original Code is Matt Holmes.
 Portions created by Matt Holmes are Copyright (C) 2003
 Matt Holmes. All Rights Reserved.

 Contributors: Mattias Jansson (mattias@realityrift.com)
               Cody Russell (cody@jhu.edu)

 ***************************************************************************/

#ifndef __NESHADER_H
#define __NESHADER_H


/**
  * \file shader.h
  * Programmable pipeline shaders
  */


#include "base.h"
#include "hashtable.h"
#include "loadableentity.h"
#include "pointer.h"


namespace NeoEngine
{


// External classes
class RenderDevice;
class Vector3d;
class Color;
class Matrix;
class Quaternion;


// Forward declarations
class Shader;





HashTableExport( ShaderParam );
typedef HashTable<ShaderParam> ShaderParamHash;


#ifdef WIN32
#  ifndef __HAVE_VECTOR_NESHADERPARAM
     UDTVectorEXPIMP( class ShaderParam* );
#    define __HAVE_VECTOR_NESHADERPARAM
#  endif
#endif


class NEOENGINE_API Shader : public RefCounter, public LoadableEntity
{
	friend class RenderDevice;

	public:

		/**
		* \enum SHADERTYPE
		* \brief Shader type identifier
		*/
		enum SHADERTYPE
		{
		  /*! Vertex shader */
		  VERTEXSHADER                                      = 0,

		  /*! Fragment shader */
		  FRAGMENTSHADER                                    = 1
		};

		/**
		* \enum SHADERTARGET
		* \brief Supported pipeline shader native types
		*/
		enum SHADERTARGET
		{
		  /*! Shader type is not supported */
		  NOTSUPPORTED                                       = 0,


		  /*! DX9 vertex shader group */
		  NEPT_DX9_VS_MASK                                   = 0x110,

		  /*! DX9 vertex shader 1.1 */
		  NEPT_DX9_VS_1_1                                    = 0x111,

		  /*! DX9 vertex shader 2.0 */
		  NEPT_DX9_VS_2_0                                    = 0x112,

		  /*! DX9 vertex shader 2.x */
		  NEPT_DX9_VS_2_X                                    = 0x113,


		  /*! DX9 pixel shader group */
		  NEPT_DX9_PS_MASK                                   = 0x120,

		  /*! DX9 pixel shader 1.1 */
		  NEPT_DX9_PS_1_1                                    = 0x121,

		  /*! DX9 pixel shader 1.2 */
		  NEPT_DX9_PS_1_2                                    = 0x122,

		  /*! DX9 pixel shader 1.3 */
		  NEPT_DX9_PS_1_3                                    = 0x123,

		  /*! DX9 pixel shader 1.4 */
		  NEPT_DX9_PS_1_4                                    = 0x124,

		  /*! DX9 pixel shader 2.0 */
		  NEPT_DX9_PS_2_0                                    = 0x125,

		  /*! DX9 pixel shader 2.x */
		  NEPT_DX9_PS_2_X                                    = 0x126,


		  /*! OpenGL vertex shader group */
		  NEPT_GL_VS_MASK                                    = 0x210,

		  /*! OpenGL ARB_vertex_program extension */
		  NEPT_GL_ARBVP_1                                    = 0x211,


		  /*! OpenGL fragment program group */
		  NEPT_GL_FS_MASK                                    = 0x220,

		  /*! OpenGL ARB_fragment_program extension */
		  NEPT_GL_ARBFP_1                                    = 0x221,

		  /*! OpenGL ATI_fragment_shader extension */
		  NEPT_GL_ATIFS                                      = 0x222,

		  /*! OpenGL NV_register_combiners extension */
		  NEPT_GL_NVRC                                       = 0x223,

		  /*! OpenGL NV_register_combiners2 extension */
		  NEPT_GL_NVRC_2                                     = 0x224
		};


#ifdef WIN32
#  ifndef __HAVE_VECTOR_NESHADERTARGET
     UDTVectorEXPIMP( SHADERTARGET );
#    define __HAVE_VECTOR_NESHADERTARGET
#  endif
#endif


	protected:

		/*! Current vertexshader target, set by render device */
		static NE_STATIC SHADERTARGET                        s_eVSTarget;

		/*! Current fragmentshader target, set by render device */
		static NE_STATIC SHADERTARGET                        s_eFSTarget;

		/*! Priority list of vertex shader profiles requested by application */
		static NE_STATIC std::vector< SHADERTARGET >         s_veVSPriority;

		/*! Priority list of fragment shader profiles requested by application */
		static NE_STATIC std::vector< SHADERTARGET >         s_veFSPriority;

		/*! Shader count */
		static NE_STATIC unsigned int                        s_uiCount;


		/*! Shader source code */
		std::string                                          m_strSource;

		/*! Shader type */
		SHADERTYPE                                           m_eShaderType;

		/*! Shader name */
		HashString                                           m_strName;

		/*! Shader ID */
		unsigned int                                         m_uiID;

		/*! Hashtable of currently registered parameters */
		ShaderParamHash                                      m_kParams;

		/*! Parameters by index */
		ShaderParam                                        **m_ppkParams;

		/*! All parameters */
		std::vector< ShaderParam* >                          m_vpkParams;

		/*! Parameters in need of rebinding */
		std::vector< ShaderParam* >                           m_vpkUpdatedParams;



		/**
		* Load the script source for this shader from the given file
		* \param uiFlags                                     Load flags
		* \return                                            True if loaded, or false
		*/
		bool                                                 LoadNode( unsigned int uiFlags );

		/**
		* Delete and clear all parameters
		*/
		void                                                 ClearParams();

		/**
		* Parse parameters and special neoengine comments for parameter bindings in the source
		*/
		void                                                 ParseParams();


	public:

		/**
		* Construct a new pipeline shader
		* \param eType                                       The type of shader to create (vertex or fragment)
		* \param pkFileManager                               File manager that loaded this shader shader, will use core file manager if null (default)
		*/
		                                                     Shader( SHADERTYPE eType, FileManager *pkFileManager = 0 );

		/**
		* Destroy this pipeline shader instance
		*/
		virtual                                             ~Shader();

		/**
		* Compile the shader
		* \param pstrSource                                  Pointer to source string, or null if already loaded
		* \return                                            True if succesful, false otherwise.
		*/
		virtual bool                                         Compile( const std::string *pstrSource = 0 ) = 0;

		/**
		* Set name of shader
		* \param rstrName                                    New name
		*/
		virtual void                                         SetName( const HashString &rstrName );

		/**
		* \return                                            Name of shader
		*/
		inline const HashString                             &GetName() const { return m_strName; }

		/**
		* \return                                            Shader ID
		*/
		inline unsigned int                                  GetID() const { return m_uiID; }

		/**
		* Get named parameter
		* \param rstrName                                    Name of parameter to get type of
		* \return                                            Parameter object
		*/
		inline ShaderParam                                  *GetParameter( const HashString &rstrName ) { return m_kParams.Find( rstrName ); }

		/**
		* Get parameter by index (register)
		* \param uiIndex                                     Register index
		* \return                                            Parameter object
		*/
		inline ShaderParam                                  *GetParameter( unsigned int uiIndex ) { return m_ppkParams[ uiIndex ]; }

		/**
		* Get all parameters for shader
		* \return                                            Vector with all parameters
		*/
		inline const std::vector< ShaderParam* >            &GetAllParameters() { return m_vpkParams; }

		/**
		* Notify shader that parameter has been updated
		* \param pkParameter                                 Parameter object
		*/
		void                                                 UpdateParameter( ShaderParam *pkParameter );

		/**
		* \return                                            Shader type (vertex or fragment)
		*/
		inline SHADERTYPE                                    GetType() const { return m_eShaderType; }

		/**
		* \param eType                                       Shader type (vertex or fragment)
		* \return                                            Current native target for shader type
		*/
		static inline SHADERTARGET                           GetTarget( SHADERTYPE eType ) { return( eType == VERTEXSHADER ? s_eVSTarget : s_eFSTarget ); }

		/**
		* Set priority list of profiles for a shader type. The backend will only choose among the profiles in this list
		* and will choose profiles in the order of the list.
		* \param eType                                       Shader type (vertex or fragment)
		* \param rvePriority                                 Vector of requested profiles in priority order (highest priority first)
		*/
		static void                                          SetPriority( SHADERTYPE eType, const std::vector< SHADERTARGET > &rvePriority );

		/**
		* Get shader target name as string
		* \param eTarget                                     Shader target identifier
		* \return                                            Name of shader target as string
		*/
		static std::string                                   GetTargetAsString( SHADERTARGET eTarget );

		/**
		* Get shader target identifier from string
		* \param rstrTarget                                  Shader target name as string
		* \return                                            Shader target identifier
		*/
		static SHADERTARGET                                  GetTargetFromString( const std::string &rstrTarget );
};


#ifndef __HAVE_SMARTPOINTER_NESHADER
   //Define smart pointer
#  ifdef _MSC_VER
#    pragma warning( disable : 4231 )
#  endif
   SmartPointer( Shader );
#  define __HAVE_SMARTPOINTER_NESHADER
#endif


};


#endif



/***************************************************************************
                     shader.cpp  -  Pipeline shaders
                             -------------------
    begin       : Wed May 7 2003
    copyright   : (C) 2003 by Reality Rift Studios
    email       : mattias@realityrift.com
 ***************************************************************************

 The contents of this file are subject to the Mozilla Public License Version
 1.1 (the "License"); you may not use this file except in compliance with
 the License. You may obtain a copy of the License at 
 http://www.mozilla.org/MPL/

 Software distributed under the License is distributed on an "AS IS" basis,
 WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 for the specific language governing rights and limitations under the
 License.

 The Original Code is the NeoEngine, NeoDevD3D9, shader.cpp

 The Initial Developer of the Original Code is Mattias Jansson.
 Portions created by Mattias Jansson are Copyright (C) 2003
 Reality Rift Studios. All Rights Reserved.

 Contributors: Keaton Mullis (kmullis@zianet.com)

 ***************************************************************************/

#include "shader.h"
#include "texture.h"

#include <neoengine/light.h>
#include <neoengine/scenenode.h>
#include <neoengine/logstream.h>

#include <d3dx9.h>

using namespace std;
using namespace NeoEngine;


namespace NeoD3D9
{


NeoEngine::ShaderPtr Device::CreateShader( Shader::SHADERTYPE eType )
{
	if( eType == Shader::VERTEXSHADER ) switch( D3D9Shader::s_eVSTarget )
	{
		case Shader::NEPT_DX9_VS_1_1:
		case Shader::NEPT_DX9_VS_2_0:
		case Shader::NEPT_DX9_VS_2_X:
			return new D3D9Shader( this, Shader::VERTEXSHADER, Core::Get()->GetFileManager() );

		case Shader::NOTSUPPORTED:
			break;

		default:
			neolog << LogLevel( ERROR ) << "*** Unable to create vertex shader: Unknown native vertex shader target [" << D3D9Shader::s_eVSTarget << "]" << endl;
			break;
	}
	else if( eType == Shader::FRAGMENTSHADER ) switch( D3D9Shader::s_eFSTarget )
	{
		case Shader::NEPT_DX9_PS_1_1:
		case Shader::NEPT_DX9_PS_1_2:
		case Shader::NEPT_DX9_PS_1_3:
		case Shader::NEPT_DX9_PS_1_4:
		case Shader::NEPT_DX9_PS_2_0:
		case Shader::NEPT_DX9_PS_2_X:
			return new D3D9Shader( this, Shader::FRAGMENTSHADER, Core::Get()->GetFileManager() );

		case Shader::NOTSUPPORTED:
			break;

		default:
			neolog << LogLevel( ERROR ) << "*** Unable to create fragment shader: Unknown native fragment shader target [" << D3D9Shader::s_eFSTarget << "]" << endl;
			break;
	}
	else
		neolog << LogLevel( ERROR ) << "*** Unable to create shader: Unknown type [" << eType << "]" << endl;

	return 0;
}


NeoEngine::ShaderPtr Device::GetShader( NeoEngine::Shader::SHADERTYPE eType, const std::string &rstrName )
{
	return (NeoEngine::Shader*)( ( eType == Shader::VERTEXSHADER ) ? D3D9Shader::s_kVSTable : D3D9Shader::s_kFSTable ).Find( rstrName );
}



ShaderTable D3D9Shader::s_kVSTable;
ShaderTable D3D9Shader::s_kFSTable;


D3D9Shader::D3D9Shader( Device *pkDevice, SHADERTYPE eType, FileManager *pkFileManager ) : 
	NeoEngine::Shader( eType, pkFileManager ),
	m_pkDevice( pkDevice ), 
	m_eType( eType ),
	m_bCompiled( false ),
	m_pkVertexShader( 0 ),
	m_pkPixelShader( 0 )
{
}


D3D9Shader::~D3D9Shader()
{
	if( m_pkDevice->m_pkVertexShader == this )
	{
		m_pkDevice->m_pkDevice->SetVertexShader( (IDirect3DVertexShader9*)0 );
		m_pkDevice->m_pkVertexShader = 0;
	}

	if( m_pkDevice->m_pkFragmentShader == this )
	{
		m_pkDevice->m_pkDevice->SetPixelShader( (IDirect3DPixelShader9*)0 );
		m_pkDevice->m_pkFragmentShader = 0;
	}

	if( m_pkVertexShader )
		m_pkVertexShader->Release();

	if( m_pkPixelShader )
		m_pkPixelShader->Release();

	( ( GetType() == VERTEXSHADER ) ? s_kVSTable : s_kFSTable ).Delete( m_strName, (D3DShader*)this );
}


void D3D9Shader::SetName( const HashString &rstrName )
{
	if( rstrName == GetName() )
		return;

	if( m_bCompiled )
	{
		ShaderTable &rkTable = ( ( GetType() == VERTEXSHADER ) ? s_kVSTable : s_kFSTable );
		
		rkTable.Delete( m_strName, (D3DShader*)this );

		m_strName = rstrName;

		rkTable.Insert( m_strName, (D3DShader*)this );
	}
	else
		m_strName = rstrName;
}


bool D3D9Shader::Compile( const string *pstrSource )
{
	if( m_bCompiled && !pstrSource )
		return true;

	if( m_pkVertexShader )
		m_pkVertexShader->Release(), m_pkVertexShader = 0;

	if( m_pkPixelShader )
		m_pkPixelShader->Release(), m_pkPixelShader = 0;

	ClearParams();

	m_bCompiled = false;

	if( pstrSource )
		m_strSource = *pstrSource;

	LPD3DXBUFFER pkBuffer = 0;
	LPD3DXBUFFER pkErr = 0;
	HRESULT hRes;

	if( FAILED( ( hRes = D3DXAssembleShader( m_strSource.c_str(), m_strSource.size() + 1, 0, 0, 0, &pkBuffer, &pkErr ) ) ) )
	{
		neolog << LogLevel( ERROR ) << "*** Unable to compile shader: Assembler failed";

		if( hRes == D3DERR_INVALIDCALL )
			neolog << " [D3DERR_INVALIDCALL]";
		else if( hRes == D3DXERR_INVALIDDATA )
			neolog << " [D3DXERR_INVALIDDATA]";
		else
			neolog << " [UNKNOWN ERROR CODE]";

		neolog << endl << (char*)pkErr->GetBufferPointer() << endl;

		return false;
	}

	if( pkErr ) pkErr->Release();

	if( m_eType == VERTEXSHADER )
	{
		if( FAILED( m_pkDevice->m_pkDevice->CreateVertexShader( (DWORD*)pkBuffer->GetBufferPointer(), &m_pkVertexShader ) ) )
		{
			neolog << LogLevel( ERROR ) << "*** Unable to compile vertex shader: Unable to create vertex shader" << endl;
			if( pkBuffer ) pkBuffer->Release();
			return false;
		}
	}
	else
	{
		if( FAILED( m_pkDevice->m_pkDevice->CreatePixelShader( (DWORD*)pkBuffer->GetBufferPointer(), &m_pkPixelShader ) ) )
		{
			neolog << LogLevel( ERROR ) << "*** Unable to compile fragment shader: Unable to create pixel shader" << endl;
			if( pkBuffer ) pkBuffer->Release();
			return false;
		}
	}

	if( pkBuffer ) pkBuffer->Release();

	m_bCompiled = true;

	ParseParams();

	return true;
}


void D3D9Shader::BindParameterVS( ShaderParam *pkParam, RenderPrimitive *pkPrimitive, const Matrix &rkView )
{
	static float afIdentity[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float afVal[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	unsigned int uiLight = pkParam->m_uiLight + m_pkDevice->m_uiCurLight;

	switch( pkParam->m_eType )
	{
		case ShaderParam::PPT_SYSTEM:
		{
			switch( pkParam->m_Value.m_eSystemID )
			{
				case ShaderParam::PSP_MODEL_MATRIX:
				{
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, &pkPrimitive->m_kModelMatrix.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_VIEW_MATRIX:
				{
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, &rkView.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_PROJECTION_MATRIX:
				{
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, &m_pkDevice->GetProjectionMatrix().m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_MODELVIEW_MATRIX:
				{
					Matrix kMat = rkView * pkPrimitive->m_kModelMatrix;
					
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, &kMat.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_MODELVIEWPROJ_MATRIX:
				{
					Matrix kMat( ( m_pkDevice->GetProjectionMatrix() * rkView ) * pkPrimitive->m_kModelMatrix );

					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, &kMat.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_INV_MODEL_MATRIX:
				{
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, &pkPrimitive->m_kInvModelMatrix.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_LIGHT_POSITION:
				{
					if( ( uiLight < m_pkDevice->m_uiNumLights ) && m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode() )
						*((Vector3d*)afVal) = m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode()->GetWorldTranslation();
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_DIRECTION:
				{
					if( ( uiLight < m_pkDevice->m_uiNumLights ) && m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode() )
						*((Vector3d*)afVal) = -m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode()->GetWorldTransform().GetColumn(2);
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_POSITION_OBJECTSPACE:
				{
					if( ( uiLight < m_pkDevice->m_uiNumLights ) && m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode() )
						*((Vector3d*)afVal) = pkPrimitive->m_kInvModelMatrix * m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode()->GetWorldTranslation();
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_DIRECTION_OBJECTSPACE:
				{
					if( ( uiLight < m_pkDevice->m_uiNumLights ) && m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode() )
						*((Vector3d*)afVal) = pkPrimitive->m_kInvModelMatrix * (-m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode()->GetWorldTransform().GetColumn(2));
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_AMBIENT_COLOR:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, m_pkDevice->m_ppkLights[ uiLight ]->m_kAmbient, 1 );
					else
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_DIFFUSE_COLOR:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, m_pkDevice->m_ppkLights[ uiLight ]->m_kDiffuse, 1 );
					else
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_SPECULAR_COLOR:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, m_pkDevice->m_ppkLights[ uiLight ]->m_kSpecular, 1 );
					else
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_ATTENUATION:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
					{
						afVal[0] = m_pkDevice->m_ppkLights[ uiLight ]->m_fConstantAttenuation;
						afVal[1] = m_pkDevice->m_ppkLights[ uiLight ]->m_fLinearAttenuation;
						afVal[2] = m_pkDevice->m_ppkLights[ uiLight ]->m_fQuadraticAttenuation;
						afVal[3] = 1.0f;
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					}
					else
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_REP_ATTENUATION:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
					{
						afVal[0] = 1.0f / m_pkDevice->m_ppkLights[ uiLight ]->m_fConstantAttenuation;
						afVal[1] = 1.0f / m_pkDevice->m_ppkLights[ uiLight ]->m_fLinearAttenuation;
						afVal[2] = 1.0f / m_pkDevice->m_ppkLights[ uiLight ]->m_fQuadraticAttenuation;
						afVal[3] = 1.0f;
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					}
					else
						m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_TOTAL_LIGHT_AMBIENT_COLOR:
				{
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, (const float*)m_pkDevice->m_kTotalAmbientLight, 1 );
					break;
				}

				case ShaderParam::PSP_TOTAL_AMBIENTLIGHT_AMBIENT_COLOR:
				{
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, (const float*)m_pkDevice->m_kAmbientLight, 1 );
					break;
				}

				case ShaderParam::PSP_EYE_POSITION_OBJECTSPACE:
				{
					*((Vector3d*)afVal) = ( rkView * pkPrimitive->m_kInvModelMatrix ).GetColumn(3);
					m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				default:
				{
					neolog << LogLevel( ERROR ) << "*** Unable to bind system parameter: Unsupported type" << endl;
					break;
				}
			}

			break;
		}

		case ShaderParam::PPT_FLOAT4:
		{
			m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, pkParam->m_Value.m_afFloat, 1 );
			break;
		}

		case ShaderParam::PPT_VECTOR:
		{
			float afVal[4] = { pkParam->m_Value.m_pkVector->x, pkParam->m_Value.m_pkVector->y, pkParam->m_Value.m_pkVector->z, 1.0f };
			m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
			break;
		}

		case ShaderParam::PPT_COLOR:
		{
			m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, (const float*)pkParam->m_Value.m_pkColor, 1 );
			break;
		}

		case ShaderParam::PPT_QUAT:
		{
			m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, (const float*)pkParam->m_Value.m_pkQuaternion, 1 );
			break;
		}

		case ShaderParam::PPT_MATRIX:
		{
			m_pkDevice->m_pkDevice->SetVertexShaderConstantF( pkParam->m_uiIndex, &pkParam->m_Value.m_pkMatrix->m_aafMatrix[0][0], 4 );			
			break;
		}

		default:
		{
			neolog << LogLevel( ERROR ) << "*** Unable to bind parameter: Unsupported type" << endl;
			break;
		}
	}
}


void D3D9Shader::BindParameterPS( ShaderParam *pkParam, RenderPrimitive *pkPrimitive, const Matrix &rkView )
{
	static float afIdentity[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float afVal[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	unsigned int uiLight = pkParam->m_uiLight + m_pkDevice->m_uiCurLight;

	switch( pkParam->m_eType )
	{
		case ShaderParam::PPT_SYSTEM:
		{
			switch( pkParam->m_Value.m_eSystemID )
			{
				case ShaderParam::PSP_MODEL_MATRIX:
				{
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, &pkPrimitive->m_kModelMatrix.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_VIEW_MATRIX:
				{
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, &rkView.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_PROJECTION_MATRIX:
				{
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, &m_pkDevice->GetProjectionMatrix().m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_MODELVIEW_MATRIX:
				{
					Matrix kMat = rkView * pkPrimitive->m_kModelMatrix;
					
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, &kMat.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_MODELVIEWPROJ_MATRIX:
				{
					Matrix kMat( ( m_pkDevice->GetProjectionMatrix() * rkView ) * pkPrimitive->m_kModelMatrix );

					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, &kMat.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_INV_MODEL_MATRIX:
				{
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, &pkPrimitive->m_kInvModelMatrix.m_aafMatrix[0][0], 4 );
					break;
				}

				case ShaderParam::PSP_LIGHT_POSITION:
				{
					if( ( uiLight < m_pkDevice->m_uiNumLights ) && m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode() )
						*((Vector3d*)afVal) = m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode()->GetWorldTranslation();
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_DIRECTION:
				{
					if( ( uiLight < m_pkDevice->m_uiNumLights ) && m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode() )
						*((Vector3d*)afVal) = -m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode()->GetWorldTransform().GetColumn(2);
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_POSITION_OBJECTSPACE:
				{
					if( ( uiLight < m_pkDevice->m_uiNumLights ) && m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode() )
						*((Vector3d*)afVal) = pkPrimitive->m_kInvModelMatrix * m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode()->GetWorldTranslation();
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_DIRECTION_OBJECTSPACE:
				{
					if( ( uiLight < m_pkDevice->m_uiNumLights ) && m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode() )
						*((Vector3d*)afVal) = pkPrimitive->m_kInvModelMatrix * (-m_pkDevice->m_ppkLights[ uiLight ]->GetSceneNode()->GetWorldTransform().GetColumn(2));
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_AMBIENT_COLOR:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, m_pkDevice->m_ppkLights[ uiLight ]->m_kAmbient, 1 );
					else
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_DIFFUSE_COLOR:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, m_pkDevice->m_ppkLights[ uiLight ]->m_kDiffuse, 1 );
					else
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_SPECULAR_COLOR:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, m_pkDevice->m_ppkLights[ uiLight ]->m_kSpecular, 1 );
					else
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_ATTENUATION:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
					{
						afVal[0] = m_pkDevice->m_ppkLights[ uiLight ]->m_fConstantAttenuation;
						afVal[1] = m_pkDevice->m_ppkLights[ uiLight ]->m_fLinearAttenuation;
						afVal[2] = m_pkDevice->m_ppkLights[ uiLight ]->m_fQuadraticAttenuation;
						afVal[3] = 1.0f;
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					}
					else
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_LIGHT_REP_ATTENUATION:
				{
					if( uiLight < m_pkDevice->m_uiNumLights )
					{
						afVal[0] = 1.0f / m_pkDevice->m_ppkLights[ uiLight ]->m_fConstantAttenuation;
						afVal[1] = 1.0f / m_pkDevice->m_ppkLights[ uiLight ]->m_fLinearAttenuation;
						afVal[2] = 1.0f / m_pkDevice->m_ppkLights[ uiLight ]->m_fQuadraticAttenuation;
						afVal[3] = 1.0f;
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					}
					else
						m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afIdentity, 1 );
					break;
				}

				case ShaderParam::PSP_TOTAL_LIGHT_AMBIENT_COLOR:
				{
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, (const float*)m_pkDevice->m_kTotalAmbientLight, 1 );
					break;
				}

				case ShaderParam::PSP_TOTAL_AMBIENTLIGHT_AMBIENT_COLOR:
				{
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, (const float*)m_pkDevice->m_kAmbientLight, 1 );
					break;
				}

				case ShaderParam::PSP_EYE_POSITION_OBJECTSPACE:
				{
					*((Vector3d*)afVal) = ( rkView * pkPrimitive->m_kInvModelMatrix ).GetColumn(3);
					m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
					break;
				}

				default:
				{
					neolog << LogLevel( ERROR ) << "*** Unable to bind system parameter: Unsupported type" << endl;
					break;
				}
			}

			break;
		}

		case ShaderParam::PPT_FLOAT4:
		{
			m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, pkParam->m_Value.m_afFloat, 1 );
			break;
		}

		case ShaderParam::PPT_VECTOR:
		{
			float afVal[4] = { pkParam->m_Value.m_pkVector->x, pkParam->m_Value.m_pkVector->y, pkParam->m_Value.m_pkVector->z, 1.0f };
			m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, afVal, 1 );
			break;
		}

		case ShaderParam::PPT_COLOR:
		{
			m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, (const float*)pkParam->m_Value.m_pkColor, 1 );
			break;
		}

		case ShaderParam::PPT_QUAT:
		{
			m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, (const float*)pkParam->m_Value.m_pkQuaternion, 1 );
			break;
		}

		case ShaderParam::PPT_MATRIX:
		{
			m_pkDevice->m_pkDevice->SetPixelShaderConstantF( pkParam->m_uiIndex, &pkParam->m_Value.m_pkMatrix->m_aafMatrix[0][0], 4 );			
			break;
		}

		default:
		{
			neolog << LogLevel( ERROR ) << "*** Unable to bind parameter: Unsupported type" << endl;
			break;
		}
	}
}


bool D3D9Shader::Bind( RenderPrimitive *pkPrimitive, const Matrix &rkView )
{
	if( !m_bCompiled )
		return false;

	if( m_eType == VERTEXSHADER )
	{
		if( FAILED( m_pkDevice->m_pkDevice->SetVertexShader( m_pkVertexShader ) ) )
			return false;

		//Bind all params
		vector< ShaderParam* >::iterator ppkParam = m_vpkParams.begin();
		vector< ShaderParam* >::iterator ppkEnd   = m_vpkParams.end();

		for( ; ppkParam != ppkEnd; ++ppkParam )
			BindParameterVS( *ppkParam, pkPrimitive, rkView );
	}
	else
	{
		if( FAILED( m_pkDevice->m_pkDevice->SetPixelShader( m_pkPixelShader ) ) )
			return false;

		//Bind all params
		vector< ShaderParam* >::iterator ppkParam = m_vpkParams.begin();
		vector< ShaderParam* >::iterator ppkEnd   = m_vpkParams.end();

		for( ; ppkParam != ppkEnd; ++ppkParam )
			BindParameterPS( *ppkParam, pkPrimitive, rkView );
	}

	//We don't use updated params for now, clear to avoid stockpiling pointers
	m_vpkUpdatedParams.clear();

	return true;
}


bool D3D9Shader::Unbind()
{
	if( m_eType == VERTEXSHADER )
	{
		if( FAILED( m_pkDevice->m_pkDevice->SetVertexShader( (IDirect3DVertexShader9*)0 ) ) )
			return false;
	}
	else
	{
		if( FAILED( m_pkDevice->m_pkDevice->SetPixelShader( (IDirect3DPixelShader9*)0 ) ) )
			return false;
	}

	return true;
}


bool D3D9Shader::BindLightParams( RenderPrimitive *pkPrimitive )
{
	//Bind all params
	vector< ShaderParam* >::iterator ppkParam = m_vpkParams.begin();
	vector< ShaderParam* >::iterator ppkEnd   = m_vpkParams.end();

	const Matrix &rkView = m_pkDevice->GetViewMatrix();

	for( ; ppkParam != ppkEnd; ++ppkParam )
	{
		if( ( (*ppkParam)->m_eType == ShaderParam::PPT_SYSTEM ) && ( (*ppkParam)->m_Value.m_eSystemID & ShaderParam::LIGHTPARAM ) )
		{
			if( m_eShaderType == Shader::VERTEXSHADER )
				BindParameterVS( *ppkParam, pkPrimitive, rkView );
			else
				BindParameterPS( *ppkParam, pkPrimitive, rkView );
		}
	}

	return true;
}


};


#endif 

