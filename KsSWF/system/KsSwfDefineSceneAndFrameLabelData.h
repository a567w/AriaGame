/************************************************************************************************/
/** 
 * @file		KsSwfDefineSceneAndFrameLabelData.h
 * @brief		SWF�R�}���h
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFDEFINESCENEANDFRAMELABELDATA_H__
#define __KSSWFDEFINESCENEANDFRAMELABELDATA_H__

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
 * @class		KsSwfDefineSceneAndFrameLabelData
 * @brief		SWF�R�}���h
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		�Ȃ�
 */
/************************************************************************************************/
class ksSWF_API KsSwfDefineSceneAndFrameLabelData : public KsSwfCommand
{
	public:
		struct KS_SWF_SCENE
		{
			KsUInt32			m_offset;		/**< �V�[���̃t���[���I�t�Z�b�g	*/
			KsString			m_name;			/**< �V�[���̖��O				*/
		};

		struct KS_SWF_FRAMELABEL
		{
			KsUInt32			m_frameNum;		/**< �V�[���̃t���[���I�t�Z�b�g	*/
			KsString			m_frameLabel;	/**< �t���[�����x���̖��O			*/
		};

	public:
		/**
		 * �R���X�g���N�^
		 */
								KsSwfDefineSceneAndFrameLabelData( KsFileObject* pFile, const KsSwfRecordHeader* tag );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsSwfDefineSceneAndFrameLabelData();

		/**
		 * �R�}���h���s
		 */
		virtual void			execute();

	private:
		KsUInt32				m_sceneCount;		/**< �V�[���̐�			*/
		KS_SWF_SCENE*			m_pScenes;			/**< �V�[�����			*/
		KsUInt32				m_frameLabelCount;	/**< �t���[�����x���̐�	*/
		KS_SWF_FRAMELABEL*		m_pFrameLabels;		/**< �t���[�����x�����	*/
};

#endif	/* __KSSWFDEFINESCENEANDFRAMELABELDATA_H__ */


