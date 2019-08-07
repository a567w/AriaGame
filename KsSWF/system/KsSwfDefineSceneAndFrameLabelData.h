/************************************************************************************************/
/** 
 * @file		KsSwfDefineSceneAndFrameLabelData.h
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFDEFINESCENEANDFRAMELABELDATA_H__
#define __KSSWFDEFINESCENEANDFRAMELABELDATA_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfDefineSceneAndFrameLabelData
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class ksSWF_API KsSwfDefineSceneAndFrameLabelData : public KsSwfCommand
{
	public:
		struct KS_SWF_SCENE
		{
			KsUInt32			m_offset;		/**< シーンのフレームオフセット	*/
			KsString			m_name;			/**< シーンの名前				*/
		};

		struct KS_SWF_FRAMELABEL
		{
			KsUInt32			m_frameNum;		/**< シーンのフレームオフセット	*/
			KsString			m_frameLabel;	/**< フレームラベルの名前			*/
		};

	public:
		/**
		 * コンストラクタ
		 */
								KsSwfDefineSceneAndFrameLabelData( KsFileObject* pFile, const KsSwfRecordHeader* tag );

		/**
		 * デストラクタ
		 */
		virtual					~KsSwfDefineSceneAndFrameLabelData();

		/**
		 * コマンド実行
		 */
		virtual void			execute();

	private:
		KsUInt32				m_sceneCount;		/**< シーンの数			*/
		KS_SWF_SCENE*			m_pScenes;			/**< シーン情報			*/
		KsUInt32				m_frameLabelCount;	/**< フレームラベルの数	*/
		KS_SWF_FRAMELABEL*		m_pFrameLabels;		/**< フレームラベル情報	*/
};

#endif	/* __KSSWFDEFINESCENEANDFRAMELABELDATA_H__ */


