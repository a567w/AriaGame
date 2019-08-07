/************************************************************************************************/
/** 
 * @file		KsSwfCxform.h
 * @brief		SWF�p�}�g���b�N�X
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFCXFORM_H__
#define __KSSWFCXFORM_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfCxform
 * @brief		SWF�p�}�g���b�N�X
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsSwfCxform
{
		friend class KsSwfImporter;
	public:
								KsSwfCxform();
		
								KsSwfCxform( KsBool add, const KsSwfColor& addColor, KsBool mult, const KsSwfColor& multColor );
		
		KsBool					hasAdd() const { return m_bAdd; }
		KsBool					hasMult() const { return m_bMult; }

		KsSwfColor				getAddColor() const { return m_addColor; }
		KsSwfColor				getMultColor() const { return m_multColor; }

	private:
		KsBool					m_bAdd;
		KsBool					m_bMult;
		KsSwfColor				m_addColor;
		KsSwfColor				m_multColor;
};


#endif /* __KSSWFCXFORM_H__ */

