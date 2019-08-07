/************************************************************************************************/
/** 
 * @file		KsSwfPlaceObject.h
 * @brief		SWF�R�}���h
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFPLACEOBJECT_H__
#define __KSSWFPLACEOBJECT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfPlaceObject
 * @brief		SWF�R�}���h
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		�Ȃ�
 */
/************************************************************************************************/
class ksSWF_API KsSwfPlaceObject : public KsSwfCommand
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsSwfPlaceObject( KsFileObject* pFile );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsSwfPlaceObject();

		/**
		 * �R�}���h���s
		 */
		virtual void			execute();

	private:
		KsUInt16				m_characterId;		/**< �z�u����L�����N�^�� ID		*/
		KsUInt16				m_depth;			/**< �L�����N�^�̐[�x				*/
		KsSwfMatrix				m_matrix;			/**< �ό`�s��f�[�^				*/
		KsSwfCxform				m_cxf;				/**< �F�ϊ��f�[�^				*/
};

/************************************************************************************************/
/**
 * @class		KsSwfPlaceObject2
 * @brief		SWF�R�}���h
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		�Ȃ�
 */
/************************************************************************************************/
class ksSWF_API KsSwfPlaceObject2 : public KsSwfCommand
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsSwfPlaceObject2( KsFileObject* pFile );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsSwfPlaceObject2();

		/**
		 * �R�}���h���s
		 */
		virtual void			execute();

	private:
		KsUInt8					m_flags;			/**< ����t���O					*/
		KsUInt16				m_characterId;		/**< �z�u����L�����N�^�� ID		*/
		KsUInt16				m_depth;			/**< �L�����N�^�̐[�x				*/
		KsSwfMatrix				m_matrix;			/**< �ό`�s��f�[�^				*/
		KsSwfCxform				m_cxf;				/**< �F�ϊ��f�[�^				*/
		KsUInt16				m_ratio;			/**< �䗦						*/
		KsString				m_name;				/**< �L�����N�^�̖��O				*/
		KsUInt16				m_clipDepth;		/**< Clip depth					*/
		KsUInt16				m_clipActions;		/**< �N���b�v�A�N�V�����f�[�^		*/
};

#endif	/* __KSSWFPLACEOBJECT_H__ */


