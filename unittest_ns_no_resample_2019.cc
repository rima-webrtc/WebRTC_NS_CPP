/*
 *  Copyright (c) 2016 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

//#include "ns/noise_suppressor.h"
#include "4884ns/include/modules/audio_processing/ns/noise_suppressor.h"
#include <memory>
#include <string>

#include "timing.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>

#ifndef nullptr
#  define nullptr 0
#endif

#ifndef MIN
#  define MIN(A, B) ((A) < (B) ? (A) : (B))
#endif

#ifndef MAX
#  define MAX(A, B) ((A) > (B) ? (A) : (B))
#endif

using namespace webrtc;

// int nsProc(short* input, size_t SampleCount, size_t sampleRate, int num_channels) {

//   //NsConfig cfg;
//   /*
//    * NsConfig::SuppressionLevel::k6dB
//    * NsConfig::SuppressionLevel::k12dB
//    * NsConfig::SuppressionLevel::k18dB
//    * NsConfig::SuppressionLevel::k21dB
//    */
//   //    cfg.target_level = NsConfig::SuppressionLevel::k21dB;
//   //NoiseSuppressor ns(cfg, sampleRate, num_channels);
//   short* buffer = input;
//   bool split_bands = sampleRate > 16000;
//   uint64_t frames = (SampleCount / stream_config.num_frames());
//   for (size_t frame_index = 0; frame_index < frames; ++frame_index) {
//     //std::cout<<"frame_index"<<frame_index<<std::endl;
//     audio.CopyFrom(buffer, stream_config);
//     if (split_bands) { audio.SplitIntoFrequencyBands(); }
//     ns.Analyze(audio);
//     ns.Process(&audio);
//     if (split_bands) { audio.MergeFrequencyBands(); }
//     audio.CopyTo(stream_config, buffer);
//     buffer += stream_config.num_frames();
//   }
//   return 0;
// }

void WebRtc_DeNoise(char* in_file, char* out_file, uint32_t sampleRate, uint32_t num_channels) {
  std::ifstream in_stream;
  in_stream.open(in_file, std::ios::in | std::ios::binary);
  std::ofstream out_stream;
  out_stream.open(out_file, std::ios::out | std::ios::binary);

  int in_size = 960*2;
  char* in_buffer = (char*)malloc(in_size);

  // wav or pcm
  in_stream.read((char*)in_buffer, 44);
  if (in_buffer[0] == 'R' && in_buffer[1] == 'I' && in_buffer[2] == 'F' && in_buffer[3] == 'F') {
    // wav
    in_stream.seekg(44, std::ios_base::beg);

  } else {
    in_stream.seekg(0, std::ios_base::beg);
  }
  int index = 0;
  NsConfig cfg;
NoiseSuppressor ns(cfg, sampleRate, num_channels);
  AudioBuffer audio(sampleRate, num_channels, sampleRate, num_channels, sampleRate, num_channels);
  StreamConfig stream_config(sampleRate, num_channels);
  do {
    in_stream.read((char*)in_buffer, in_size);
    
    size_t gcount_size = in_stream.gcount();
    
    size_t sampleCout = gcount_size/4;
    short * input_ptr = (short *)in_buffer;
    std::cout << "process index: " << index++ << " insize: " << in_size << " gcount_size:" << gcount_size <<" sampleRate: "<<sampleRate<<" channels: "<<num_channels <<std::endl;
  
  short* buffer = input_ptr;
  bool split_bands = sampleRate > 16000;
  uint64_t frames = (sampleCout / stream_config.num_frames());
  for (size_t frame_index = 0; frame_index < frames; ++frame_index) {
    //std::cout<<"frame_index"<<frame_index<<std::endl;
    audio.CopyFrom(buffer, stream_config);
    if (split_bands) { audio.SplitIntoFrequencyBands(); }
    ns.Analyze(audio);
    ns.Process(&audio);
    if (split_bands) { audio.MergeFrequencyBands(); }
    audio.CopyTo(stream_config, buffer);
    buffer += stream_config.num_frames()*stream_config.num_channels();
  }

    out_stream.write((char*)in_buffer, gcount_size);

  } while (in_stream && !in_stream.eof());

  if (in_buffer) free(in_buffer);
// corrupted size vs. prev_size
// Aborted (core dumped)
// out_stream.write((char*)in_buffer, sampleCout*2);
}

int main(int argc, char* argv[]) {
  WebRtc_DeNoise("/home/fengmao/cowa_audio/backup_git/WebRTC_NS_CPP/capture.pcm",
                 "../lab2/capture_NS_no_sample_2019_960*2.pcm", 48000, 2);
  printf("�������棬�������...\n");
  return 0;
}
