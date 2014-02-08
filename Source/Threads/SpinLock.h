#pragma once

#include <boost\atomic\atomic.hpp>

class SpinLock 
{
public:
  SpinLock() : m_state(Unlocked) {}

  inline void lock()
  {
	  while (m_state.exchange(Locked, boost::memory_order_acquire) == Locked) 
	  {
	  }
  }
  inline void unlock()
  {
	  m_state.store(Unlocked, boost::memory_order_release);
  }
private:
  enum LockState
  {
	  Locked,
	  Unlocked
  };
  boost::atomic<LockState> m_state;
};