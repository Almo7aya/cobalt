// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_UPDATE_CLIENT_PING_MANAGER_H_
#define COMPONENTS_UPDATE_CLIENT_PING_MANAGER_H_

#include <string>

#include "base/functional/callback_forward.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/threading/thread_checker.h"

namespace update_client {

class Configurator;
class Component;

#if defined(STARBOARD)
class PingSender;
#endif

class PingManager : public base::RefCountedThreadSafe<PingManager> {
 public:
  // |error| is 0 if the ping was sent successfully, otherwise |error| contains
  // a value with no particular meaning for the caller.
  using Callback =
      base::OnceCallback<void(int error, const std::string& response)>;

  explicit PingManager(scoped_refptr<Configurator> config);

  // Sends a ping for the |item|. |callback| is invoked after the ping is sent
  // or an error has occured. The ping itself is not persisted and it will
  // be discarded if it has not been sent for any reason.
  virtual void SendPing(const Component& component, Callback callback);

#if defined(STARBOARD)
  virtual void Cancel();
#endif
 protected:
  virtual ~PingManager();

 private:
  friend class base::RefCountedThreadSafe<PingManager>;

  THREAD_CHECKER(thread_checker_);
  const scoped_refptr<Configurator> config_;

#if defined(STARBOARD)
  scoped_refptr<PingSender> ping_sender_;
#endif

  DISALLOW_COPY_AND_ASSIGN(PingManager);
};

}  // namespace update_client

#endif  // COMPONENTS_UPDATE_CLIENT_PING_MANAGER_H_
