/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef FVF_DECODER_H
#define FVF_DECODER_H

#include "common/rational.h"

#include "video/video_decoder.h"
#include "video/codecs/codec.h"
#include "audio/audiostream.h"
#include "audio/mixer.h"

namespace Unity {

class FVFDecoder : public ::Video::FixedRateVideoDecoder {
public:
	FVFDecoder(Audio::Mixer *mixer,
		Audio::Mixer::SoundType soundType = Audio::Mixer::kPlainSoundType);
	virtual ~FVFDecoder();

	uint16 getWidth() const { return _width; }
	uint16 getHeight() const { return _height; }

	uint32 getFrameCount() const { return _frameCount; }

	bool loadStream(Common::SeekableReadStream *stream);
	void close();

	bool isVideoLoaded() const { return _fileStream != 0; }

	::Graphics::Surface *decodeNextFrame();
	::Graphics::PixelFormat getPixelFormat() const;

protected:
	Common::Rational getFrameRate() const { return _frameRate; }

private:
	Audio::Mixer *_mixer;
	Audio::Mixer::SoundType _soundType;

	Audio::SoundHandle *_audioHandle;
	Audio::QueuingAudioStream *_audioStream;
	Audio::QueuingAudioStream *createAudioStream();

	uint16 _width;
	uint16 _height;
	uint16 _bpp;

	uint32 _frameCount;
	Common::Rational _frameRate;

	Common::SeekableReadStream *_fileStream;

	::Graphics::Surface _surface;

	byte palette_entry_count, header_pal_count;

	void readNextBlock();
	uint32 curr_block_remaining_frames, curr_block_remaining_size;

	// generated lookup tables
	uint32 block_id_to_offset[6000];
	uint32 block_status_lookup[6000];
	uint16 block_lookup[16000];
	byte modify_lookup[32768];

	// front/back buffers
	byte real_front_buffer[64000], real_back_buffer[64000],
		real_colour_front_buffer[32000], real_colour_back_buffer[32000];
	byte *front_buffer, *back_buffer, *colour_front_buffer, *colour_back_buffer;

	// decoder state (visibility)
	byte curr_status;
	byte block_status[6000];
	// decoder state (per-frame offset data)
	int16 storage[256];

	void setupTables();
	void decodeVideoFrame(uint16 *frame, unsigned int len);
	void decodeVideoFrameData(uint16 *frame, unsigned int len);

	unsigned int GetOddPixelOffset(unsigned int in);
};

} // Unity

#endif
