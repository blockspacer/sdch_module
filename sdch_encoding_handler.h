// Copyright (c) 2015 Yandex LLC. All rights reserved.
// Author: Vasily Chekalkin <bacek@yandex-team.ru>

#ifndef SDCH_ENCODING_HANDLER_H_
#define SDCH_ENCODING_HANDLER_H_

#include "sdch_handler.h"

#include <google/vcencoder.h>

namespace sdch {

class RequestContext;

// Actual VCDiff encoding handler
class EncodingHandler : public Handler,
                        public open_vcdiff::OutputStringInterface {
 public:
  // TODO: Remove fat RequestContext and only pass required parameters
  EncodingHandler(RequestContext* ctx, Handler* next);
  ~EncodingHandler();

  // sdch::Handler implementation
  ssize_t on_data(const char* buf, size_t len) override;
  void on_finish() override;

  // open_vcdiff::OutputStringInterface implementation
  open_vcdiff::OutputStringInterface& append(const char* s, size_t n) override;
  void clear() override;
  void push_back(char c) override;
  void ReserveAdditionalBytes(size_t res_arg) override;
  size_t size() const override;

 private:
  class OutHelper;

  RequestContext* ctx_;

  // Actual encoder. We do allocate it from pool, so no manual memory management
  // required.
  open_vcdiff::VCDiffStreamingEncoder* enc_;

  // For OutputStringInterface implementation
  size_t cursize_;
};


}  // namespace sdch

#endif  // SDCH_ENCODING_HANDLER_H_

