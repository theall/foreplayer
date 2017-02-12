#include "waveexport.h"

#if 1
#define Endian16_Swap(x) (x)
#define Endian_16_Swap(x) (x)
#define Endian32_Swap(x) (x)
#else
#define Endian16_Swap(x) (((x)<<8) | ((x)>>8))
#define Endian_16_Swap(x) (((x)<<8) | ((x)>>8))
#define Endian32_Swap(x) ( ((x&0xff000000)>>24) || ((x&0x00ff0000)>>8) || ((x&0x0000ff00)<<8) || ((x&0x000000ff)<<24) )
#endif

TWaveExport::TWaveExport(wchar_t *fileName, int sampleRate) :
    TAbstractExport(fileName)
  , mSampleRate(sampleRate)
{
    start();
}

TWaveExport::~TWaveExport()
{
    end();
}

void TWaveExport::start()
{
    int ua = 0;
    short wFormatTag = 0;	// format 1 is linear PCM
    short nChannels = 0;
    int nSamplesPerSec = 0, nAvgBytesPerSec = 0;
    short nBlockAlign = 0, wBitsPerSample = 0;

    // create the .WAV header
    nChannels = Endian16_Swap(2);
    nSamplesPerSec = Endian32_Swap(mSampleRate);
    nAvgBytesPerSec = Endian32_Swap((mSampleRate*4));
    wBitsPerSample = Endian16_Swap(16);
    nBlockAlign = Endian16_Swap((nChannels * (wBitsPerSample/8)));
    ua = Endian32_Swap(0x10);
    wFormatTag = Endian16_Swap(1);

    writeString("RIFF    WAVEfmt ");
    writeInt(ua);
    writeShort(wFormatTag);
    writeShort(nChannels);
    writeInt(nSamplesPerSec);
    writeInt(nAvgBytesPerSec);
    writeShort(nBlockAlign);
    writeShort(wBitsPerSample);
    writeString("data    ");
}

void TWaveExport::end()
{
    // get total file length
    seek(0, SEEK_END);
    int nLen = tell();

    // set RIFF chunk size (total minus 8 for the RIFF and length)
    seek(4, SEEK_SET);
    nLen -= 8;
    writeInt(Endian32_Swap(nLen));

    // set WAVE chunk size (total - 8 - 36 more for the WAVE header stuff)
    seek(0x28, SEEK_SET);
    nLen -= 36;
    writeInt(Endian32_Swap(nLen));
}

int TWaveExport::write(char *buf, int size)
{
    short *data = (short *)buf;
    for (int i = 0; i < size/2; i++)
    {
        writeShort(Endian16_Swap(data[i]));
    }

    return size;
}
