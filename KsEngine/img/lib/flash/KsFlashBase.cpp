
KsUInt32 KsFlashFixed::convertToRaw() const
{
	KsUInt32 r = ((KsInt32)upperval)<<16;
	r |= lowerval;
	return r;
}
void KsFlashFixed::getFromRaw(KsInt32 raw)
{
	upperval = raw >> 16;
	lowerval = (raw & 0xffff);
}

KsReal64 KsFlashFixed::convertToDouble() const
{
	return upperval + KsReal64(lowerval) / 0x10000;
}
void KsFlashFixed::getFromDouble(KsReal64 x)
{
	upperval = (KsUInt16)floor(x);
	lowerval = (KsUInt16)((x-floor(x))*0x10000);
}
		



KsUInt16 KsFlashFixed16::ConvertToRaw() const
{
    KsUInt16 r = ((KsInt16)upperval)<<8;
    r |= lowerval;
    return r;
}
void KsFlashFixed16::GetFromRaw(KsInt16 raw)
{
    upperval = raw >> 8;
    lowerval = (raw & 0xff);
}
KsReal64 KsFlashFixed16::ConvertToDouble()
{
    return upperval + KsReal64(lowerval) / 0x100;
}
void KsFlashFixed16::GetFromDouble(KsReal64 x)
{
    upperval = (KsUInt8)floor(x);
    lowerval = (KsUInt8)((x-floor(x))*0x100);
}

