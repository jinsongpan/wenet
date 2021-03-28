// Copyright 2021 Mobvoi Inc. All Rights Reserved.
// Author: zhendong.peng@mobvoi.com (Zhendong Peng)

#ifndef DECODER_DECODER_INTERFACE_H_
#define DECODER_DECODER_INTERFACE_H_

#include <string>
#include <vector>

#include "decoder/ctc_prefix_beam_search.h"

namespace wenet {

struct DecodeOptions {
  int chunk_size = 16;
  int num_left_chunks = -1;
  CtcPrefixBeamSearchOptions ctc_search_opts;
};

struct WordPiece {
  std::string word;
  int start;
  int end;

  void Reset() {
    word.clear();
    start = -1;
    end = -1;
  }

  friend std::ostream& operator<<(std::ostream& ostream,
                                  const WordPiece& word_piece) {
    return ostream << "{word:" << word_piece.word
                   << ", startTime: " << word_piece.start
                   << " endTime: " << word_piece.end
                   << "}";
  }
};

struct DecodeResult {
  std::vector<std::string> nbest;
  std::vector<WordPiece> word_pieces;

  void clear() {
    nbest.clear();
    word_pieces.clear();
  }

  friend std::ostream& operator<<(std::ostream& ostream,
                                  const DecodeResult& decodeResult) {
    ostream << "{Nbest: [";
    for (const std::string& path : decodeResult.nbest) {
      ostream << path << ", ";
    }
    ostream << "], WordPieces: ";
    for (const WordPiece& word_piece : decodeResult.word_pieces) {
      ostream << word_piece << ", ";
    }
    return ostream << "]}";
  }
};

class DecoderInterface {
 public:
  DecoderInterface() {}
  virtual ~DecoderInterface() {}

  virtual bool Decode() = 0;
  virtual void Reset() = 0;
};

}  // namespace wenet

#endif  // DECODER_DECODER_INTERFACE_H_
