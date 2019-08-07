/************************************************************************************************/
/** 
 * @file		KsTimer.h
 * @brief		�^�C�}�[
 * @author		Tsukasa Kato
 * @data		2005/06/27
 * @since		2005/06/27
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSTIMER_H__
#define __KSTIMER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsTimer
 * @brief		�^�C�}�[
 * @author		Tsukasa Kato
 * @data		2005/06/27
 * @since		2005/06/27
 */
/************************************************************************************************/
class ksENGINE_API KsTimer
{
	public:

		enum ksFPS_TYPE
		{
			ksFPS60 = 0,
			ksFPS30 = 1,
			ksFPS15 = 2,
		};

	public:
		/**
		 * �R���X�g���N�^
		 */
		KsTimer();

	public:
		/**
		 * ������
		 */
		static void					initialize();

		/**
		 * �~���b�Ŏ��Ԃ��擾
		 * @return					�~���b
		 */
		static KsUInt32				getTimeCount();

		/**
		 * �}�C�N���b�Ŏ��Ԃ��擾
		 * @return					�}�C�N���b
		 */
		static KsInt64				getMicroCount();

		/**
		 * FPS���擾����
		 * @return					FPS
		 */
		static KsUInt32				getFps();

		/**
		 * �t���[���J�E���g���擾
		 * @return					�t���[���J�E���g
		 */
		static KsUInt32				getFrameCount();

		/**
		 * �X�V����
		 */
		static void					update();

		static void					vsync( ksFPS_TYPE _fpsType = ksFPS60 );

		static void					setStart();
		static void					setCpu();
		static void					setGpu();
		static void					setTotal();

		static KsUInt32				getCpuPerformance();
		static KsUInt32				getGpuPerformance();
		static KsUInt32				getTotalPerformance();

		KsReal						getElapsedTime() const { return m_elapsedTime; }

	private:
		static LARGE_INTEGER		m_frequency;				/**< �J�Ԃ����x			*/
		static KsBool				m_support;					/**< �T�|�[�g���		*/
		static KsUInt32				m_initTime;					/**< ��������			*/
		static KsReal				m_frameTime;				/**< �t���[���^�C��		*/
		static KsUInt32				m_frameCount;				/**< �o�߃t���[����		*/
		static KsUInt32				m_fps;						/**< FPS�l				*/
		static KsUInt32				m_fpsCount;					/**< FPS�v���p			*/
		static KsUInt32				m_startTime;				/**< �v���J�n����		*/
		static KsUInt32				m_cpuTime;					/**< CUP��������			*/
		static KsUInt32				m_gpuTime;					/**< GPU��������			*/
		static KsUInt32				m_totalTime;				/**< �S�̏�������		*/
		static KsUInt32				m_lastFrameTime;			/**< �O��FPS�X�V����		*/
		static KsUInt32				m_cpuPerformance;			/**< CPU�p�t�H�[�}���X	*/
		static KsUInt32				m_gpuPerformance;			/**< GPU�p�t�H�[�}���X	*/
		static KsUInt32				m_totalPerformance;			/**< ���v�p�t�H�[�}���X	*/
		KsReal						m_elapsedTime;				/**< �o�ߎ���			*/
};


#endif		/* __KSTIMER_H__ */


