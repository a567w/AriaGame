/************************************************************************************************/
/**
 * @file		KsBinaryReader.h
 * @brief		�o�C�i���[���[�_�[
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBINARYREADER_H__
#define __KSBINARYREADER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsBinaryReader
 * @brief		�o�C�i���[���[�_�[
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsBinaryReader
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param		pFile			�t�@�C���|�C���^
		 */
		KsBinaryReader( const KsWChar* pFileName );

		/**
		 * �R���X�g���N�^
		 * @param		pFile			�t�@�C���|�C���^
		 */
		KsBinaryReader( const KsSChar* pFileName );

		/**
		 * �R���X�g���N�^
		 * @param		pFile			�t�@�C���|�C���^
		 */
		KsBinaryReader( const KsByte* pDataBlob, KsUInt32 dataSize );

		/**
		 * �o�C�i���[����w��T�C�Y��ǂݍ���
		 * @return		�f�[�^
		 */
		template<typename T> T const& read()
		{
			return *readArray<T>(1);
		}

		/**
		 * �o�C�i���[����w��T�C�Y��ǂݍ���
		 * @return		�f�[�^
		 */
		template<typename T> T const* readArray( KsUInt32 elementCount )
		{
			KsByte const* newPos = m_pPos + sizeof(T) * elementCount;

			if (newPos > m_pEnd)
				throw std::exception("End of file");

			T const* result = reinterpret_cast<T const*>(m_pPos);

			m_pPos = newPos;

			return result;
		}

		/**
		 * �o�C�i���[����w��T�C�Y��ǂݍ���
		 * @return		�f�[�^
		 */
		static HRESULT readEntireFile( KsWChar const* pFileName, KsByte** pData, KsUInt32* pDataSize );

		/**
		 * �o�C�i���[����w��T�C�Y��ǂݍ���
		 * @return		�f�[�^
		 */
		static HRESULT readEntireFile( KsSChar const* pFileName, KsByte** pData, KsUInt32* pDataSize );

	private:
		const KsByte*				m_pPos;			/**< */
		const KsByte*				m_pEnd;			/**< */
		KsByte*						m_pData;		/**< */


		// Prevent copying.
		KsBinaryReader( KsBinaryReader const&);
		KsBinaryReader& operator= ( KsBinaryReader const&);
};


#endif /* __KSBINARYREADER_H__ */


