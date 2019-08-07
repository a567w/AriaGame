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
		KsUInt32			magic;								/**< ���ʗp(FLS0)					*/
		KsUInt32			flags;								/**< �t���O							*/
		KsUInt32			numFiles;							/**< �t�@�C����						*/
		KsUInt32			alignment;							/**< ���o�C�g�A���C�������g			*/

	
};



