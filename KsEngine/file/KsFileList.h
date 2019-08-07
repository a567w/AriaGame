class KsFileList
{
	public:
		typedef struct _KsFileListInfo
		{
			KsInt32				fileSize;
			KsInt32				fileOffset;
			KsString			fileName;
		}KsFileListInfo;

		KsFileList();
		
		~KsFileList();

	private:
		KsUInt32			magic;								/**< 識別用(FLS0)					*/
		KsUInt32			flags;								/**< フラグ							*/
		KsUInt32			numFiles;							/**< ファイル数						*/
		KsUInt32			alignment;							/**< 何バイトアラインメント			*/

	
};



